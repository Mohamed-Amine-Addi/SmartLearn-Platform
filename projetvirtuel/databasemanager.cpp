#include "databasemanager.h"
#include <QCryptographicHash>
#include <QDate>

databasemanager& databasemanager::instance() {
    static databasemanager inst;
    return inst;
}

bool databasemanager::init(const QString& dbPath) {
    m_db = QSqlDatabase::addDatabase("QSQLITE");
    m_db.setDatabaseName(dbPath);
    if (!m_db.open()) {
        qDebug() << "DB open error:" << m_db.lastError().text();
        return false;
    }
    qDebug() << "Database opened:" << dbPath;
    if (!createTables()) return false;

    // Migration: add last_login column if it doesn't exist yet
    // (safe to run every time — SQLite ignores if column exists)
    QSqlQuery mig(m_db);
    mig.exec("ALTER TABLE users ADD COLUMN "
             "last_login TEXT DEFAULT ''");

    seedCourses();
    seedQuestions();
    seedLessons();

    // Migration: if lessons table exists but is empty, force re-seed
    // This fixes users who had the app before lessons were added
    QSqlQuery lessonCheck(m_db);
    lessonCheck.exec("SELECT COUNT(*) FROM lessons");
    if (lessonCheck.next() && lessonCheck.value(0).toInt() == 0) {
        qDebug() << "Lessons table empty — re-seeding...";
        // Reset the seed guard by temporarily allowing re-seed
        QSqlQuery resetQ(m_db);
        resetQ.exec("DELETE FROM lessons");
        seedLessons();
    }

    return true;
}

bool databasemanager::createTables() {
    QSqlQuery q(m_db);

    // Users
    bool ok = q.exec(R"(
        CREATE TABLE IF NOT EXISTS users (
            id         INTEGER PRIMARY KEY AUTOINCREMENT,
            first_name TEXT NOT NULL,
            last_name  TEXT NOT NULL,
            username   TEXT UNIQUE NOT NULL,
            email      TEXT UNIQUE NOT NULL,
            password   TEXT NOT NULL,
            xp         INTEGER DEFAULT 0,
            level      INTEGER DEFAULT 1,
            streak     INTEGER DEFAULT 0,
            last_login TEXT DEFAULT '',
            created_at TEXT DEFAULT (datetime('now'))
        )
    )");
    if (!ok) {
        qDebug() << "users table error:" << q.lastError().text();
        return false;
    }

    // Courses
    ok = q.exec(R"(
        CREATE TABLE IF NOT EXISTS courses (
            id            INTEGER PRIMARY KEY AUTOINCREMENT,
            title         TEXT UNIQUE NOT NULL,
            description   TEXT NOT NULL,
            language      TEXT NOT NULL,
            difficulty    INTEGER NOT NULL,
            total_lessons INTEGER DEFAULT 0,
            xp_reward     INTEGER DEFAULT 100
        )
    )");
    if (!ok) {
        qDebug() << "courses table error:" << q.lastError().text();
        return false;
    }

    // User progress
    ok = q.exec(R"(
        CREATE TABLE IF NOT EXISTS user_progress (
            id           INTEGER PRIMARY KEY AUTOINCREMENT,
            user_id      INTEGER NOT NULL,
            course_id    INTEGER NOT NULL,
            lessons_done INTEGER DEFAULT 0,
            completed    INTEGER DEFAULT 0,
            started_at   TEXT DEFAULT (datetime('now')),
            FOREIGN KEY(user_id)   REFERENCES users(id),
            FOREIGN KEY(course_id) REFERENCES courses(id),
            UNIQUE(user_id, course_id)
        )
    )");
    if (!ok) {
        qDebug() << "user_progress table error:" << q.lastError().text();
        return false;
    }

    // Questions
    ok = q.exec(R"(
        CREATE TABLE IF NOT EXISTS questions (
            id             INTEGER PRIMARY KEY AUTOINCREMENT,
            course_id      INTEGER NOT NULL,
            type           INTEGER DEFAULT 0,
            text           TEXT NOT NULL,
            option_0       TEXT DEFAULT '',
            option_1       TEXT DEFAULT '',
            option_2       TEXT DEFAULT '',
            option_3       TEXT DEFAULT '',
            correct_index  INTEGER DEFAULT 0,
            correct_answer TEXT DEFAULT '',
            explanation    TEXT DEFAULT '',
            xp_reward      INTEGER DEFAULT 10,
            FOREIGN KEY(course_id) REFERENCES courses(id)
        )
    )");
    if (!ok) {
        qDebug() << "questions table error:" << q.lastError().text();
        return false;
    }

    // Quiz history
    ok = q.exec(R"(
        CREATE TABLE IF NOT EXISTS quiz_history (
            id        INTEGER PRIMARY KEY AUTOINCREMENT,
            username  TEXT NOT NULL,
            course_id INTEGER NOT NULL,
            score     INTEGER NOT NULL,
            xp_earned INTEGER NOT NULL,
            correct   INTEGER NOT NULL,
            total     INTEGER NOT NULL,
            taken_at  TEXT DEFAULT (datetime('now'))
        )
    )");
    if (!ok) {
        qDebug() << "quiz_history table error:" << q.lastError().text();
        return false;
    }

    // Badges
    ok = q.exec(R"(
        CREATE TABLE IF NOT EXISTS user_badges (
            username   TEXT NOT NULL,
            badge_key  TEXT NOT NULL,
            awarded_at TEXT DEFAULT (datetime('now')),
            PRIMARY KEY (username, badge_key)
        )
    )");
    if (!ok) {
        qDebug() << "user_badges table error:" << q.lastError().text();
        return false;
    }

    // Lessons
    ok = q.exec(R"(
        CREATE TABLE IF NOT EXISTS lessons (
            id        INTEGER PRIMARY KEY AUTOINCREMENT,
            course_id INTEGER NOT NULL,
            order_num INTEGER NOT NULL,
            title     TEXT NOT NULL,
            content   TEXT NOT NULL,
            FOREIGN KEY(course_id) REFERENCES courses(id)
        )
    )");
    if (!ok) {
        qDebug() << "lessons table error:" << q.lastError().text();
        return false;
    }

    qDebug() << "All tables created successfully.";
    return true;
}// ── Password hashing ─────────────────────────────────────────
static QString hashPassword(const QString& pw) {
    return QCryptographicHash::hash(
               pw.toUtf8(), QCryptographicHash::Sha256).toHex();
}

// ── Auth ─────────────────────────────────────────────────────
bool databasemanager::usernameexists(const QString& username) {
    QSqlQuery q(m_db);
    q.prepare("SELECT id FROM users WHERE username=:u");
    q.bindValue(":u", username.trimmed().toLower());
    q.exec();
    return q.next();
}

bool databasemanager::emailexists(const QString& email) {
    QSqlQuery q(m_db);
    q.prepare("SELECT id FROM users WHERE email=:e");
    q.bindValue(":e", email.trimmed().toLower());
    q.exec();
    return q.next();
}

bool databasemanager::registeruser(const QString& firstname,
                                   const QString& lastname,
                                   const QString& username,
                                   const QString& email,
                                   const QString& password) {
    QSqlQuery q(m_db);
    q.prepare(R"(
        INSERT INTO users
            (first_name, last_name, username, email, password)
        VALUES (:fn, :ln, :u, :e, :p)
    )");
    q.bindValue(":fn", firstname.trimmed());
    q.bindValue(":ln", lastname.trimmed());
    q.bindValue(":u",  username.trimmed().toLower());
    q.bindValue(":e",  email.trimmed().toLower());
    q.bindValue(":p",  hashPassword(password));
    if (!q.exec()) {
        qDebug() << "registeruser error:" << q.lastError().text();
        return false;
    }
    return true;
}

bool databasemanager::loginuser(const QString& name,
                                const QString& password) {
    QSqlQuery q(m_db);
    q.prepare(R"(
        SELECT id FROM users
        WHERE username=:u AND password=:p
    )");
    q.bindValue(":u", name.trimmed().toLower());
    q.bindValue(":p", hashPassword(password));
    if (q.exec() && q.next()) return true;
    return false;
}

// ── User data ─────────────────────────────────────────────────
int databasemanager::getUserXp(const QString& username) {
    QSqlQuery q(m_db);
    q.prepare("SELECT xp FROM users WHERE username=:u");
    q.bindValue(":u", username.trimmed().toLower());
    q.exec();
    if (q.next()) {
        qDebug() << "getUserXp for" << username
                 << "=" << q.value(0).toInt();
        return q.value(0).toInt();
    }
    return 0;
}

int databasemanager::getUserLevel(const QString& username) {
    QSqlQuery q(m_db);
    q.prepare("SELECT level FROM users WHERE username=:u");
    q.bindValue(":u", username.trimmed().toLower());
    q.exec();
    return q.next() ? q.value(0).toInt() : 1;
}

QString databasemanager::getUserFirstname(const QString& username) {
    QSqlQuery q(m_db);
    q.prepare("SELECT first_name FROM users WHERE username=:u");
    q.bindValue(":u", username.trimmed().toLower());
    q.exec();
    return q.next() ? q.value(0).toString() : username;
}

void databasemanager::addXpToUser(const QString& username, int xp) {
    if (xp <= 0) return;

    // Add XP
    QSqlQuery q(m_db);
    q.prepare("UPDATE users SET xp = xp + :x WHERE username=:u");
    q.bindValue(":x", xp);
    q.bindValue(":u", username.trimmed().toLower());
    if (!q.exec()) {
        qDebug() << "addXpToUser error:" << q.lastError().text();
        return;
    }
    qDebug() << "Added" << xp << "XP to" << username;

    // Recalculate level
    QSqlQuery q2(m_db);
    q2.prepare("SELECT xp, level FROM users WHERE username=:u");
    q2.bindValue(":u", username.trimmed().toLower());
    q2.exec();
    if (q2.next()) {
        int totalXp   = q2.value(0).toInt();
        int curLevel  = q2.value(1).toInt();
        int newLevel  = 1;
        int threshold = 100;
        int xpCopy    = totalXp;
        while (xpCopy >= threshold) {
            xpCopy -= threshold;
            newLevel++;
            threshold = newLevel * 100;
        }
        qDebug() << "Level calc: totalXP=" << totalXp
                 << "newLevel=" << newLevel;
        if (newLevel != curLevel) {
            QSqlQuery q3(m_db);
            q3.prepare(
                "UPDATE users SET level=:l WHERE username=:u");
            q3.bindValue(":l", newLevel);
            q3.bindValue(":u", username.trimmed().toLower());
            q3.exec();
            qDebug() << "Level up! Now level" << newLevel;
        }
    }
}

// ── Courses ───────────────────────────────────────────────────
QList<course> databasemanager::getAllCourses() {
    QList<course> list;
    QSqlQuery q(m_db);
    bool ok = q.exec(R"(
        SELECT id, title, description, language,
               difficulty, total_lessons, xp_reward
        FROM courses
        ORDER BY difficulty, id
    )");
    if (!ok) {
        qDebug() << "getAllCourses error:" << q.lastError().text();
        return list;
    }
    while (q.next()) {
        course c;
        c.id           = q.value(0).toInt();
        c.title        = q.value(1).toString();
        c.description  = q.value(2).toString();
        c.language     = q.value(3).toString();
        c.difficulty   = static_cast<Difficulty>(q.value(4).toInt());
        c.totallessons = q.value(5).toInt();
        c.xpreward     = q.value(6).toInt();
        list.append(c);
    }
    qDebug() << "Loaded" << list.size() << "courses from DB";
    return list;
}

bool databasemanager::courseExists(const QString& title) {
    QSqlQuery q(m_db);
    q.prepare("SELECT id FROM courses WHERE title=:t");
    q.bindValue(":t", title);
    q.exec();
    return q.next();
}

// ── Questions ────────────────────────────────────────────────
QList<Question> databasemanager::getQuestionsForCourse(
    int courseId)
{
    QList<Question> list;
    QSqlQuery q(m_db);
    q.prepare(R"(
        SELECT id, type, text,
               option_0, option_1, option_2, option_3,
               correct_index, correct_answer,
               explanation, xp_reward
        FROM questions
        WHERE course_id=:cid
        ORDER BY id
    )");
    q.bindValue(":cid", courseId);
    if (!q.exec()) {
        qDebug() << "getQuestionsForCourse error:"
                 << q.lastError().text();
        return list;
    }
    while (q.next()) {
        Question qu;
        qu.id            = q.value(0).toInt();
        qu.courseId      = courseId;
        qu.type          = static_cast<QuestionType>(
            q.value(1).toInt());
        qu.text          = q.value(2).toString();
        qu.options       << q.value(3).toString()
                   << q.value(4).toString()
                   << q.value(5).toString()
                   << q.value(6).toString();
        qu.correctIndex  = q.value(7).toInt();
        qu.correctAnswer = q.value(8).toString();
        qu.explanation   = q.value(9).toString();
        qu.xpReward      = q.value(10).toInt();
        list.append(qu);
    }
    qDebug() << "Loaded" << list.size()
             << "questions for courseId" << courseId;
    return list;
}

bool databasemanager::saveQuizResult(const QString& username,
                                     const QuizResult& result) {
    QSqlQuery q(m_db);
    q.prepare(R"(
        INSERT INTO quiz_history
            (username, course_id, score, xp_earned,
             correct, total)
        VALUES (:u, :cid, :sc, :xp, :cor, :tot)
    )");
    q.bindValue(":u",   username.trimmed().toLower());
    q.bindValue(":cid", result.courseId);
    q.bindValue(":sc",  result.score);
    q.bindValue(":xp",  result.xpEarned);
    q.bindValue(":cor", result.correct);
    q.bindValue(":tot", result.total);
    if (!q.exec()) {
        qDebug() << "saveQuizResult error:" << q.lastError().text();
        return false;
    }
    qDebug() << "Quiz result saved: score=" << result.score
             << "xp=" << result.xpEarned;
    return true;
}

// ── Progress ──────────────────────────────────────────────────
QList<QuizHistoryEntry> databasemanager::getQuizHistory(
    const QString& username)
{
    QList<QuizHistoryEntry> list;
    QSqlQuery q(m_db);
    q.prepare(R"(
        SELECT c.title, h.score, h.correct,
               h.total, h.xp_earned, h.taken_at
        FROM quiz_history h
        JOIN courses c ON h.course_id = c.id
        WHERE h.username=:u
        ORDER BY h.taken_at DESC
    )");
    q.bindValue(":u", username.trimmed().toLower());
    q.exec();
    while (q.next()) {
        QuizHistoryEntry e;
        e.courseTitle = q.value(0).toString();
        e.score       = q.value(1).toInt();
        e.correct     = q.value(2).toInt();
        e.total       = q.value(3).toInt();
        e.xpEarned    = q.value(4).toInt();
        e.takenAt     = q.value(5).toString().left(10);
        list.append(e);
    }
    return list;
}

int databasemanager::getTotalQuizesDone(
    const QString& username)
{
    QSqlQuery q(m_db);
    q.prepare(R"(
        SELECT COUNT(*) FROM quiz_history
        WHERE username=:u
    )");
    q.bindValue(":u", username.trimmed().toLower());
    q.exec();
    return q.next() ? q.value(0).toInt() : 0;
}

int databasemanager::getAverageScore(
    const QString& username)
{
    QSqlQuery q(m_db);
    q.prepare(R"(
        SELECT AVG(score) FROM quiz_history
        WHERE username=:u
    )");
    q.bindValue(":u", username.trimmed().toLower());
    q.exec();
    return q.next() ? q.value(0).toInt() : 0;
}

// ── Badges ───────────────────────────────────────────────────
bool databasemanager::hasBadge(const QString& username,
                               const QString& key) {
    QSqlQuery q(m_db);
    q.prepare(R"(
        SELECT 1 FROM user_badges
        WHERE username=:u AND badge_key=:k
    )");
    q.bindValue(":u", username.trimmed().toLower());
    q.bindValue(":k", key);
    q.exec();
    return q.next();
}

bool databasemanager::awardBadge(const QString& username,
                                 const QString& key) {
    if (hasBadge(username, key)) return false;
    QSqlQuery q(m_db);
    q.prepare(R"(
        INSERT OR IGNORE INTO user_badges
            (username, badge_key)
        VALUES (:u, :k)
    )");
    q.bindValue(":u", username.trimmed().toLower());
    q.bindValue(":k", key);
    return q.exec();
}

QList<Badge> databasemanager::getUserBadges(
    const QString& username)
{
    QList<Badge> all = allBadges();
    for (Badge& b : all)
        b.unlocked = hasBadge(username, b.key);
    return all;
}

void databasemanager::checkAndAwardBadges(
    const QString& username)
{
    int xp      = getUserXp(username);
    int level   = getUserLevel(username);
    int quizzes = getTotalQuizesDone(username);
    int avg     = getAverageScore(username);

    if (quizzes >= 1)  awardBadge(username, "first_quiz");
    if (quizzes >= 5)  awardBadge(username, "quiz_5");
    if (quizzes >= 10) awardBadge(username, "quiz_10");
    if (xp >= 100)     awardBadge(username, "xp_100");
    if (xp >= 500)     awardBadge(username, "xp_500");
    if (level >= 3)    awardBadge(username, "level_3");
    if (level >= 5)    awardBadge(username, "level_5");
    if (avg >= 80)     awardBadge(username, "avg_80");
}

// ── Seed courses ─────────────────────────────────────────────
void databasemanager::seedCourses() {
    QSqlQuery check(m_db);
    check.exec("SELECT COUNT(*) FROM courses");
    if (check.next() && check.value(0).toInt() > 0) return;

    struct CourseData {
        QString title, description, language;
        int difficulty, lessons, xp;
    };

    QList<CourseData> courses = {
                                 {"C++ Fundamentals",
                                  "Master variables, types, loops and functions in C++.",
                                  "C++", 0, 8, 150},
                                 {"C++ Object-Oriented Programming",
                                  "Learn classes, inheritance, polymorphism and encapsulation.",
                                  "C++", 1, 10, 250},
                                 {"C++ Advanced Topics",
                                  "Templates, STL, smart pointers and modern C++17 features.",
                                  "C++", 2, 12, 400},
                                 {"Python Basics",
                                  "Learn Python syntax, variables, lists and control flow.",
                                  "Python", 0, 7, 120},
                                 {"Python Fundamentals & Modules",
                                  "Functions, modules, file handling and error management.",
                                  "Python", 1, 9, 220},
                                 {"Data Structures in C++",
                                  "Arrays, linked lists, stacks, queues and trees.",
                                  "C++", 1, 11, 300},
                                 {"Algorithms & Complexity",
                                  "Sorting, searching, recursion and Big-O analysis.",
                                  "C++", 2, 10, 380},
                                 {"Python for Data Science",
                                  "NumPy, Pandas basics and data manipulation with Python.",
                                  "Python", 2, 8, 350},
                                 };

    QSqlQuery q(m_db);
    q.prepare(R"(
        INSERT OR IGNORE INTO courses
            (title, description, language,
             difficulty, total_lessons, xp_reward)
        VALUES (:t, :d, :l, :diff, :les, :xp)
    )");

    for (const CourseData& c : courses) {
        q.bindValue(":t",    c.title);
        q.bindValue(":d",    c.description);
        q.bindValue(":l",    c.language);
        q.bindValue(":diff", c.difficulty);
        q.bindValue(":les",  c.lessons);
        q.bindValue(":xp",   c.xp);
        if (!q.exec())
            qDebug() << "Seed course error:"
                     << q.lastError().text();
    }
    qDebug() << "Courses seeded:" << courses.size();
}

// ── Seed questions ───────────────────────────────────────────
void databasemanager::seedQuestions() {
    QSqlQuery check(m_db);
    check.exec("SELECT COUNT(*) FROM questions");
    if (check.next() && check.value(0).toInt() > 0) return;

    auto getCourseId = [this](const QString& title) -> int {
        QSqlQuery q(m_db);
        q.prepare("SELECT id FROM courses WHERE title=:t");
        q.bindValue(":t", title);
        q.exec();
        if (q.next()) return q.value(0).toInt();
        qDebug() << "WARNING: course not found:" << title;
        return -1;
    };

    // type: 0=MultipleChoice 1=TrueFalse 2=FillBlank
    struct QData {
        QString course, text, o0, o1, o2, o3,
            correctAnswer, explanation;
        int type, correctIndex, xp;
    };

    QList<QData> questions = {

    // ── C++ Fundamentals ──────────────────────
    {"C++ Fundamentals",
     "Which keyword declares an integer variable in C++?",
     "int","float","string","bool",
     "","'int' stores whole numbers like 1, -5, 100.",
     0, 0, 10},

        {"C++ Fundamentals",
         "What symbol ends every statement in C++?",
         "","","","",
         ";","Every C++ statement must end with a semicolon ;",
         2, 0, 15},

        {"C++ Fundamentals",
         "In C++, // is used to write a single-line comment.",
         "True","False","","",
         "","// comment. Use /* */ for multi-line comments.",
         1, 0, 10},

        {"C++ Fundamentals",
         "Which syntax correctly prints text in C++?",
         "print(\"Hello\")","Console.Write(\"Hello\")",
         "cout << \"Hello\";","echo \"Hello\"",
         "","cout with << is the standard C++ output operator.",
         0, 2, 10},

        {"C++ Fundamentals",
         "What keyword makes a variable read-only in C++?",
         "","","","",
         "const","const int x = 5; cannot be changed after declaration.",
         2, 0, 15},

        {"C++ Fundamentals",
         "C++ is a case-sensitive programming language.",
         "True","False","","",
         "","'myVar' and 'myvar' are completely different identifiers.",
         1, 0, 10},

        {"C++ Fundamentals",
         "Which data type stores a single character in C++?",
         "string","char","letter","byte",
         "","char c = 'A'; stores exactly one character.",
         0, 1, 10},

        {"C++ Fundamentals",
         "What is stored in a variable of type bool?",
         "","","","",
         "true or false","bool values are either true (1) or false (0).",
         2, 0, 10},

        // ── C++ OOP ───────────────────────────────
        {"C++ Object-Oriented Programming",
         "Which keyword defines a class in C++?",
         "class","struct","object","type",
         "","class MyClass { }; — members are private by default.",
         0, 0, 10},

        {"C++ Object-Oriented Programming",
         "A constructor has the same name as the class.",
         "True","False","","",
         "","Constructor: MyClass() { } — no return type.",
         1, 0, 10},

        {"C++ Object-Oriented Programming",
         "Which access specifier makes members accessible everywhere?",
         "","","","",
         "public","public members can be accessed from outside the class.",
         2, 0, 15},

        {"C++ Object-Oriented Programming",
         "What is the OOP concept of hiding internal data called?",
         "Inheritance","Polymorphism","Encapsulation","Abstraction",
         "","Encapsulation uses private members and public getters/setters.",
         0, 2, 10},

        {"C++ Object-Oriented Programming",
         "A derived class inherits members from its base class.",
         "True","False","","",
         "","class Dog : public Animal { }; inherits all public members.",
         1, 0, 10},

        {"C++ Object-Oriented Programming",
         "What symbol is used to inherit a class in C++?",
         "","","","",
         ":","class Dog : public Animal { }; — colon means inherits from.",
         2, 0, 15},

        {"C++ Object-Oriented Programming",
         "Which concept allows one interface to have multiple implementations?",
         "Encapsulation","Inheritance","Polymorphism","Abstraction",
         "","Polymorphism: same function name, different behaviors.",
         0, 2, 10},

        {"C++ Object-Oriented Programming",
         "A destructor is called when an object goes out of scope.",
         "True","False","","",
         "","Destructor: ~MyClass() { } — releases resources automatically.",
         1, 0, 10},

        // ── C++ Advanced ──────────────────────────
        {"C++ Advanced Topics",
         "Which feature allows functions to work with any data type?",
         "Macros","Templates","Overloading","Namespaces",
         "","template<typename T> T add(T a, T b){ return a+b; }",
         0, 1, 10},

        {"C++ Advanced Topics",
         "Smart pointers automatically manage memory in C++.",
         "True","False","","",
         "","unique_ptr, shared_ptr prevent memory leaks automatically.",
         1, 0, 10},

        {"C++ Advanced Topics",
         "What does STL stand for?",
         "","","","",
         "Standard Template Library",
         "STL provides vector, map, sort, and many other tools.",
         2, 0, 20},

        {"C++ Advanced Topics",
         "Which smart pointer allows only ONE owner of a resource?",
         "shared_ptr","weak_ptr","unique_ptr","auto_ptr",
         "","unique_ptr cannot be copied — only moved.",
         0, 2, 10},

        {"C++ Advanced Topics",
         "std::vector automatically resizes when elements are added.",
         "True","False","","",
         "","vector is a dynamic array — push_back() grows it as needed.",
         1, 0, 10},

        {"C++ Advanced Topics",
         "What C++11 keyword lets the compiler deduce variable types?",
         "","","","",
         "auto","auto x = 3.14; — compiler figures out x is double.",
         2, 0, 15},

        {"C++ Advanced Topics",
         "Which container provides O(1) average-case lookup?",
         "vector","list","unordered_map","deque",
         "","unordered_map uses hashing for near-instant key lookup.",
         0, 2, 10},

        {"C++ Advanced Topics",
         "Lambda functions were introduced in C++11.",
         "True","False","","",
         "","auto f = [](int x){ return x*2; }; is a lambda.",
         1, 0, 10},

        // ── Python Basics ─────────────────────────
        {"Python Basics",
         "In Python, indentation defines code blocks.",
         "True","False","","",
         "","Python uses spaces instead of curly braces {}.",
         1, 0, 10},

        {"Python Basics",
         "What built-in function prints output in Python?",
         "","","","",
         "print","print('Hello, World!') displays text.",
         2, 0, 10},

        {"Python Basics",
         "Python variables must be declared with a type keyword.",
         "True","False","","",
         "","Python is dynamically typed — just write x = 5.",
         1, 1, 10},

        {"Python Basics",
         "Which symbol starts a comment in Python?",
         "//","#","--","/*",
         "","# This is a comment — Python ignores it.",
         0, 1, 10},

        {"Python Basics",
         "What does len('Python') return?",
         "","","","",
         "6","len() counts the characters. 'Python' has 6.",
         2, 0, 15},

        {"Python Basics",
         "Python lists can contain elements of different types.",
         "True","False","","",
         "","[1, 'hello', 3.14, True] is a perfectly valid list.",
         1, 0, 10},

        {"Python Basics",
         "Which operator is used for exponentiation in Python?",
         "*","^","**","^^",
         "","2**10 = 1024. Python uses ** not ^ for powers.",
         0, 2, 10},

        {"Python Basics",
         "What keyword starts a function definition in Python?",
         "","","","",
         "def","def greet(name): print('Hello', name)",
         2, 0, 10},

        // ── Python Functions & Modules ────────────
        {"Python Fundamentals & Modules",
         "What keyword defines a function in Python?",
         "function","def","func","define",
         "","def my_function(param): body",
         0, 1, 10},

        {"Python Fundamentals & Modules",
         "A Python function can return multiple values.",
         "True","False","","",
         "","def swap(a,b): return b,a returns a tuple.",
         1, 0, 10},

        {"Python Fundamentals & Modules",
         "What keyword imports a module in Python?",
         "","","","",
         "import","import math — then use math.sqrt(16)",
         2, 0, 10},

        {"Python Fundamentals & Modules",
         "What does the return keyword do?",
         "Ends the program","Prints a value",
         "Sends a value back to the caller","Repeats the function",
         "","return result exits the function with a value.",
         0, 2, 10},

        {"Python Fundamentals & Modules",
         "Default parameter values are assigned with =.",
         "True","False","","",
         "","def greet(name='World'): — name defaults to World.",
         1, 0, 10},

        {"Python Fundamentals & Modules",
         "Which built-in function opens a file in Python?",
         "","","","",
         "open","with open('file.txt', 'r') as f: data = f.read()",
         2, 0, 15},

        {"Python Fundamentals & Modules",
         "What does *args allow in a Python function?",
         "Named arguments","Variable number of positional arguments",
         "Default values","Module imports",
         "","def func(*args): — args is a tuple of all passed values.",
         0, 1, 10},

        {"Python Fundamentals & Modules",
         "try and except are used for error handling in Python.",
         "True","False","","",
         "","try: risky() except ValueError as e: handle(e)",
         1, 0, 10},

        // ── Data Structures ───────────────────────
        {"Data Structures in C++",
         "An array stores elements at contiguous memory locations.",
         "True","False","","",
         "","Contiguous memory means elements sit right next to each other.",
         1, 0, 10},

        {"Data Structures in C++",
         "Which data structure follows LIFO order?",
         "Queue","Stack","Linked List","Tree",
         "","Stack: Last In First Out — like a stack of plates.",
         0, 1, 10},

        {"Data Structures in C++",
         "What does FIFO stand for?",
         "","","","",
         "First In First Out","Queues process elements in arrival order.",
         2, 0, 15},

        {"Data Structures in C++",
         "A linked list uses contiguous memory like arrays.",
         "True","False","","",
         "","Linked list nodes can be anywhere in memory — connected by pointers.",
         1, 1, 10},

        {"Data Structures in C++",
         "Which STL container implements a stack in C++?",
         "vector","queue","stack","deque",
         "","std::stack<int> s; s.push(5); s.pop();",
         0, 2, 10},

        {"Data Structures in C++",
         "What is the time complexity of array index access?",
         "","","","",
         "O(1)","arr[i] is always instant regardless of array size.",
         2, 0, 20},

        {"Data Structures in C++",
         "A binary tree node has at most two children.",
         "True","False","","",
         "","Binary tree: left child and right child — maximum two.",
         1, 0, 10},

        {"Data Structures in C++",
         "Which structure always gives the highest priority element first?",
         "Stack","Queue","Priority Queue","Deque",
         "","priority_queue always pops the largest element first.",
         0, 2, 10},

        // ── Algorithms ────────────────────────────
        {"Algorithms & Complexity",
         "What does Big-O notation measure?",
         "Code style","Memory only",
         "Growth rate of time or space","Number of bugs",
         "","Big-O describes how performance scales with input size.",
         0, 2, 10},

        {"Algorithms & Complexity",
         "Binary search requires the array to be sorted.",
         "True","False","","",
         "","Binary search splits the sorted array in half each step.",
         1, 0, 10},

        {"Algorithms & Complexity",
         "What is the Big-O time complexity of binary search?",
         "","","","",
         "O(log n)","Each step halves the search space — logarithmic.",
         2, 0, 20},

        {"Algorithms & Complexity",
         "Which sorting algorithm guarantees O(n log n) in all cases?",
         "Bubble Sort","Quick Sort","Merge Sort","Selection Sort",
         "","Merge sort is always O(n log n) — even worst case.",
         0, 2, 10},

        {"Algorithms & Complexity",
         "Recursion must have a base case to avoid infinite loops.",
         "True","False","","",
         "","Without a base case, recursion causes a stack overflow.",
         1, 0, 10},

        {"Algorithms & Complexity",
         "What is the worst-case complexity of bubble sort?",
         "","","","",
         "O(n²)","Bubble sort compares every pair — very slow for large n.",
         2, 0, 20},

        {"Algorithms & Complexity",
         "Which algorithm divides the problem into subproblems and stores results?",
         "Greedy","Brute Force","Dynamic Programming","Recursion",
         "","DP memoizes results to avoid redundant computation.",
         0, 2, 10},

        {"Algorithms & Complexity",
         "Dijkstra's algorithm finds the shortest path in a graph.",
         "True","False","","",
         "","Dijkstra works on weighted graphs with non-negative edges.",
         1, 0, 10},

        // ── Python for Data Science ───────────────
        {"Python for Data Science",
         "NumPy stands for Numerical Python.",
         "True","False","","",
         "","NumPy provides fast array operations for scientific computing.",
         1, 0, 10},

        {"Python for Data Science",
         "What function creates a NumPy array from a Python list?",
         "","","","",
         "np.array","np.array([1,2,3]) creates a fast numeric array.",
         2, 0, 15},

        {"Python for Data Science",
         "Which library provides the DataFrame structure?",
         "NumPy","Matplotlib","Pandas","SciPy",
         "","import pandas as pd — df = pd.DataFrame(data)",
         0, 2, 10},

        {"Python for Data Science",
         "A Pandas DataFrame is a 2D labeled data structure.",
         "True","False","","",
         "","DataFrames have rows and named columns like a spreadsheet.",
         1, 0, 10},

        {"Python for Data Science",
         "What Pandas function reads a CSV file into a DataFrame?",
         "","","","",
         "pd.read_csv","df = pd.read_csv('data.csv') loads the file.",
         2, 0, 15},

        {"Python for Data Science",
         "Which NumPy function computes the average of an array?",
         "np.sum","np.mean","np.avg","np.total",
         "","np.mean([1,2,3,4,5]) returns 3.0",
         0, 1, 10},

        {"Python for Data Science",
         "df.dropna() removes rows that contain missing values.",
         "True","False","","",
         "","NaN values are dropped — use df.fillna(0) to replace instead.",
         1, 0, 10},

        {"Python for Data Science",
         "What Pandas method shows basic statistics of a DataFrame?",
         "","","","",
         "describe","df.describe() shows count, mean, std, min, max.",
         2, 0, 15},
        };

QSqlQuery q(m_db);
q.prepare(R"(
        INSERT INTO questions
            (course_id, type, text,
             option_0, option_1, option_2, option_3,
             correct_index, correct_answer,
             explanation, xp_reward)
        VALUES
            (:cid, :tp, :txt,
             :o0, :o1, :o2, :o3,
             :ci, :ca, :ex, :xp)
    )");

int seeded = 0;
for (const QData& d : questions) {
    int cid = getCourseId(d.course);
    if (cid < 0) continue;
    q.bindValue(":cid", cid);
    q.bindValue(":tp",  d.type);
    q.bindValue(":txt", d.text);
    q.bindValue(":o0",  d.o0);
    q.bindValue(":o1",  d.o1);
    q.bindValue(":o2",  d.o2);
    q.bindValue(":o3",  d.o3);
    q.bindValue(":ci",  d.correctIndex);
    q.bindValue(":ca",  d.correctAnswer);
    q.bindValue(":ex",  d.explanation);
    q.bindValue(":xp",  d.xp);
    if (q.exec()) seeded++;
    else qDebug() << "Q seed error:" << q.lastError().text()
                 << d.text.left(30);
}
qDebug() << "Questions seeded:" << seeded
         << "/" << questions.size();
}


// ── getLessonsForCourse ───────────────────────────────────────
QList<databasemanager::LessonContent>
databasemanager::getLessonsForCourse(int courseId)
{
    QList<LessonContent> list;
    QSqlQuery q(m_db);
    q.prepare(R"(
        SELECT id, course_id, order_num, title, content
        FROM lessons
        WHERE course_id=:cid
        ORDER BY order_num
    )");
    q.bindValue(":cid", courseId);
    if (!q.exec()) {
        qDebug() << "getLessonsForCourse error:"
                 << q.lastError().text();
        return list;
    }
    while (q.next()) {
        LessonContent l;
        l.id       = q.value(0).toInt();
        l.courseId = q.value(1).toInt();
        l.orderNum = q.value(2).toInt();
        l.title    = q.value(3).toString();
        l.content  = q.value(4).toString();
        list.append(l);
    }
    qDebug() << "Loaded" << list.size()
             << "lessons for courseId" << courseId;
    return list;
}

// ── seedLessons ───────────────────────────────────────────────
void databasemanager::seedLessons()
{
    QSqlQuery check(m_db);
    check.exec("SELECT COUNT(*) FROM lessons");
    if (check.next() && check.value(0).toInt() > 0) return;

    auto getCourseId = [this](const QString& title) -> int {
        QSqlQuery q(m_db);
        q.prepare("SELECT id FROM courses WHERE title=:t");
        q.bindValue(":t", title);
        q.exec();
        return q.next() ? q.value(0).toInt() : -1;
    };

    struct LData {
        QString course, title, content;
        int order;
    };

    QList<LData> lessons = {

        // ── C++ Fundamentals ─────────────────────────────────
        {"C++ Fundamentals", "Introduction to C++",
R"(WHAT IS C++?
C++ is a powerful general-purpose programming language created by Bjarne Stroustrup in 1979.

C++ is used for:
  - Operating systems (Windows, Linux)
  - Game engines (Unreal Engine)
  - Databases (MySQL)
  - Browsers (Chrome)

YOUR FIRST PROGRAM:

    #include <iostream>
    using namespace std;

    int main() {
        cout << "Hello, World!" << endl;
        return 0;
    }

HOW IT WORKS:
  - #include <iostream>  imports input/output tools
  - main()               entry point of every program
  - cout <<              prints text to the screen
  - return 0             tells the OS the program succeeded)", 1},

        {"C++ Fundamentals", "Variables and Data Types",
R"(WHAT IS A VARIABLE?
A variable is a named container that stores data in memory.

    int age = 25;
    // int = type,  age = name,  25 = value

MAIN DATA TYPES:

    int    score = 100;       whole numbers
    double price = 9.99;      decimal numbers
    char   grade = 'A';       single character
    bool   ok    = true;      true or false
    string name  = "Ahmed";   text (#include <string>)

NAMING RULES:
  - Must start with a letter or underscore
  - No spaces — use camelCase: firstName
  - Cannot be a keyword (int, class, return...)
  - Case-sensitive: age and Age are DIFFERENT)", 2},

        {"C++ Fundamentals", "Operators",
R"(ARITHMETIC OPERATORS:
    int a = 10, b = 3;
    a + b   // 13  addition
    a - b   // 7   subtraction
    a * b   // 30  multiplication
    a / b   // 3   integer division
    a % b   // 1   modulo (remainder)

COMPARISON OPERATORS (return bool):
    a == b  // false   equal to
    a != b  // true    not equal
    a > b   // true    greater than
    a < b   // false   less than

LOGICAL OPERATORS:
    true && false  // false  AND
    true || false  // true   OR
    !true          // false  NOT

ASSIGNMENT OPERATORS:
    int x = 5;
    x += 3;  // x = 8
    x -= 2;  // x = 6
    x++;     // x = 7   increment
    x--;     // x = 6   decrement)", 3},

        {"C++ Fundamentals", "Control Flow — if/else",
R"(MAKING DECISIONS:

    int score = 85;

    if (score >= 90) {
        cout << "Grade: A";
    } else if (score >= 80) {
        cout << "Grade: B";
    } else if (score >= 70) {
        cout << "Grade: C";
    } else {
        cout << "Grade: F";
    }

SWITCH STATEMENT:

    int day = 3;
    switch (day) {
        case 1: cout << "Monday";    break;
        case 2: cout << "Tuesday";   break;
        case 3: cout << "Wednesday"; break;
        default: cout << "Other";
    }

IMPORTANT: Always use break in switch cases!)", 4},

        {"C++ Fundamentals", "Loops",
R"(FOR LOOP — when you know how many times:

    for (int i = 0; i < 5; i++) {
        cout << i << " ";
    }
    // Output: 0 1 2 3 4

WHILE LOOP — while condition is true:

    int count = 0;
    while (count < 3) {
        cout << "Hello!" << endl;
        count++;
    }

DO-WHILE — always runs at least once:

    int num;
    do {
        cin >> num;
    } while (num <= 0);

BREAK and CONTINUE:

    for (int i = 0; i < 10; i++) {
        if (i == 5) break;        // stops the loop
        if (i % 2 == 0) continue; // skips even numbers
        cout << i << " ";
    }
    // Output: 1 3)", 5},

        {"C++ Fundamentals", "Functions",
R"(WHAT IS A FUNCTION?
A reusable block of code that performs a specific task.

DEFINING AND CALLING:

    int add(int a, int b) {
        return a + b;
    }

    int main() {
        int result = add(3, 5);
        cout << result;   // 8
    }

VOID FUNCTIONS (no return value):

    void greet(string name) {
        cout << "Hello, " << name << "!" << endl;
    }

    greet("Ahmed");   // Hello, Ahmed!

DEFAULT PARAMETERS:

    void greet(string name = "World") {
        cout << "Hello, " << name << "!";
    }

    greet();          // Hello, World!
    greet("Fatima");  // Hello, Fatima!)", 6},

        {"C++ Fundamentals", "Arrays and Strings",
R"(ARRAYS — multiple values of the same type:

    int scores[5] = {90, 85, 78, 92, 88};

    cout << scores[0];   // 90  first element
    cout << scores[4];   // 88  last element

    // Loop through array:
    for (int i = 0; i < 5; i++) {
        cout << scores[i] << " ";
    }

    // Modern range-for:
    for (int s : scores) {
        cout << s << " ";
    }

STRINGS:

    #include <string>
    string name = "Langora";

    cout << name.length();      // 7
    cout << name[0];            // L
    cout << name.substr(0, 4);  // Lang
    name += " App";             // Langora App

    if (name == "Langora App") cout << "Match!";)", 7},

        {"C++ Fundamentals", "Pointers and References",
R"(POINTERS — store memory addresses:

    int x = 42;
    int* ptr = &x;   // ptr holds address of x

    cout << x;       // 42    the value
    cout << ptr;     // memory address
    cout << *ptr;    // 42    dereference

    *ptr = 100;      // changes x to 100
    cout << x;       // 100

REFERENCES — alias for a variable:

    int y = 10;
    int& ref = y;   // ref IS y

    ref = 50;
    cout << y;      // 50   y changed!

PASS BY REFERENCE:

    void doubleIt(int& val) {
        val = val * 2;
    }

    int num = 5;
    doubleIt(num);
    cout << num;    // 10   num was modified!)", 8},

        // ── Python Basics ─────────────────────────────────────
        {"Python Basics", "Introduction to Python",
R"(WHAT IS PYTHON?
Python is a beginner-friendly language created by Guido van Rossum in 1991.

YOUR FIRST PROGRAM:

    print("Hello, World!")

That is the ENTIRE program! Python is simple.

COMMENTS:

    # This is a single-line comment

    """
    This is a
    multi-line comment
    """

RUNNING PYTHON:
  - Python files end in .py
  - Run with: python filename.py
  - Or use interactive mode: type python in terminal

WHY PYTHON?
  - Simple, clean syntax — reads like English
  - Used in AI, data science, web, automation
  - Massive library ecosystem (NumPy, Django...)
  - Most popular language in the world)", 1},

        {"Python Basics", "Variables and Types",
R"(VARIABLES — no type declaration needed:

    name       = "Ahmed"   # str
    age        = 25        # int
    height     = 1.80      # float
    is_student = True      # bool

CHECK THE TYPE:

    print(type(name))    # <class 'str'>
    print(type(age))     # <class 'int'>

TYPE CONVERSION:

    x   = "42"
    num = int(x)          # "42" -> 42
    txt = str(100)        # 100  -> "100"
    dec = float("3.14")   # string -> float

STRING OPERATIONS:

    name = "Python"
    print(len(name))      # 6
    print(name.upper())   # PYTHON
    print(name[0])        # P   indexing
    print(name[-1])       # n   last character
    print(name[0:3])      # Pyt slicing

F-STRINGS:

    age = 25
    print(f"I am {age} years old")   # I am 25 years old)", 2},

        {"Python Basics", "Lists and Collections",
R"(LISTS — ordered changeable collections:

    fruits  = ["apple", "banana", "cherry"]
    numbers = [1, 2, 3, 4, 5]
    mixed   = [1, "hello", True, 3.14]   # any types!

ACCESSING:

    print(fruits[0])    # apple
    print(fruits[-1])   # cherry  (last)
    print(fruits[1:3])  # ['banana', 'cherry']

MODIFYING:

    fruits.append("mango")      # add to end
    fruits.insert(1, "grape")   # insert at index
    fruits.remove("banana")     # remove by value
    fruits.pop()                # remove last
    fruits.sort()               # sort
    print(len(fruits))          # length

DICTIONARIES — key:value pairs:

    person = {
        "name": "Ahmed",
        "age":  25
    }
    print(person["name"])         # Ahmed
    person["email"] = "a@b.com"   # add key)", 3},

        {"Python Basics", "Control Flow",
R"(IF/ELIF/ELSE — Python uses indentation:

    score = 85

    if score >= 90:
        print("Grade: A")
    elif score >= 80:
        print("Grade: B")
    elif score >= 70:
        print("Grade: C")
    else:
        print("Grade: F")

LOGICAL OPERATORS:

    if age >= 18 and has_id:
        print("Access granted")

    if is_student or is_teacher:
        print("School member")

TERNARY (one-line if):

    status = "adult" if age >= 18 else "minor"

IN OPERATOR:

    fruits = ["apple", "banana", "cherry"]
    if "apple" in fruits:
        print("Found it!")", 4},

        {"Python Basics", "Loops in Python",
R"(FOR LOOP:

    for i in range(5):
        print(i)   # 0 1 2 3 4

    for i in range(1, 6):
        print(i)   # 1 2 3 4 5

ITERATING COLLECTIONS:

    fruits = ["apple", "banana", "cherry"]
    for fruit in fruits:
        print(fruit)

    for i, fruit in enumerate(fruits):
        print(f"{i}: {fruit}")

WHILE LOOP:

    count = 0
    while count < 5:
        print(count)
        count += 1

BREAK and CONTINUE:

    for i in range(10):
        if i == 5:
            break          # stop at 5
        if i % 2 == 0:
            continue       # skip even
        print(i)           # prints: 1 3)", 5},

        {"Python Basics", "Functions in Python",
R"(DEFINING FUNCTIONS:

    def greet(name):
        return f"Hello, {name}!"

    message = greet("Ahmed")
    print(message)     # Hello, Ahmed!

DEFAULT PARAMETERS:

    def greet(name="World"):
        print(f"Hello, {name}!")

    greet()            # Hello, World!
    greet("Fatima")    # Hello, Fatima!

MULTIPLE RETURN VALUES:

    def min_max(numbers):
        return min(numbers), max(numbers)

    low, high = min_max([3, 1, 8, 2, 5])
    print(low, high)   # 1 8

LAMBDA:

    square = lambda x: x ** 2
    print(square(5))   # 25)", 6},

        {"Python Basics", "Input, Output and Modules",
R"(USER INPUT:

    name = input("Enter your name: ")
    print(f"Hello, {name}!")

    age   = int(input("Enter your age: "))
    price = float(input("Enter price: "))

IMPORTING MODULES:

    import math
    print(math.sqrt(16))       # 4.0
    print(math.pi)             # 3.14159...

    import random
    print(random.randint(1, 10))
    print(random.choice(["a","b","c"]))

SELECTIVE IMPORTS:

    from math import sqrt, pi
    print(sqrt(25))            # 5.0 — no math. needed

USEFUL BUILT-INS:

    print(abs(-5))         # 5
    print(max(1, 5, 3))    # 5
    print(min(1, 5, 3))    # 1
    print(sum([1,2,3]))    # 6
    print(round(3.7))      # 4
    print(sorted([3,1,2])) # [1, 2, 3])", 7},

        // ── C++ OOP ───────────────────────────────────────────
        {"C++ Object-Oriented Programming", "Classes and Objects",
R"(WHAT IS OOP?
Organizes code around objects that have data and behavior.

DEFINING A CLASS:

    class Car {
    public:
        string brand;
        int    year;

        void honk() {
            cout << brand << ": Beep!" << endl;
        }
    };

CREATING OBJECTS:

    Car myCar;
    myCar.brand = "Toyota";
    myCar.year  = 2022;
    myCar.honk();   // Toyota: Beep!

CONSTRUCTOR (initializes automatically):

    class Car {
    public:
        string brand;
        int    year;

        Car(string b, int y) {
            brand = b;
            year  = y;
        }
    };

    Car myCar("Toyota", 2022);
    cout << myCar.brand;   // Toyota)", 1},

        {"C++ Object-Oriented Programming", "Encapsulation",
R"(HIDING INTERNAL STATE:

    class BankAccount {
    private:
        double balance;   // hidden from outside

    public:
        BankAccount(double initial) {
            balance = initial;
        }

        void deposit(double amount) {
            if (amount > 0)
                balance += amount;
        }

        void withdraw(double amount) {
            if (amount > 0 && amount <= balance)
                balance -= amount;
        }

        double getBalance() {
            return balance;   // controlled access
        }
    };

USING IT:

    BankAccount acc(1000.0);
    acc.deposit(500);
    acc.withdraw(200);
    cout << acc.getBalance();   // 1300

    // acc.balance = -999;  ERROR! balance is private)", 2},

        {"C++ Object-Oriented Programming", "Inheritance",
R"(REUSING CODE FROM PARENT CLASS:

    class Animal {
    public:
        string name;
        void eat()   { cout << name << " is eating."; }
        void sleep() { cout << name << " is sleeping."; }
    };

    class Dog : public Animal {
    public:
        void bark() {
            cout << name << " says: Woof!";
        }
    };

    class Cat : public Animal {
    public:
        void meow() {
            cout << name << " says: Meow!";
        }
    };

USING INHERITANCE:

    Dog dog;
    dog.name = "Rex";
    dog.eat();    // from Animal — Rex is eating.
    dog.bark();   // from Dog   — Rex says: Woof!

    Cat cat;
    cat.name = "Whiskers";
    cat.sleep();  // from Animal
    cat.meow();   // from Cat)", 3},

        {"C++ Object-Oriented Programming", "Polymorphism",
R"(MANY FORMS — same name, different behavior.

FUNCTION OVERLOADING (compile-time):

    class Calculator {
    public:
        int    add(int a, int b)       { return a+b; }
        double add(double a, double b) { return a+b; }
        int    add(int a, int b, int c){ return a+b+c; }
    };

    Calculator calc;
    calc.add(2, 3);      // int version -> 5
    calc.add(2.5, 3.5);  // double version -> 6.0

VIRTUAL FUNCTIONS (run-time):

    class Shape {
    public:
        virtual double area() { return 0; }
    };

    class Circle : public Shape {
        double r;
    public:
        Circle(double r) : r(r) {}
        double area() override {
            return 3.14159 * r * r;
        }
    };

    class Rectangle : public Shape {
        double w, h;
    public:
        Rectangle(double w, double h):w(w),h(h){}
        double area() override { return w * h; }
    };

    Shape* s1 = new Circle(5.0);
    Shape* s2 = new Rectangle(4.0, 6.0);
    cout << s1->area();   // 78.54
    cout << s2->area();   // 24)", 4},

        // ── Data Structures ───────────────────────────────────
        {"Data Structures in C++", "Arrays and Vectors",
R"(ARRAYS — fixed-size sequential containers:

    int arr[5] = {10, 20, 30, 40, 50};
    cout << arr[2];   // 30   O(1) access

VECTORS — dynamic arrays:

    #include <vector>
    vector<int> v = {1, 2, 3, 4, 5};

    v.push_back(6);            // add to end   O(1)
    v.pop_back();              // remove last  O(1)
    v.insert(v.begin()+2, 99); // at index 2  O(n)
    v.erase(v.begin()+1);      // at index 1  O(n)

    cout << v.size();    // element count
    cout << v.front();   // first element
    cout << v.back();    // last element

    for (int x : v) cout << x << " ";

    #include <algorithm>
    sort(v.begin(), v.end());   // sort in-place

COMPLEXITY:
    Access by index : O(1)  instant
    Search          : O(n)  linear
    Insert at end   : O(1)  fast
    Insert at middle: O(n)  slow)", 1},

        {"Data Structures in C++", "Linked Lists",
R"(NODES CONNECTED BY POINTERS:

    [10|->] -> [20|->] -> [30|->] -> null

NODE STRUCTURE:

    struct Node {
        int   data;
        Node* next;
        Node(int val) : data(val), next(nullptr) {}
    };

BUILDING A LIST:

    Node* head = new Node(10);
    head->next = new Node(20);
    head->next->next = new Node(30);

TRAVERSING:

    Node* cur = head;
    while (cur != nullptr) {
        cout << cur->data << " ";
        cur = cur->next;
    }   // 10 20 30

INSERT AT FRONT — O(1):

    Node* newNode = new Node(5);
    newNode->next = head;
    head = newNode;   // 5 10 20 30

ARRAY vs LINKED LIST:
    Insert at front : Array O(n), List O(1)
    Access by index : Array O(1), List O(n))", 2},

        {"Data Structures in C++", "Stacks and Queues",
R"(STACK — Last In First Out (LIFO):

    #include <stack>
    stack<int> s;
    s.push(10);
    s.push(20);
    s.push(30);

    cout << s.top();   // 30  peek
    s.pop();           // removes 30
    cout << s.top();   // 20
    cout << s.size();  // 2

USES: browser back button, undo, call stack

QUEUE — First In First Out (FIFO):

    #include <queue>
    queue<int> q;
    q.push(10);   // enqueue
    q.push(20);
    q.push(30);

    cout << q.front(); // 10  first element
    q.pop();           // removes 10
    cout << q.front(); // 20

USES: print queue, CPU scheduling, BFS

PRIORITY QUEUE:

    priority_queue<int> pq;
    pq.push(30); pq.push(10); pq.push(50);
    cout << pq.top();  // 50  always maximum!)", 3},

        {"Data Structures in C++", "Trees and Maps",
R"(BINARY SEARCH TREE (BST):

        50
       /  \
      30   70
     / \   / \
    20 40 60  80

Left < Node < Right

SEARCH: O(log n) average

STL MAP — sorted key-value pairs O(log n):

    #include <map>
    map<string, int> scores;
    scores["Ahmed"]  = 95;
    scores["Fatima"] = 88;
    scores["Karim"]  = 91;

    cout << scores["Ahmed"];   // 95

    for (auto& [name, score] : scores)
        cout << name << ": " << score << endl;
    // Output sorted by name!

UNORDERED_MAP — O(1) average with hashing:

    #include <unordered_map>
    unordered_map<string, int> freq;
    freq["apple"]++;
    freq["banana"]++;
    freq["apple"]++;
    cout << freq["apple"];   // 2)", 4},

        // ── Algorithms ────────────────────────────────────────
        {"Algorithms & Complexity", "Big-O Notation",
R"(HOW PERFORMANCE SCALES WITH INPUT SIZE n:

    O(1)      Constant    — always same speed
    O(log n)  Logarithmic — halves each step
    O(n)      Linear      — one op per item
    O(n log n)             — efficient sorting
    O(n^2)    Quadratic   — loop inside loop
    O(2^n)    Exponential — doubles each step

EXAMPLE — input n = 1,000,000:

    O(1)       ->         1 operation
    O(log n)   ->        20 operations
    O(n)       -> 1,000,000 operations
    O(n^2)     -> 10^12 operations (unusable!)

O(1) EXAMPLE:

    int getFirst(vector<int>& v) { return v[0]; }

O(n) EXAMPLE:

    for (int x : arr) sum += x;

O(n^2) EXAMPLE:

    for (int i : arr)
        for (int j : arr)   // nested loops!
            process(i, j);)", 1},

        {"Algorithms & Complexity", "Sorting Algorithms",
R"(BUBBLE SORT — O(n^2) — simple but slow:

    void bubbleSort(vector<int>& arr) {
        for (int i = 0; i < arr.size()-1; i++)
            for (int j = 0; j < arr.size()-i-1; j++)
                if (arr[j] > arr[j+1])
                    swap(arr[j], arr[j+1]);
    }

MERGE SORT — O(n log n) — divide and conquer:

    Split:  [8,3,5,1] -> [8,3] [5,1]
    Sort:             -> [3,8] [1,5]
    Merge:            -> [1,3,5,8]

QUICK SORT — O(n log n) average:
Pick a pivot, partition around it, recurse.

STL SORT — always use this in practice:

    #include <algorithm>
    vector<int> v = {5, 3, 8, 1, 9, 2};
    sort(v.begin(), v.end());
    // v = {1, 2, 3, 5, 8, 9}

    sort(v.rbegin(), v.rend());   // descending
    // v = {9, 8, 5, 3, 2, 1})", 2},

        {"Algorithms & Complexity", "Searching Algorithms",
R"(LINEAR SEARCH — O(n):

    int linearSearch(vector<int>& arr, int target) {
        for (int i = 0; i < arr.size(); i++)
            if (arr[i] == target) return i;
        return -1;   // not found
    }

Works on ANY array. Slow for large data.

BINARY SEARCH — O(log n) — SORTED array only:

    int binarySearch(vector<int>& arr, int target) {
        int left = 0, right = arr.size() - 1;
        while (left <= right) {
            int mid = (left + right) / 2;
            if (arr[mid] == target) return mid;
            if (arr[mid] < target)  left  = mid + 1;
            else                    right = mid - 1;
        }
        return -1;
    }

EXAMPLE — find 11 in [1,3,5,7,9,11,13]:

    Step 1: mid=3, arr[3]=7,  11>7 -> search right
    Step 2: mid=5, arr[5]=11  FOUND at index 5!

STL:

    #include <algorithm>
    vector<int> v = {1,3,5,7,9};
    bool found = binary_search(v.begin(),v.end(),7);)", 3},

        {"Algorithms & Complexity", "Recursion and Dynamic Programming",
R"(RECURSION — function calls itself:

    int factorial(int n) {
        if (n == 0) return 1;        // BASE CASE
        return n * factorial(n - 1); // RECURSIVE
    }

    factorial(4) = 4 * 3 * 2 * 1 * 1 = 24

FIBONACCI — naive O(2^n) very slow:

    int fib(int n) {
        if (n <= 1) return n;
        return fib(n-1) + fib(n-2);
    }
    // fib(3) computed MULTIPLE TIMES! Wasteful.

DYNAMIC PROGRAMMING — store results:

    int fib_dp(int n) {
        vector<int> dp(n+1, 0);
        dp[0] = 0;
        dp[1] = 1;
        for (int i = 2; i <= n; i++)
            dp[i] = dp[i-1] + dp[i-2];
        return dp[n];
    }
    // Each subproblem computed ONCE -> O(n)

USE DP WHEN:
  - Problem has overlapping subproblems
  - Optimal solution built from optimal sub-solutions)", 4},

        // ── Python Functions & Modules ────────────────────────
        {"Python Fundamentals & Modules", "Advanced Functions",
R"(SCOPE:

    x = 10   # global

    def my_func():
        y = 20   # local
        print(x)  # can access global
        # print(z) would be ERROR outside

GLOBAL KEYWORD:

    count = 0
    def increment():
        global count
        count += 1

    increment(); increment()
    print(count)   # 2

CLOSURES:

    def make_multiplier(factor):
        def multiply(x):
            return x * factor   # remembers factor!
        return multiply

    double = make_multiplier(2)
    triple = make_multiplier(3)
    print(double(5))   # 10
    print(triple(5))   # 15

*ARGS and **KWARGS:

    def total(*nums):
        return sum(nums)

    print(total(1, 2, 3, 4))   # 10)", 1},

        {"Python Fundamentals & Modules", "Modules and Packages",
R"(IMPORTING:

    import math
    print(math.sqrt(25))    # 5.0
    print(math.ceil(4.2))   # 5
    print(math.pi)          # 3.14159...

    import random
    print(random.randint(1, 100))

FROM IMPORT:

    from math import sqrt, pi
    print(sqrt(16))    # 4.0   no math. prefix

ALIASES:

    import numpy  as np
    import pandas as pd

CREATING YOUR OWN MODULE:

    # Save as utils.py:
    def add(a, b): return a + b
    PI = 3.14159

    # In another file:
    import utils
    print(utils.add(3, 5))   # 8
    print(utils.PI)           # 3.14159

STANDARD LIBRARY HIGHLIGHTS:
    os       — file system operations
    datetime — dates and times
    json     — read/write JSON
    re       — regular expressions
    sys      — system information)", 2},

        {"Python Fundamentals & Modules", "File Handling",
R"(READING FILES:

    with open("data.txt", "r") as f:
        content = f.read()        # entire file
        print(content)

    with open("data.txt", "r") as f:
        for line in f:
            print(line.strip())   # line by line

WRITING FILES:

    with open("output.txt", "w") as f:
        f.write("Hello, World!\n")
        f.write("Second line\n")

    with open("log.txt", "a") as f:
        f.write("New entry\n")    # append mode

CSV FILES:

    import csv

    with open("data.csv", "r") as f:
        reader = csv.reader(f)
        for row in reader:
            print(row)

    with open("out.csv", "w", newline="") as f:
        writer = csv.writer(f)
        writer.writerow(["Name", "Score"])
        writer.writerow(["Ahmed", 95])

ALWAYS use 'with' — file closes automatically!)", 3},

        {"Python Fundamentals & Modules", "Error Handling",
R"(TRY / EXCEPT:

    try:
        x = int(input("Enter number: "))
        result = 10 / x
        print(f"Result: {result}")
    except ValueError:
        print("That wasn't a number!")
    except ZeroDivisionError:
        print("Cannot divide by zero!")

MULTIPLE EXCEPT + ELSE + FINALLY:

    try:
        f = open("data.txt")
        data = f.read()
    except FileNotFoundError:
        print("File missing!")
    else:
        print("Success!")     # runs if no error
    finally:
        print("Always runs!") # cleanup

RAISING YOUR OWN ERRORS:

    def set_age(age):
        if age < 0 or age > 150:
            raise ValueError(f"Invalid age: {age}")

    try:
        set_age(-5)
    except ValueError as e:
        print(e)   # Invalid age: -5

COMMON EXCEPTIONS:
    ValueError        wrong type of value
    TypeError         wrong argument type
    IndexError        list index out of range
    KeyError          dict key not found
    FileNotFoundError file does not exist)", 4},

        // ── C++ Advanced ──────────────────────────────────────
        {"C++ Advanced Topics", "Templates",
R"(WRITE ONCE, USE FOR ANY TYPE:

    template<typename T>
    T maximum(T a, T b) {
        return (a > b) ? a : b;
    }

    cout << maximum(3, 7);          // 7    int
    cout << maximum(3.14, 2.71);    // 3.14 double
    cout << maximum('A', 'Z');      // Z    char

CLASS TEMPLATE:

    template<typename T>
    class Box {
    private:
        T value;
    public:
        Box(T val) : value(val) {}
        T get() { return value; }
    };

    Box<int>    intBox(42);
    Box<string> strBox("Hello");
    cout << intBox.get();    // 42
    cout << strBox.get();    // Hello

MULTIPLE TYPE PARAMETERS:

    template<typename K, typename V>
    class Pair {
    public:
        K key; V value;
    };

STL IS BUILT ON TEMPLATES:
    vector<int>    v1;   // vector of ints
    map<string,int> m;   // map with any types)", 1},

        {"C++ Advanced Topics", "STL Containers",
R"(VECTOR — dynamic array:

    vector<int> v = {3, 1, 4, 1, 5};
    v.push_back(9);
    sort(v.begin(), v.end());

MAP — sorted key-value O(log n):

    map<string, int> ages;
    ages["Ahmed"]  = 25;
    ages["Fatima"] = 22;
    for (auto& [name, age] : ages)
        cout << name << ": " << age << endl;

UNORDERED_MAP — hash O(1) average:

    unordered_map<string, int> freq;
    string text = "hello";
    for (char c : text) freq[c]++;

SET — unique sorted elements:

    set<int> s = {5, 3, 8, 3, 1, 5};
    // {1, 3, 5, 8}  duplicates removed!

STL ALGORITHMS:

    #include <algorithm>
    vector<int> v = {5, 2, 8, 1};
    sort(v.begin(), v.end());
    reverse(v.begin(), v.end());
    auto it = find(v.begin(), v.end(), 5);
    int sum = accumulate(v.begin(),v.end(), 0);)", 2},

        {"C++ Advanced Topics", "Smart Pointers",
R"(PROBLEM WITH RAW POINTERS:

    int* p = new int(42);
    // Forget delete p; -> MEMORY LEAK!

SMART POINTERS auto-manage memory.
    #include <memory>

UNIQUE_PTR — one owner only:

    auto p1 = make_unique<int>(42);
    cout << *p1;      // 42

    // Cannot copy — only move:
    auto p2 = move(p1);   // p1 is now null
    // Auto-deleted when p2 goes out of scope!

SHARED_PTR — shared ownership:

    auto sp1 = make_shared<int>(100);
    auto sp2 = sp1;   // both own it!

    cout << sp1.use_count();   // 2
    sp2.reset();               // releases
    cout << sp1.use_count();   // 1
    // Freed when LAST shared_ptr gone

WEAK_PTR — non-owning reference:

    weak_ptr<int> wp = sp1;   // no ownership

RULE: Always use smart pointers!
    unique_ptr — one owner
    shared_ptr — multiple owners)", 3},

        {"C++ Advanced Topics", "Modern C++11/17 Features",
R"(AUTO — type inference:

    auto x = 42;           // int
    auto y = 3.14;         // double
    auto v = vector<int>{1,2,3};

    for (auto& item : v) cout << item;

LAMBDA FUNCTIONS:

    auto square = [](int x) { return x * x; };
    cout << square(5);   // 25

    int factor = 3;
    auto multiply = [factor](int x) {
        return x * factor;
    };
    cout << multiply(7);   // 21

    // With STL:
    vector<int> v = {1,5,3,8,2};
    sort(v.begin(), v.end(),
         [](int a, int b){ return a > b; });

STRUCTURED BINDINGS (C++17):

    map<string,int> m = {{"A",95},{"B",87}};
    for (auto& [name, score] : m)
        cout << name << ": " << score << endl;

NULLPTR:

    int* p = nullptr;   // safe null pointer

CONSTEXPR:

    constexpr double PI = 3.14159265358979;)", 4},

        // ── Python for Data Science ───────────────────────────
        {"Python for Data Science", "NumPy Basics",
R"(WHAT IS NUMPY?
Fast, efficient arrays for mathematical computing.

    import numpy as np

CREATING ARRAYS:

    a = np.array([1, 2, 3, 4, 5])
    b = np.array([[1,2,3],[4,5,6]])  # 2D

    zeros = np.zeros(5)           # [0. 0. 0. 0. 0.]
    ones  = np.ones((2,3))        # 2x3 matrix of 1s
    rng   = np.arange(0, 10, 2)   # [0 2 4 6 8]

PROPERTIES:

    print(a.shape)   # (5,)    1D with 5 elements
    print(b.shape)   # (2, 3)  2 rows, 3 columns
    print(a.dtype)   # int64

VECTORIZED OPERATIONS:

    a = np.array([1, 2, 3, 4, 5])
    print(a + 10)    # [11 12 13 14 15]
    print(a * 2)     # [2 4 6 8 10]
    print(a ** 2)    # [1 4 9 16 25]

MATH FUNCTIONS:

    np.sum(a)    # 15
    np.mean(a)   # 3.0
    np.max(a)    # 5
    np.min(a)    # 1
    np.sqrt(a)   # [1. 1.41 1.73 2. 2.23])", 1},

        {"Python for Data Science", "Pandas DataFrames",
R"(WHAT IS PANDAS?
DataFrame is a 2D table — Python's Excel!

    import pandas as pd

CREATING:

    data = {
        "Name":  ["Ahmed", "Fatima", "Karim"],
        "Age":   [25, 22, 28],
        "Score": [95, 88, 91]
    }
    df = pd.DataFrame(data)

EXPLORING:

    df.head()        # first 5 rows
    df.shape         # (3, 3)
    df.columns       # column names
    df.describe()    # statistics

ACCESSING:

    df["Name"]              # entire column
    df[["Name","Score"]]    # multiple columns
    df.iloc[0]              # first row
    df.loc[df["Age"] > 23]  # filter rows

MODIFYING:

    df["Grade"] = ["A","B","A"]    # add column
    df["Score"] = df["Score"] + 5  # modify
    df.sort_values("Score", ascending=False)

MISSING VALUES:

    df.isnull().sum()   # count NaN per column
    df.dropna()         # remove NaN rows
    df.fillna(0)        # replace NaN with 0)", 2},

        {"Python for Data Science", "Data Cleaning",
R"(LOADING DATA:

    import pandas as pd

    df = pd.read_csv("students.csv")
    df = pd.read_excel("data.xlsx")
    df.to_csv("clean.csv", index=False)

EXPLORING:

    df.info()              # types and null counts
    df.describe()          # statistics
    df.isnull().sum()      # missing per column

HANDLING MISSING VALUES:

    df.dropna()                         # remove rows
    df.dropna(subset=["Score"])         # specific col

    df["Score"].fillna(df["Score"].mean(), inplace=True)
    df["Name"].fillna("Unknown", inplace=True)

REMOVING DUPLICATES:

    df.drop_duplicates(inplace=True)

FIXING TYPES:

    df["Age"] = pd.to_numeric(df["Age"], errors="coerce")

FILTERING:

    high  = df[df["Score"] >= 90]
    cpp   = df[df["Language"] == "C++"]
    combo = df[(df["Score"] > 80) & (df["Age"] < 30)]

STRING OPERATIONS:

    df["Name"] = df["Name"].str.strip()
    df["Name"] = df["Name"].str.lower())", 3},

        {"Python for Data Science", "Data Analysis",
R"(GROUPING:

    grouped = df.groupby("Language")["Score"].mean()
    # Language
    # C++    91.5
    # Python 87.3

    df.groupby("Language").agg({
        "Score": ["mean", "max", "min"]
    })

APPLY FUNCTIONS:

    df["Category"] = df["Score"].apply(
        lambda x: "A" if x >= 90 else
                  "B" if x >= 80 else "C"
    )

    def label(row):
        if row["Score"] >= 90:
            return f"{row['Name']} is excellent!"
        return f"{row['Name']} needs improvement"

    df["Label"] = df.apply(label, axis=1)

STATISTICS:

    df["Score"].mean()    # average
    df["Score"].median()  # middle value
    df["Score"].std()     # standard deviation

    df["Score"].corr(df["Age"])  # correlation

SAVING:

    df.to_csv("results.csv", index=False)
    summary = df.groupby("Language")["Score"].describe()
    summary.to_excel("summary.xlsx"))", 4},
    };  // end of lessons list

    QSqlQuery q(m_db);
    q.prepare(R"(
        INSERT INTO lessons (course_id, order_num, title, content)
        VALUES (:cid, :ord, :title, :content)
    )");

    int seeded = 0;
    for (const LData& l : lessons) {
        int cid = getCourseId(l.course);
        if (cid < 0) {
            qDebug() << "Lesson: course not found:" << l.course;
            continue;
        }
        q.bindValue(":cid",     cid);
        q.bindValue(":ord",     l.order);
        q.bindValue(":title",   l.title);
        q.bindValue(":content", l.content);
        if (q.exec()) seeded++;
        else qDebug() << "Lesson seed error:"
                      << q.lastError().text();
    }
    qDebug() << "Lessons seeded:" << seeded
             << "/" << lessons.size();
}

// ── getUserStreak ─────────────────────────────────────────────
int databasemanager::getUserStreak(const QString& username) {
    QSqlQuery q(m_db);
    q.prepare("SELECT streak FROM users WHERE username=:u");
    q.bindValue(":u", username.trimmed().toLower());
    q.exec();
    return q.next() ? q.value(0).toInt() : 0;
}

// ── updateStreak ──────────────────────────────────────────────
// Increments streak if last login was yesterday.
// Resets to 1 if more than 1 day gap.
// Does nothing if already logged in today.
void databasemanager::updateStreak(const QString& username) {
    // Get last login date and current streak
    QSqlQuery q(m_db);
    q.prepare("SELECT streak, last_login FROM users WHERE username=:u");
    q.bindValue(":u", username.trimmed().toLower());
    q.exec();

    if (!q.next()) return;

    int     currentStreak = q.value(0).toInt();
    QString lastLogin     = q.value(1).toString(); // "YYYY-MM-DD"
    QString today = QDate::currentDate().toString("yyyy-MM-dd");

    int newStreak = currentStreak;

    if (lastLogin.isEmpty()) {
        // First ever login
        newStreak = 1;
    } else if (lastLogin == today) {
        // Already logged in today — do nothing
        return;
    } else {
        QDate last = QDate::fromString(lastLogin, "yyyy-MM-dd");
        int daysDiff = last.daysTo(QDate::currentDate());
        if (daysDiff == 1) {
            newStreak = currentStreak + 1; // consecutive day!
        } else {
            newStreak = 1; // gap > 1 day — reset streak
        }
    }

    QSqlQuery upd(m_db);
    upd.prepare("UPDATE users SET streak=:s, last_login=:d "
                "WHERE username=:u");
    upd.bindValue(":s", newStreak);
    upd.bindValue(":d", today);
    upd.bindValue(":u", username.trimmed().toLower());
    upd.exec();

    qDebug() << "Streak updated to" << newStreak
             << "for" << username;
}

// ── markCourseStarted ─────────────────────────────────────────
void databasemanager::markCourseStarted(const QString& username,
                                         int courseId) {
    // Get user id
    QSqlQuery uid(m_db);
    uid.prepare("SELECT id FROM users WHERE username=:u");
    uid.bindValue(":u", username.trimmed().toLower());
    uid.exec();
    if (!uid.next()) return;
    int userId = uid.value(0).toInt();

    // Insert only if not already started
    QSqlQuery q(m_db);
    q.prepare(R"(
        INSERT OR IGNORE INTO user_progress
            (user_id, course_id, lessons_done, completed)
        VALUES (:uid, :cid, 0, 0)
    )");
    q.bindValue(":uid", userId);
    q.bindValue(":cid", courseId);
    q.exec();
}

// ── markCourseCompleted ───────────────────────────────────────
void databasemanager::markCourseCompleted(const QString& username,
                                           int courseId) {
    QSqlQuery uid(m_db);
    uid.prepare("SELECT id FROM users WHERE username=:u");
    uid.bindValue(":u", username.trimmed().toLower());
    uid.exec();
    if (!uid.next()) return;
    int userId = uid.value(0).toInt();

    // Upsert — insert if not exists, update if exists
    QSqlQuery q(m_db);
    q.prepare(R"(
        INSERT INTO user_progress
            (user_id, course_id, completed)
        VALUES (:uid, :cid, 1)
        ON CONFLICT(user_id, course_id)
        DO UPDATE SET completed=1
    )");
    q.bindValue(":uid", userId);
    q.bindValue(":cid", courseId);
    if (!q.exec())
        qDebug() << "markCourseCompleted error:"
                 << q.lastError().text();
}

// ── getCoursesStarted ─────────────────────────────────────────
int databasemanager::getCoursesStarted(const QString& username) {
    QSqlQuery uid(m_db);
    uid.prepare("SELECT id FROM users WHERE username=:u");
    uid.bindValue(":u", username.trimmed().toLower());
    uid.exec();
    if (!uid.next()) return 0;
    int userId = uid.value(0).toInt();

    QSqlQuery q(m_db);
    q.prepare("SELECT COUNT(*) FROM user_progress "
              "WHERE user_id=:uid");
    q.bindValue(":uid", userId);
    q.exec();
    return q.next() ? q.value(0).toInt() : 0;
}

// ── getUserProfile ────────────────────────────────────────────
databasemanager::UserProfile
databasemanager::getUserProfile(const QString& username)
{
    UserProfile p;
    QSqlQuery q(m_db);
    q.prepare(R"(
        SELECT first_name, last_name, username,
               email, xp, level, streak, created_at
        FROM users WHERE username=:u
    )");
    q.bindValue(":u", username.trimmed().toLower());
    q.exec();
    if (q.next()) {
        p.firstname  = q.value(0).toString();
        p.lastname   = q.value(1).toString();
        p.username   = q.value(2).toString();
        p.email      = q.value(3).toString();
        p.xp         = q.value(4).toInt();
        p.level      = q.value(5).toInt();
        p.streak     = q.value(6).toInt();
        // Format created_at to just the date part
        p.createdAt  = q.value(7).toString().left(10);
    }
    return p;
}

// ── updateProfile ─────────────────────────────────────────────
bool databasemanager::updateProfile(
    const QString& currentUsername,
    const QString& newFirstname,
    const QString& newLastname,
    const QString& newUsername,
    const QString& newEmail,
    const QString& currentPassword)
{
    // Verify current password first
    if (!loginuser(currentUsername, currentPassword)) {
        qDebug() << "updateProfile: wrong password";
        return false;
    }

    // Check if new username is taken by someone else
    QString newU = newUsername.trimmed().toLower();
    QString curU = currentUsername.trimmed().toLower();
    if (newU != curU && usernameexists(newU)) {
        qDebug() << "updateProfile: username taken";
        return false;
    }

    // Check if new email is taken by someone else
    QString newE = newEmail.trimmed().toLower();
    QSqlQuery checkE(m_db);
    checkE.prepare(
        "SELECT id FROM users WHERE email=:e AND username!=:u");
    checkE.bindValue(":e", newE);
    checkE.bindValue(":u", curU);
    checkE.exec();
    if (checkE.next()) {
        qDebug() << "updateProfile: email taken";
        return false;
    }

    QSqlQuery q(m_db);
    q.prepare(R"(
        UPDATE users
        SET first_name=:fn,
            last_name=:ln,
            username=:nu,
            email=:ne
        WHERE username=:cu
    )");
    q.bindValue(":fn", newFirstname.trimmed());
    q.bindValue(":ln", newLastname.trimmed());
    q.bindValue(":nu", newU);
    q.bindValue(":ne", newE);
    q.bindValue(":cu", curU);

    if (!q.exec()) {
        qDebug() << "updateProfile error:"
                 << q.lastError().text();
        return false;
    }
    qDebug() << "Profile updated for" << currentUsername;
    return true;
}

// ── changePassword ────────────────────────────────────────────
bool databasemanager::changePassword(
    const QString& username,
    const QString& currentPassword,
    const QString& newPassword)
{
    // Verify current password
    if (!loginuser(username, currentPassword)) {
        qDebug() << "changePassword: wrong current password";
        return false;
    }

    QSqlQuery q(m_db);
    q.prepare("UPDATE users SET password=:p WHERE username=:u");

    // Hash the new password
    QString hashed = QCryptographicHash::hash(
        newPassword.toUtf8(),
        QCryptographicHash::Sha256).toHex();

    q.bindValue(":p", hashed);
    q.bindValue(":u", username.trimmed().toLower());

    if (!q.exec()) {
        qDebug() << "changePassword error:"
                 << q.lastError().text();
        return false;
    }
    qDebug() << "Password changed for" << username;
    return true;
}
