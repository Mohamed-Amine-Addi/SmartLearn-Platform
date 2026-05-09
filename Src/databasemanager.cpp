#include "databasemanager.h"
#include <QCryptographicHash>

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
    if (!createTables()) return false;

    //Migrate: add last_login if not present
    QSqlQuery mig(m_db);
    mig.exec("ALTER TABLE users ADD COLUMN last_login TEXT DEFAULT ''");

    seedCourses();
    seedQuestions();
    seedLessons();
    return true;
    qDebug() << "Database opened:" << dbPath;
    if (!createTables()) return false;
    seedCourses();
    seedQuestions();
    return true;
}

bool databasemanager::createTables() {
    QSqlQuery q(m_db);

    //Users
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

    //User progress
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

    // Lessons table
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

    qDebug() << "All tables created successfully.";
    return true;
}

// ── Password hashing ─────────────────────────────────────────
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

bool databasemanager::registeruser(const QString& firstname, const QString& lastname, const QString& username, const QString& email, const QString& password) {
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

//User data
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
            q3.prepare("UPDATE users SET level=:l WHERE username=:u");
            q3.bindValue(":l", newLevel);
            q3.bindValue(":u", username.trimmed().toLower());
            q3.exec();
            qDebug() << "Level up! Now level" << newLevel;
        }
    }
}

//Courses
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
        qu.options      << q.value(3).toString()
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

//Progress
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

//Badges
bool databasemanager::hasBadge(const QString& username, const QString& key) {
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

bool databasemanager::awardBadge(const QString& username, const QString& key) {
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

//Seed courses
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
            qDebug() << "Seed course error:" << q.lastError().text();
    }
    qDebug() << "Courses seeded:" << courses.size();
}

//Seed questions
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

    //C++ Fundamentals
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
    else qDebug() << "Q seed error:" << q.lastError().text() << d.text.left(30);
}
qDebug() << "Questions seeded:" << seeded << "/" << questions.size();
}

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
    q.exec();
    while (q.next()) {
        LessonContent l;
        l.id       = q.value(0).toInt();
        l.courseId = q.value(1).toInt();
        l.orderNum = q.value(2).toInt();
        l.title    = q.value(3).toString();
        l.content  = q.value(4).toString();
        list.append(l);
    }
    qDebug() << "Loaded" << list.size() << "lessons for courseId" << courseId;
    return list;
}

void databasemanager::seedLessons() {
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

    // ══════════════════════════════════════════
    // C++ FUNDAMENTALS
    // ══════════════════════════════════════════
    {"C++ Fundamentals", "Introduction to C++", R"(
WHAT IS C++?
C++ is a powerful general-purpose programming language created by Bjarne Stroustrup in 1979. It extends the C language with object-oriented features.

C++ is used for:
- Operating systems (Windows, Linux)
- Game engines (Unreal Engine)
- Databases (MySQL)
- Browsers (Chrome)

YOUR FIRST PROGRAM:
Every C++ program starts with a main() function:

    #include <iostream>
    using namespace std;

    int main() {
        cout << "Hello, World!" << endl;
        return 0;
    }

HOW IT WORKS:
- #include <iostream> — imports input/output tools
- main() — the entry point of every program
- cout << — prints text to the screen
- return 0 — tells the OS the program succeeded
)", 1},

        {"C++ Fundamentals", "Variables and Data Types", R"(
WHAT IS A VARIABLE?
A variable is a named container that stores data in memory.

    int age = 25;
    // int = type, age = name, 25 = value

THE MAIN DATA TYPES:

int — whole numbers
    int score = 100;
    int temperature = -5;

double — decimal numbers
    double price = 9.99;
    double pi = 3.14159;

char — single character
    char grade = 'A';
    char symbol = '$';

bool — true or false
    bool isLoggedIn = true;
    bool hasError = false;

string — text (needs #include <string>)
    string name = "Ahmed";
    string city = "Algiers";

RULES FOR NAMING VARIABLES:
- Must start with a letter or underscore
- Cannot contain spaces — use camelCase: firstName
- Cannot be a C++ keyword (int, class, return...)
- Case-sensitive: age and Age are different!
)", 2},

        {"C++ Fundamentals", "Operators", R"(
ARITHMETIC OPERATORS:
    int a = 10, b = 3;
    cout << a + b;   // 13 — addition
    cout << a - b;   // 7  — subtraction
    cout << a * b;   // 30 — multiplication
    cout << a / b;   // 3  — integer division
    cout << a % b;   // 1  — modulo (remainder)

COMPARISON OPERATORS (return bool):
    a == b   // false — equal to
    a != b   // true  — not equal to
    a > b    // true  — greater than
    a < b    // false — less than
    a >= b   // true  — greater or equal
    a <= b   // false — less or equal

LOGICAL OPERATORS:
    true && false   // false — AND (both must be true)
    true || false   // true  — OR (one must be true)
    !true           // false — NOT (flips the value)

ASSIGNMENT OPERATORS:
    int x = 5;
    x += 3;   // x = x + 3 = 8
    x -= 2;   // x = x - 2 = 6
    x *= 4;   // x = x * 4 = 24
    x /= 6;   // x = x / 6 = 4
    x++;      // x = x + 1 = 5
    x--;      // x = x - 1 = 4
)", 3},

        {"C++ Fundamentals", "Control Flow — if/else", R"(
MAKING DECISIONS WITH IF/ELSE:
Programs need to make decisions based on conditions.

BASIC IF:
    int score = 85;
    if (score >= 60) {
        cout << "You passed!";
    }

IF/ELSE:
    if (score >= 60) {
        cout << "Pass";
    } else {
        cout << "Fail";
    }

IF/ELSE IF/ELSE:
    if (score >= 90) {
        cout << "Grade: A";
    } else if (score >= 80) {
        cout << "Grade: B";
    } else if (score >= 70) {
        cout << "Grade: C";
    } else {
        cout << "Grade: F";
    }

SWITCH STATEMENT (for multiple exact values):
    int day = 3;
    switch (day) {
        case 1: cout << "Monday";    break;
        case 2: cout << "Tuesday";   break;
        case 3: cout << "Wednesday"; break;
        default: cout << "Other day";
    }

IMPORTANT: Always use break in switch cases to
prevent fall-through to the next case!
)", 4},

        {"C++ Fundamentals", "Loops", R"(
REPEATING CODE WITH LOOPS:

FOR LOOP — when you know how many times to repeat:
    for (int i = 0; i < 5; i++) {
        cout << i << " ";
    }
    // Output: 0 1 2 3 4

    Structure: for (start; condition; step)

WHILE LOOP — repeats while condition is true:
    int count = 0;
    while (count < 3) {
        cout << "Hello!" << endl;
        count++;
    }

DO-WHILE — always runs at least once:
    int num;
    do {
        cin >> num;
    } while (num <= 0);   // keep asking until positive

BREAK AND CONTINUE:
    for (int i = 0; i < 10; i++) {
        if (i == 5) break;      // stops the loop at 5
        if (i % 2 == 0) continue; // skips even numbers
        cout << i << " ";
    }
    // Output: 1 3

NESTED LOOPS (loop inside a loop):
    for (int i = 1; i <= 3; i++) {
        for (int j = 1; j <= 3; j++) {
            cout << i * j << "\t";
        }
        cout << endl;
    }
)", 5},

        {"C++ Fundamentals", "Functions", R"(
WHAT IS A FUNCTION?
A function is a reusable block of code that performs a specific task.

DEFINING A FUNCTION:
    returnType functionName(parameters) {
        // code
        return value;
    }

EXAMPLE:
    int add(int a, int b) {
        return a + b;
    }

    int main() {
        int result = add(3, 5);   // Call the function
        cout << result;           // Output: 8
    }

VOID FUNCTIONS (no return value):
    void greet(string name) {
        cout << "Hello, " << name << "!" << endl;
    }

    greet("Ahmed");   // Output: Hello, Ahmed!

DEFAULT PARAMETERS:
    void greet(string name = "World") {
        cout << "Hello, " << name << "!";
    }

    greet();          // Hello, World!
    greet("Fatima");  // Hello, Fatima!

FUNCTION OVERLOADING — same name, different parameters:
    int multiply(int a, int b) { return a * b; }
    double multiply(double a, double b) { return a * b; }
    // C++ picks the right one based on argument types
)", 6},

        {"C++ Fundamentals", "Arrays and Strings", R"(
ARRAYS — storing multiple values of the same type:
    int scores[5] = {90, 85, 78, 92, 88};
    //       [0]   [1]  [2]  [3]  [4]   — indices

    cout << scores[0];   // 90 — first element
    cout << scores[4];   // 88 — last element

    // Modifying an element:
    scores[2] = 100;

ITERATING OVER AN ARRAY:
    for (int i = 0; i < 5; i++) {
        cout << scores[i] << " ";
    }

    // Modern C++ range-for:
    for (int s : scores) {
        cout << s << " ";
    }

2D ARRAYS (like a table):
    int matrix[2][3] = {
        {1, 2, 3},
        {4, 5, 6}
    };
    cout << matrix[1][2];   // 6

STRINGS — text in C++:
    #include <string>
    string name = "Langora";

    cout << name.length();      // 7
    cout << name[0];            // L
    cout << name.substr(0, 4);  // Lang
    name += " App";             // Langora App

    // Comparing strings:
    if (name == "Langora App") cout << "Match!";
)", 7},

        {"C++ Fundamentals", "Pointers and References", R"(
MEMORY AND ADDRESSES:
Every variable is stored at a memory address.
A pointer stores that address.

DECLARING A POINTER:
    int x = 42;
    int* ptr = &x;    // ptr holds the address of x

    cout << x;        // 42  — the value
    cout << &x;       // address (like 0x7fff...)
    cout << ptr;      // same address
    cout << *ptr;     // 42  — dereferencing (value at address)

MODIFYING THROUGH A POINTER:
    *ptr = 100;       // changes x to 100
    cout << x;        // 100

REFERENCES — an alias for a variable:
    int y = 10;
    int& ref = y;     // ref IS y, same memory

    ref = 50;
    cout << y;        // 50 — y changed through ref!

PASS BY REFERENCE (efficient function parameters):
    void doubleIt(int& val) {
        val = val * 2;
    }

    int num = 5;
    doubleIt(num);
    cout << num;      // 10 — num was modified!

WHY USE POINTERS?
- Dynamic memory allocation (new/delete)
- Efficient passing of large data
- Building data structures like linked lists
)", 8},

        // ══════════════════════════════════════════
        // PYTHON BASICS
        // ══════════════════════════════════════════
        {"Python Basics", "Introduction to Python", R"(
WHAT IS PYTHON?
Python is a beginner-friendly, high-level programming language
created by Guido van Rossum in 1991. It reads almost like English!

WHY PYTHON?
- Simple, clean syntax
- Used in web development, AI, data science, automation
- Huge library ecosystem (NumPy, Pandas, Django...)
- Most popular language in the world (2024)

YOUR FIRST PROGRAM:
    print("Hello, World!")

That is the entire program! Compare to C++:
    #include <iostream>
    using namespace std;
    int main() { cout << "Hello!" << endl; return 0; }

RUNNING PYTHON:
- Python files end in .py
- Run with: python filename.py
- Or use interactive mode: type python in terminal

COMMENTS:
    # This is a single-line comment

    """
    This is a
    multi-line comment
    (actually a string, but used as comment)
    """
)", 1},

        {"Python Basics", "Variables and Types", R"(
VARIABLES IN PYTHON:
No type declaration needed — Python figures it out!

    name = "Ahmed"      # str
    age = 25            # int
    height = 1.80       # float
    is_student = True   # bool

CHECK THE TYPE:
    print(type(name))    # <class 'str'>
    print(type(age))     # <class 'int'>

TYPE CONVERSION:
    x = "42"
    num = int(x)         # "42" → 42
    text = str(100)      # 100 → "100"
    dec = float("3.14")  # "3.14" → 3.14

STRING OPERATIONS:
    first = "Hello"
    last = "World"
    full = first + " " + last   # "Hello World"

    name = "Python"
    print(len(name))     # 6
    print(name.upper())  # PYTHON
    print(name.lower())  # python
    print(name[0])       # P — indexing
    print(name[-1])      # n — last character
    print(name[0:3])     # Pyt — slicing

F-STRINGS (modern formatting):
    age = 25
    print(f"I am {age} years old")  # I am 25 years old
    print(f"Double: {age * 2}")     # Double: 50
)", 2},

        {"Python Basics", "Lists and Collections", R"(
LISTS — ordered, changeable collections:
    fruits = ["apple", "banana", "cherry"]
    numbers = [1, 2, 3, 4, 5]
    mixed = [1, "hello", True, 3.14]   # any types!

ACCESSING ELEMENTS:
    print(fruits[0])    # apple
    print(fruits[-1])   # cherry (last)
    print(fruits[1:3])  # ['banana', 'cherry']

MODIFYING LISTS:
    fruits.append("mango")     # add to end
    fruits.insert(1, "grape")  # insert at index 1
    fruits.remove("banana")    # remove by value
    fruits.pop()               # remove last
    fruits.pop(0)              # remove at index 0
    fruits.sort()              # sort alphabetically
    fruits.reverse()           # reverse order
    print(len(fruits))         # number of items

LIST COMPREHENSION (powerful shortcut):
    squares = [x**2 for x in range(1, 6)]
    # [1, 4, 9, 16, 25]

    evens = [x for x in range(10) if x % 2 == 0]
    # [0, 2, 4, 6, 8]

TUPLES — like lists but IMMUTABLE (cannot change):
    point = (3, 5)
    coordinates = (10.5, 20.3, 0.0)

DICTIONARIES — key:value pairs:
    person = {
        "name": "Ahmed",
        "age": 25,
        "city": "Algiers"
    }
    print(person["name"])       # Ahmed
    person["email"] = "a@b.com" # add new key
    print(person.keys())        # all keys
    print(person.values())      # all values
)", 3},

        {"Python Basics", "Control Flow", R"(
IF/ELIF/ELSE IN PYTHON:
Note: Python uses indentation (spaces) instead of { }

    score = 85

    if score >= 90:
        print("Grade: A")
    elif score >= 80:
        print("Grade: B")
    elif score >= 70:
        print("Grade: C")
    else:
        print("Grade: F")

COMPARISON OPERATORS:
    ==  equal to
    !=  not equal
    >   greater than
    <   less than
    >=  greater or equal
    <=  less or equal

LOGICAL OPERATORS:
    and  — both must be true
    or   — at least one must be true
    not  — flips true/false

    if age >= 18 and has_id:
        print("Access granted")

    if is_student or is_teacher:
        print("School member")

TERNARY (one-line if):
    status = "adult" if age >= 18 else "minor"
    print(status)

IN OPERATOR (check membership):
    fruits = ["apple", "banana", "cherry"]
    if "apple" in fruits:
        print("Found it!")

    name = "Python"
    if "Py" in name:
        print("Starts with Py!")
)", 4},

        {"Python Basics", "Loops in Python", R"(
FOR LOOP — iterate over a sequence:
    for i in range(5):
        print(i)          # 0, 1, 2, 3, 4

    for i in range(1, 6):
        print(i)          # 1, 2, 3, 4, 5

    for i in range(0, 10, 2):
        print(i)          # 0, 2, 4, 6, 8

ITERATING OVER COLLECTIONS:
    fruits = ["apple", "banana", "cherry"]
    for fruit in fruits:
        print(fruit)

    # With index:
    for i, fruit in enumerate(fruits):
        print(f"{i}: {fruit}")

    # Iterating a string:
    for char in "Python":
        print(char)

WHILE LOOP:
    count = 0
    while count < 5:
        print(count)
        count += 1

    # User input loop:
    answer = ""
    while answer != "quit":
        answer = input("Enter command: ")

BREAK AND CONTINUE:
    for i in range(10):
        if i == 5:
            break         # stop at 5
        if i % 2 == 0:
            continue      # skip even numbers
        print(i)          # prints: 1, 3

NESTED LOOPS:
    for i in range(1, 4):
        for j in range(1, 4):
            print(f"{i}x{j}={i*j}", end="  ")
        print()
)", 5},

        {"Python Basics", "Functions in Python", R"(
DEFINING FUNCTIONS:
    def function_name(parameters):
        # body
        return value

BASIC EXAMPLE:
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

*ARGS — variable number of arguments:
    def total(*numbers):
        return sum(numbers)

    print(total(1, 2, 3))       # 6
    print(total(10, 20, 30, 40)) # 100

**KWARGS — keyword arguments:
    def describe(**info):
        for key, value in info.items():
            print(f"{key}: {value}")

    describe(name="Ahmed", age=25, city="Algiers")

LAMBDA (anonymous functions):
    square = lambda x: x ** 2
    print(square(5))   # 25

    double = lambda x: x * 2
    numbers = [1, 2, 3, 4]
    doubled = list(map(double, numbers))
    print(doubled)     # [2, 4, 6, 8]
)", 6},

        {"Python Basics", "Input, Output and Modules", R"(
USER INPUT:
    name = input("Enter your name: ")
    print(f"Hello, {name}!")

    # Input always returns a string — convert if needed:
    age = int(input("Enter your age: "))
    price = float(input("Enter price: "))

FORMATTED OUTPUT:
    name = "Ahmed"
    score = 95.5

    # f-strings (recommended):
    print(f"Student: {name}, Score: {score:.1f}")

    # format() method:
    print("Student: {}, Score: {:.1f}".format(name, score))

    # Special characters:
    print("Line 1\nLine 2")   # newline
    print("A\tB\tC")          # tab

IMPORTING MODULES:
    import math
    print(math.sqrt(16))     # 4.0
    print(math.pi)           # 3.14159...

    import random
    print(random.randint(1, 10))   # random 1-10
    print(random.choice(["a","b","c"]))

    from math import sqrt, pi      # import specific
    print(sqrt(25))                # 5.0

    import datetime
    now = datetime.datetime.now()
    print(now.year, now.month, now.day)

USEFUL BUILT-IN FUNCTIONS:
    print(abs(-5))        # 5
    print(max(1, 5, 3))   # 5
    print(min(1, 5, 3))   # 1
    print(sum([1,2,3]))   # 6
    print(round(3.7))     # 4
    print(sorted([3,1,2]))# [1, 2, 3]
)", 7},

        // ══════════════════════════════════════════
        // C++ OOP — 4 lessons
        // ══════════════════════════════════════════
        {"C++ Object-Oriented Programming", "Classes and Objects", R"(
WHAT IS OOP?
Object-Oriented Programming organizes code around objects
that have data (attributes) and behavior (methods).

DEFINING A CLASS:
    class Car {
    public:
        string brand;
        string model;
        int year;

        void honk() {
            cout << brand << " says: Beep!" << endl;
        }
    };

CREATING AN OBJECT:
    Car myCar;
    myCar.brand = "Toyota";
    myCar.model = "Corolla";
    myCar.year = 2022;

    myCar.honk();   // Toyota says: Beep!

    Car anotherCar;
    anotherCar.brand = "BMW";

CONSTRUCTORS (initialize objects automatically):
    class Car {
    public:
        string brand;
        int year;

        Car(string b, int y) {
            brand = b;
            year = y;
        }
    };

    Car myCar("Toyota", 2022);   // Constructor called!
    cout << myCar.brand;         // Toyota
)", 1},

        {"C++ Object-Oriented Programming", "Encapsulation", R"(
WHAT IS ENCAPSULATION?
Encapsulation means hiding the internal state of an object
and only exposing what is necessary through public methods.

ACCESS SPECIFIERS:
    class BankAccount {
    private:
        double balance;    // hidden from outside
        string owner;

    public:
        BankAccount(string name, double initial) {
            owner = name;
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
            return balance;        // controlled access
        }
    };

USING THE CLASS:
    BankAccount acc("Ahmed", 1000.0);
    acc.deposit(500);
    acc.withdraw(200);
    cout << acc.getBalance();   // 1300

    // This would be an ERROR:
    // acc.balance = -999;       // balance is private!

WHY ENCAPSULATION?
- Prevents invalid data (negative balance)
- Hides implementation details
- Makes code easier to maintain
)", 2},

        {"C++ Object-Oriented Programming", "Inheritance", R"(
WHAT IS INHERITANCE?
Inheritance lets a class (child) reuse and extend
the features of another class (parent).

BASE CLASS:
    class Animal {
    public:
        string name;
        int age;

        Animal(string n, int a) : name(n), age(a) {}

        void eat() {
            cout << name << " is eating." << endl;
        }

        void sleep() {
            cout << name << " is sleeping." << endl;
        }
    };

DERIVED CLASSES:
    class Dog : public Animal {
    public:
        string breed;

        Dog(string n, int a, string b)
            : Animal(n, a), breed(b) {}

        void bark() {
            cout << name << " says: Woof!" << endl;
        }
    };

    class Cat : public Animal {
    public:
        Cat(string n, int a) : Animal(n, a) {}

        void meow() {
            cout << name << " says: Meow!" << endl;
        }
    };

USING INHERITANCE:
    Dog dog("Rex", 3, "Labrador");
    dog.eat();    // from Animal — "Rex is eating."
    dog.bark();   // from Dog — "Rex says: Woof!"

    Cat cat("Whiskers", 2);
    cat.sleep();  // from Animal
    cat.meow();   // from Cat
)", 3},

        {"C++ Object-Oriented Programming", "Polymorphism", R"(
WHAT IS POLYMORPHISM?
Polymorphism means "many forms" — the same function name
behaves differently depending on the object.

FUNCTION OVERLOADING (compile-time polymorphism):
    class Calculator {
    public:
        int add(int a, int b) { return a + b; }
        double add(double a, double b) { return a + b; }
        int add(int a, int b, int c) { return a+b+c; }
    };

    Calculator calc;
    calc.add(2, 3);         // calls int version → 5
    calc.add(2.5, 3.5);     // calls double version → 6.0
    calc.add(1, 2, 3);      // calls 3-param version → 6

VIRTUAL FUNCTIONS (run-time polymorphism):
    class Shape {
    public:
        virtual double area() {
            return 0;
        }
    };

    class Circle : public Shape {
        double radius;
    public:
        Circle(double r) : radius(r) {}
        double area() override {
            return 3.14159 * radius * radius;
        }
    };

    class Rectangle : public Shape {
        double width, height;
    public:
        Rectangle(double w, double h)
            : width(w), height(h) {}
        double area() override {
            return width * height;
        }
    };

USING POLYMORPHISM:
    Shape* shapes[2];
    shapes[0] = new Circle(5.0);
    shapes[1] = new Rectangle(4.0, 6.0);

    for (Shape* s : shapes) {
        cout << s->area() << endl;
    }
    // 78.5398
    // 24
)", 4},

        // ══════════════════════════════════════════
        // DATA STRUCTURES — 4 lessons
        // ══════════════════════════════════════════
        {"Data Structures in C++", "Arrays and Vectors", R"(
ARRAYS — fixed-size sequential containers:
    int arr[5] = {10, 20, 30, 40, 50};

    // Access: O(1) — instant
    cout << arr[2];   // 30

    // Search: O(n) — must check each element
    for (int i = 0; i < 5; i++) {
        if (arr[i] == 30) cout << "Found at " << i;
    }

VECTORS — dynamic arrays (resize automatically):
    #include <vector>
    vector<int> v = {1, 2, 3, 4, 5};

    v.push_back(6);     // add to end: O(1)
    v.pop_back();       // remove last: O(1)
    v.insert(v.begin()+2, 99);  // insert at index 2
    v.erase(v.begin()+1);       // remove at index 1

    cout << v.size();   // number of elements
    cout << v.front();  // first element
    cout << v.back();   // last element

    // Iterate:
    for (int x : v) cout << x << " ";

    // Sort:
    #include <algorithm>
    sort(v.begin(), v.end());

WHEN TO USE WHICH:
Array: when size is known and fixed
Vector: when size might change (preferred in modern C++)

TIME COMPLEXITY:
    Access by index:  O(1) — instant
    Search:           O(n) — linear
    Insert at end:    O(1) — fast
    Insert at middle: O(n) — slow (shift elements)
)", 1},

        {"Data Structures in C++", "Linked Lists", R"(
WHAT IS A LINKED LIST?
A linked list stores data in nodes where each node
contains data and a pointer to the next node.

    [10|→] → [20|→] → [30|→] → [null]

NODE STRUCTURE:
    struct Node {
        int data;
        Node* next;

        Node(int val) : data(val), next(nullptr) {}
    };

BUILDING A LINKED LIST:
    Node* head = new Node(10);
    head->next = new Node(20);
    head->next->next = new Node(30);

TRAVERSING:
    Node* current = head;
    while (current != nullptr) {
        cout << current->data << " ";
        current = current->next;
    }
    // Output: 10 20 30

INSERT AT FRONT: O(1) — very fast
    Node* newNode = new Node(5);
    newNode->next = head;
    head = newNode;
    // List: 5 → 10 → 20 → 30

DELETE A NODE: O(n) — find then remove
    // To delete node with value 20:
    Node* prev = head;
    while (prev->next->data != 20)
        prev = prev->next;
    Node* toDelete = prev->next;
    prev->next = toDelete->next;
    delete toDelete;

ARRAY vs LINKED LIST:
    Insert at front: Array O(n), List O(1) ✓
    Access by index: Array O(1) ✓, List O(n)
    Memory:          Array fixed, List flexible ✓
)", 2},

        {"Data Structures in C++", "Stacks and Queues", R"(
STACK — Last In, First Out (LIFO):
Like a stack of plates — you take the top one first.

    #include <stack>
    stack<int> s;

    s.push(10);   // add to top
    s.push(20);
    s.push(30);

    cout << s.top();  // 30 — peek at top
    s.pop();          // remove 30
    cout << s.top();  // 20

    cout << s.size(); // 2
    cout << s.empty(); // false

REAL-WORLD STACK USES:
    • Browser back button (undo history)
    • Function call stack in programs
    • Expression evaluation (calculator)
    • Syntax checking (matching brackets)

QUEUE — First In, First Out (FIFO):
Like a line at a store — first person served first.

    #include <queue>
    queue<int> q;

    q.push(10);   // enqueue (add to back)
    q.push(20);
    q.push(30);

    cout << q.front(); // 10 — first element
    cout << q.back();  // 30 — last element
    q.pop();           // dequeue (remove front) → removes 10
    cout << q.front(); // 20

REAL-WORLD QUEUE USES:
    • Print queue (first document sent prints first)
    • CPU task scheduling
    • Breadth-first search in graphs
    • Customer service systems

PRIORITY QUEUE — highest priority served first:
    priority_queue<int> pq;
    pq.push(30);
    pq.push(10);
    pq.push(50);
    cout << pq.top();  // 50 — always the maximum!
)", 3},

        {"Data Structures in C++", "Trees and Maps", R"(
BINARY TREE BASICS:
Each node has at most 2 children (left and right).

    struct TreeNode {
        int data;
        TreeNode* left;
        TreeNode* right;
        TreeNode(int val) : data(val),
            left(nullptr), right(nullptr) {}
    };

BINARY SEARCH TREE (BST):
- Left subtree: values less than node
- Right subtree: values greater than node

        50
       /  \
      30   70
     / \   / \
    20 40 60  80

SEARCH IN BST: O(log n) average
    TreeNode* search(TreeNode* root, int val) {
        if (!root || root->data == val) return root;
        if (val < root->data)
            return search(root->left, val);
        return search(root->right, val);
    }

STL MAP — key-value pairs with O(log n) operations:
    #include <map>
    map<string, int> scores;

    scores["Ahmed"] = 95;
    scores["Fatima"] = 88;
    scores["Karim"] = 91;

    cout << scores["Ahmed"];  // 95

    // Iterate sorted by key:
    for (auto& pair : scores) {
        cout << pair.first << ": " << pair.second << endl;
    }

UNORDERED_MAP — O(1) average with hashing:
    #include <unordered_map>
    unordered_map<string, int> freq;
    freq["apple"]++;
    freq["banana"]++;
    freq["apple"]++;
    cout << freq["apple"];   // 2
)", 4},

        // ══════════════════════════════════════════
        // ALGORITHMS — 4 lessons
        // ══════════════════════════════════════════
        {"Algorithms & Complexity", "Big-O Notation", R"(
mmmmmm
WHAT IS BIG-O NOTATION?
Big-O describes how the performance of an algorithm
scales as input size (n) grows.

COMMON COMPLEXITIES (from fastest to slowest):

O(1) — Constant: same speed regardless of input
    int getFirst(vector<int>& v) { return v[0]; }
    // Always one operation — instant!

O(log n) — Logarithmic: halves the problem each step
    Binary search on sorted array
    Each step: 1,000,000 → 500,000 → 250,000 → ...
    Only needs ~20 steps for 1 million items!

O(n) — Linear: one operation per item
    for (int x : arr) sum += x;
    // 1000 items = 1000 operations

O(n log n) — Linearithmic: efficient sorting
    Merge sort, heap sort
    1000 items ≈ 10,000 operations

O(n²) — Quadratic: loop inside a loop
    for (int i : arr)
        for (int j : arr)   // nested loops!
    // 1000 items = 1,000,000 operations!

O(2ⁿ) — Exponential: doubles with each element
    Naive recursive Fibonacci
    // 50 items = 1 QUADRILLION operations! Unusable.

PRACTICAL EXAMPLE:
    Input size: n = 1,000,000

    O(1)       →          1 operation
    O(log n)   →         20 operations
    O(n)       →  1,000,000 operations
    O(n²)      →  10^12 operations (takes years!)
)", 1},

        {"Algorithms & Complexity", "Sorting Algorithms", R"(
BUBBLE SORT — O(n²) — simple but slow:
Compare adjacent pairs and swap if wrong order.
    void bubbleSort(vector<int>& arr) {
        int n = arr.size();
        for (int i = 0; i < n-1; i++) {
            for (int j = 0; j < n-i-1; j++) {
                if (arr[j] > arr[j+1])
                    swap(arr[j], arr[j+1]);
            }
        }
    }
    // [5,3,8,1] → [3,5,8,1] → [3,5,1,8] → [1,3,5,8]

SELECTION SORT — O(n²):
Find minimum, place at front, repeat.
    void selectionSort(vector<int>& arr) {
        for (int i = 0; i < arr.size(); i++) {
            int minIdx = i;
            for (int j = i+1; j < arr.size(); j++)
                if (arr[j] < arr[minIdx]) minIdx = j;
            swap(arr[i], arr[minIdx]);
        }
    }

MERGE SORT — O(n log n) — efficient, divide and conquer:
Split in half, sort each half, merge back.
    [8,3,5,1] → [8,3] [5,1] → [3,8] [1,5] → [1,3,5,8]

QUICK SORT — O(n log n) average, O(n²) worst:
Pick a pivot, partition around it, recurse.

STL SORT — always use this in practice!
    #include <algorithm>
    vector<int> v = {5, 3, 8, 1, 9, 2};
    sort(v.begin(), v.end());
    // v = {1, 2, 3, 5, 8, 9}

    sort(v.rbegin(), v.rend()); // descending
    // v = {9, 8, 5, 3, 2, 1}
)", 2},

        {"Algorithms & Complexity", "Searching Algorithms", R"(
LINEAR SEARCH — O(n):
Check each element one by one.
    int linearSearch(vector<int>& arr, int target) {
        for (int i = 0; i < arr.size(); i++) {
            if (arr[i] == target) return i;
        }
        return -1;   // not found
    }
    // Works on ANY array — sorted or not
    // Slow for large arrays

BINARY SEARCH — O(log n):
REQUIRES a SORTED array!
Compare target with the MIDDLE element:
- If equal — found!
- If target < middle — search LEFT half
- If target > middle — search RIGHT half

    int binarySearch(vector<int>& arr, int target) {
        int left = 0, right = arr.size() - 1;

        while (left <= right) {
            int mid = (left + right) / 2;

            if (arr[mid] == target) return mid;
            if (arr[mid] < target)  left = mid + 1;
            else                    right = mid - 1;
        }
        return -1;   // not found
    }

BINARY SEARCH EXAMPLE:
    arr = [1, 3, 5, 7, 9, 11, 13]
    target = 7

    Step 1: mid=3, arr[3]=7 → FOUND at index 3!

    target = 11
    Step 1: mid=3, arr[3]=7, 11>7 → search right
    Step 2: mid=5, arr[5]=11 → FOUND at index 5!

STL BINARY SEARCH:
    #include <algorithm>
    vector<int> v = {1,3,5,7,9};
    sort(v.begin(), v.end());   // must be sorted!
    bool found = binary_search(v.begin(), v.end(), 7);
    // found = true
)", 3},

        {"Algorithms & Complexity", "Recursion and Dynamic Programming", R"(
RECURSION — a function that calls itself:
    Every recursive function needs:
    1. A BASE CASE (stop condition)
    2. A RECURSIVE CASE (calls itself with smaller input)

FACTORIAL EXAMPLE:
    int factorial(int n) {
        if (n == 0) return 1;        // base case
        return n * factorial(n - 1); // recursive case
    }

    factorial(4) = 4 * factorial(3)
                 = 4 * 3 * factorial(2)
                 = 4 * 3 * 2 * factorial(1)
                 = 4 * 3 * 2 * 1 * factorial(0)
                 = 4 * 3 * 2 * 1 * 1 = 24

FIBONACCI (naive recursion — O(2ⁿ) very slow!):
    int fib(int n) {
        if (n <= 1) return n;
        return fib(n-1) + fib(n-2);
    }
    // fib(5) calls fib(4) AND fib(3)
    // fib(4) calls fib(3) AND fib(2)
    // fib(3) is computed TWICE! Wasteful.

DYNAMIC PROGRAMMING — store results to avoid recomputation:
    int fib_dp(int n) {
        vector<int> dp(n+1, 0);
        dp[0] = 0;
        dp[1] = 1;
        for (int i = 2; i <= n; i++)
            dp[i] = dp[i-1] + dp[i-2];
        return dp[n];
    }
    // Each subproblem computed ONCE → O(n)

DP PRINCIPLE: "Remember what you already computed!"
Use DP when:
    • Problem has overlapping subproblems
    • Optimal solution built from optimal sub-solutions
    Examples: Fibonacci, shortest path, knapsack
)", 4},

        // ══════════════════════════════════════════
        // PYTHON FUNCTIONS & MODULES — 4 lessons
        // ══════════════════════════════════════════
        {"Python Fundamentals & Modules", "Advanced Functions", R"(
SCOPE — where variables live:
    x = 10   # global variable

    def my_func():
        y = 20   # local variable
        print(x)  # can access global
        print(y)  # local is fine

    my_func()
    # print(y)   # ERROR! y is local to my_func

GLOBAL KEYWORD:
    count = 0
    def increment():
        global count   # declare we mean the global
        count += 1

    increment()
    increment()
    print(count)   # 2

CLOSURES — function that remembers its environment:
    def make_multiplier(factor):
        def multiply(x):
            return x * factor   # remembers factor!
        return multiply

    double = make_multiplier(2)
    triple = make_multiplier(3)
    print(double(5))   # 10
    print(triple(5))   # 15

DECORATORS — wrap a function to add behavior:
    def timer(func):
        def wrapper(*args):
            import time
            start = time.time()
            result = func(*args)
            end = time.time()
            print(f"Took {end-start:.4f} seconds")
            return result
        return wrapper

    @timer
    def slow_function():
        import time; time.sleep(0.1)

    slow_function()   # Took 0.1001 seconds
)", 1},

        {"Python Fundamentals & Modules", "Modules and Packages", R"(
WHAT IS A MODULE?
A module is a Python file containing functions, classes,
and variables that you can reuse in other programs.

IMPORTING MODULES:
    import math
    print(math.sqrt(25))    # 5.0
    print(math.ceil(4.2))   # 5
    print(math.floor(4.8))  # 4
    print(math.pi)          # 3.14159...

    import random
    print(random.randint(1, 100))     # random int
    print(random.choice([1,2,3,4]))   # random choice
    random.shuffle([1,2,3,4,5])       # shuffle in place

    import os
    print(os.getcwd())        # current directory
    files = os.listdir('.')   # list files

SELECTIVE IMPORTS:
    from math import sqrt, pi
    print(sqrt(16))    # 4.0 — no math. prefix needed

    from random import randint
    print(randint(1, 10))

ALIASES:
    import numpy as np         # standard alias
    import pandas as pd        # standard alias
    import matplotlib.pyplot as plt

CREATING YOUR OWN MODULE:
    # Save as utils.py:
    def add(a, b): return a + b
    def subtract(a, b): return a - b
    PI = 3.14159

    # In another file:
    import utils
    print(utils.add(3, 5))   # 8
    print(utils.PI)           # 3.14159
)", 2},

        {"Python Fundamentals & Modules", "File Handling", R"(
READING FILES:
    # Open and read entire file:
    with open("data.txt", "r") as f:
        content = f.read()
        print(content)

    # Read line by line:
    with open("data.txt", "r") as f:
        for line in f:
            print(line.strip())  # strip removes \n

    # Read all lines into a list:
    with open("data.txt", "r") as f:
        lines = f.readlines()

WRITING FILES:
    # Write (overwrites existing content):
    with open("output.txt", "w") as f:
        f.write("Hello, World!\n")
        f.write("Second line\n")

    # Append (adds to existing content):
    with open("log.txt", "a") as f:
        f.write("New log entry\n")

WORKING WITH CSV FILES:
    import csv

    # Reading CSV:
    with open("students.csv", "r") as f:
        reader = csv.reader(f)
        for row in reader:
            print(row)

    # Writing CSV:
    with open("output.csv", "w", newline="") as f:
        writer = csv.writer(f)
        writer.writerow(["Name", "Score"])
        writer.writerow(["Ahmed", 95])
        writer.writerow(["Fatima", 88])

THE "WITH" STATEMENT:
    with open("file.txt") as f:
        ...
    # File closes AUTOMATICALLY — even if error occurs!
    # Always use "with" for file operations.
)", 3},

        {"Python Fundamentals & Modules", "Error Handling", R"(
WHY HANDLE ERRORS?
Programs encounter unexpected situations — wrong input,
missing files, network failures. Error handling prevents crashes.

TRY/EXCEPT:
    try:
        x = int(input("Enter a number: "))
        result = 10 / x
        print(f"Result: {result}")
    except ValueError:
        print("That wasn't a number!")
    except ZeroDivisionError:
        print("Cannot divide by zero!")

MULTIPLE EXCEPT BLOCKS:
    try:
        risky_code()
    except TypeError as e:
        print(f"Type error: {e}")
    except FileNotFoundError as e:
        print(f"File not found: {e}")
    except Exception as e:
        print(f"Unexpected error: {e}")   # catch-all

ELSE AND FINALLY:
    try:
        f = open("data.txt")
        data = f.read()
    except FileNotFoundError:
        print("File missing!")
    else:
        print("File read successfully!")  # runs if no error
    finally:
        print("This ALWAYS runs!")        # cleanup code

RAISING YOUR OWN ERRORS:
    def set_age(age):
        if age < 0 or age > 150:
            raise ValueError(f"Invalid age: {age}")
        return age

    try:
        set_age(-5)
    except ValueError as e:
        print(e)   # Invalid age: -5

COMMON EXCEPTION TYPES:
    ValueError      — wrong type of value
    TypeError       — wrong type of argument
    IndexError      — list index out of range
    KeyError        — dictionary key not found
    FileNotFoundError — file does not exist
    ZeroDivisionError — division by zero
)", 4},

        // ══════════════════════════════════════════
        // C++ ADVANCED — 4 lessons
        // ══════════════════════════════════════════
        {"C++ Advanced Topics", "Templates", R"(
WHAT ARE TEMPLATES?
Templates allow you to write code that works with ANY data type.
Write once, use for int, double, string, or any custom type.

FUNCTION TEMPLATE:
    template<typename T>
    T maximum(T a, T b) {
        return (a > b) ? a : b;
    }

    cout << maximum(3, 7);        // 7 (int)
    cout << maximum(3.14, 2.71);  // 3.14 (double)
    cout << maximum('A', 'Z');    // Z (char)

CLASS TEMPLATE:
    template<typename T>
    class Box {
    private:
        T value;
    public:
        Box(T val) : value(val) {}
        T get() { return value; }
        void set(T val) { value = val; }
    };

    Box<int> intBox(42);
    Box<string> strBox("Hello");
    Box<double> dblBox(3.14);

    cout << intBox.get();  // 42
    cout << strBox.get();  // Hello

MULTIPLE TEMPLATE PARAMETERS:
    template<typename K, typename V>
    class Pair {
    public:
        K key;
        V value;
        Pair(K k, V v) : key(k), value(v) {}
    };

    Pair<string, int> p("score", 95);
    cout << p.key << ": " << p.value;  // score: 95

STL IS BUILT ON TEMPLATES:
    vector<int>    v1;   // vector of ints
    vector<string> v2;   // vector of strings
    map<string, int> m;  // map with any types
)", 1},

        {"C++ Advanced Topics", "STL Containers", R"(
THE STANDARD TEMPLATE LIBRARY (STL):
A collection of ready-made, optimized data structures.

VECTOR — dynamic array:
    vector<int> v = {3, 1, 4, 1, 5};
    v.push_back(9);
    sort(v.begin(), v.end());
    cout << v[0];           // 1

MAP — sorted key-value pairs O(log n):
    map<string, int> ages;
    ages["Ahmed"] = 25;
    ages["Fatima"] = 22;
    ages["Karim"] = 28;

    for (auto& [name, age] : ages)
        cout << name << ": " << age << endl;
    // Output sorted by name!

UNORDERED_MAP — hash map O(1) average:
    unordered_map<string, int> freq;
    string text = "hello world";
    for (char c : text) freq[c]++;

SET — unique sorted elements:
    set<int> s = {5, 3, 8, 3, 1, 5};
    // Contains: {1, 3, 5, 8} — duplicates removed!
    s.insert(10);
    s.erase(3);
    cout << s.count(5);  // 1 (exists) or 0 (not)

DEQUE — double-ended queue:
    deque<int> dq;
    dq.push_front(1);  // add to front
    dq.push_back(2);   // add to back
    dq.pop_front();    // remove from front
    dq.pop_back();     // remove from back

STL ALGORITHMS:
    #include <algorithm>
    vector<int> v = {5,2,8,1,9};
    sort(v.begin(), v.end());
    reverse(v.begin(), v.end());
    int sum = accumulate(v.begin(), v.end(), 0);
    auto it = find(v.begin(), v.end(), 8);
    int count = count_if(v.begin(), v.end(),
                         [](int x){ return x > 5; });
)", 2},

        {"C++ Advanced Topics", "Smart Pointers", R"(
THE PROBLEM WITH RAW POINTERS:
    int* p = new int(42);
    // If you forget delete p; → MEMORY LEAK!
    // If you delete twice → UNDEFINED BEHAVIOR!

SMART POINTERS automatically manage memory.
Include: #include <memory>

UNIQUE_PTR — exclusive ownership:
    unique_ptr<int> p1 = make_unique<int>(42);
    cout << *p1;      // 42

    // Cannot copy:
    // unique_ptr<int> p2 = p1;   // ERROR!

    // Can only move:
    unique_ptr<int> p2 = move(p1);
    // p1 is now null, p2 owns the resource

    // Auto-deleted when p2 goes out of scope!

SHARED_PTR — shared ownership:
    shared_ptr<int> sp1 = make_shared<int>(100);
    shared_ptr<int> sp2 = sp1;   // both own it!

    cout << sp1.use_count();   // 2 (two owners)
    sp2.reset();               // sp2 releases ownership
    cout << sp1.use_count();   // 1
    // Memory freed when LAST shared_ptr is gone

WEAK_PTR — non-owning reference:
    shared_ptr<int> sp = make_shared<int>(50);
    weak_ptr<int> wp = sp;   // does not increase count

    if (auto locked = wp.lock()) {
        cout << *locked;   // 50 — valid!
    }

USE SMART POINTERS ALWAYS:
    unique_ptr — when one owner
    shared_ptr — when multiple owners needed
    Never use raw pointers for ownership!
)", 3},

        {"C++ Advanced Topics", "Modern C++11/17 Features", R"(
AUTO — type inference:
    auto x = 42;          // int
    auto y = 3.14;        // double
    auto s = "hello"s;    // string
    auto v = vector<int>{1,2,3};

    // In loops — very useful:
    for (auto& item : v) cout << item;

LAMBDA FUNCTIONS — anonymous functions:
    auto square = [](int x) { return x * x; };
    cout << square(5);   // 25

    // Capturing variables:
    int factor = 3;
    auto multiply = [factor](int x) {
        return x * factor;
    };
    cout << multiply(7);   // 21

    // With STL algorithms:
    vector<int> v = {1,5,3,8,2};
    sort(v.begin(), v.end(),
         [](int a, int b){ return a > b; });
    // Sorted descending: {8,5,3,2,1}

RANGE-BASED FOR:
    vector<string> names = {"Ahmed","Fatima","Karim"};
    for (const string& name : names)
        cout << name << endl;

STRUCTURED BINDINGS (C++17):
    map<string,int> scores = {{"A",95},{"B",87}};
    for (auto& [name, score] : scores)
        cout << name << ": " << score << endl;

NULLPTR (replaces NULL):
    int* p = nullptr;   // safe null pointer
    if (p != nullptr) cout << *p;

CONSTEXPR — compile-time constants:
    constexpr int MAX_SIZE = 100;
    constexpr double PI = 3.14159265358979;
)", 4},

        // ══════════════════════════════════════════
        // PYTHON DATA SCIENCE — 4 lessons
        // ══════════════════════════════════════════
        {"Python for Data Science", "NumPy Basics", R"(
WHAT IS NUMPY?
NumPy (Numerical Python) provides fast, efficient arrays
for mathematical computing. Much faster than Python lists!

IMPORTING NUMPY:
    import numpy as np

CREATING ARRAYS:
    a = np.array([1, 2, 3, 4, 5])
    b = np.array([[1,2,3],[4,5,6]])  # 2D array

    zeros = np.zeros(5)         # [0. 0. 0. 0. 0.]
    ones  = np.ones((2,3))      # 2x3 matrix of 1s
    rng   = np.arange(0, 10, 2) # [0 2 4 6 8]
    lin   = np.linspace(0,1,5)  # [0. 0.25 0.5 0.75 1.]

ARRAY PROPERTIES:
    print(a.shape)   # (5,) — 1D with 5 elements
    print(b.shape)   # (2, 3) — 2 rows, 3 columns
    print(a.dtype)   # int64
    print(a.size)    # total number of elements

VECTORIZED OPERATIONS (no loops needed!):
    a = np.array([1, 2, 3, 4, 5])
    print(a + 10)     # [11 12 13 14 15]
    print(a * 2)      # [2 4 6 8 10]
    print(a ** 2)     # [1 4 9 16 25]
    print(a + a)      # [2 4 6 8 10]

MATHEMATICAL FUNCTIONS:
    print(np.sum(a))     # 15
    print(np.mean(a))    # 3.0
    print(np.std(a))     # standard deviation
    print(np.min(a))     # 1
    print(np.max(a))     # 5
    print(np.sqrt(a))    # [1. 1.41 1.73 2. 2.23]

INDEXING AND SLICING:
    a = np.array([10, 20, 30, 40, 50])
    print(a[2])      # 30
    print(a[1:4])    # [20 30 40]
    print(a[-1])     # 50

    b = np.array([[1,2,3],[4,5,6]])
    print(b[0,1])    # 2 — row 0, col 1
    print(b[:,1])    # [2,5] — all rows, col 1
)", 1},

        {"Python for Data Science", "Pandas DataFrames", R"(
WHAT IS PANDAS?
Pandas provides the DataFrame — a 2D table with labeled
rows and columns. Think of it as Python's Excel!

IMPORTING:
    import pandas as pd

CREATING A DATAFRAME:
    data = {
        "Name":  ["Ahmed", "Fatima", "Karim"],
        "Age":   [25, 22, 28],
        "Score": [95, 88, 91]
    }
    df = pd.DataFrame(data)

    #      Name  Age  Score
    # 0   Ahmed   25     95
    # 1  Fatima   22     88
    # 2   Karim   28     91

EXPLORING THE DATA:
    print(df.head())        # first 5 rows
    print(df.tail(2))       # last 2 rows
    print(df.shape)         # (3, 3) rows x columns
    print(df.columns)       # column names
    print(df.dtypes)        # data types
    print(df.describe())    # statistics

ACCESSING DATA:
    df["Name"]              # entire column
    df[["Name","Score"]]    # multiple columns
    df.iloc[0]              # first row by position
    df.iloc[0:2]            # first 2 rows
    df.loc[df["Age"] > 23]  # filter rows

MODIFYING DATA:
    df["Grade"] = ["A","B","A"]   # add column
    df["Score"] = df["Score"] + 5  # modify column
    df.drop("Grade", axis=1)       # remove column
    df.rename(columns={"Name":"Student"}) # rename

SORTING:
    df.sort_values("Score", ascending=False)
    df.sort_values(["Age","Score"])

MISSING VALUES:
    df.isnull().sum()    # count NaN in each column
    df.dropna()          # remove rows with NaN
    df.fillna(0)         # replace NaN with 0
)", 2},

        {"Python for Data Science", "Data Cleaning", R"(
LOADING DATA FROM FILES:
    import pandas as pd

    df = pd.read_csv("students.csv")
    df = pd.read_excel("data.xlsx")
    df = pd.read_json("data.json")

    # Save back:
    df.to_csv("clean_data.csv", index=False)

EXPLORING A REAL DATASET:
    print(df.head())          # first look
    print(df.info())          # column types and non-null counts
    print(df.describe())      # statistics
    print(df.isnull().sum())  # missing values per column

HANDLING MISSING VALUES:
    # Remove rows with any missing value:
    df_clean = df.dropna()

    # Remove only if specific column is missing:
    df_clean = df.dropna(subset=["Score"])

    # Fill missing with a value:
    df["Score"].fillna(df["Score"].mean(), inplace=True)
    df["Name"].fillna("Unknown", inplace=True)

REMOVING DUPLICATES:
    df.drop_duplicates(inplace=True)
    df.drop_duplicates(subset=["Name"], inplace=True)

FIXING DATA TYPES:
    df["Age"] = pd.to_numeric(df["Age"], errors="coerce")
    df["Date"] = pd.to_datetime(df["Date"])

FILTERING AND SELECTING:
    high_scores = df[df["Score"] >= 90]
    cpp_courses = df[df["Language"] == "C++"]
    combo = df[(df["Score"] > 80) & (df["Age"] < 30)]

STRING OPERATIONS:
    df["Name"] = df["Name"].str.strip()    # remove spaces
    df["Name"] = df["Name"].str.lower()    # lowercase
    df["Name"] = df["Name"].str.title()    # Title Case
    df[df["Name"].str.contains("Ali")]     # filter by string
)", 3},

        {"Python for Data Science", "Data Analysis", R"(
GROUPING AND AGGREGATION:
    import pandas as pd

    # Group by a column and compute statistics:
    grouped = df.groupby("Language")["Score"].mean()
    # Language
    # C++       91.5
    # Python    87.3

    # Multiple aggregations:
    df.groupby("Language").agg({
        "Score": ["mean", "max", "min"],
        "Age":   ["mean"]
    })

    # Count per group:
    df.groupby("Language").size()

APPLYING FUNCTIONS:
    # Apply to a column:
    df["Score_Category"] = df["Score"].apply(
        lambda x: "A" if x >= 90 else
                  "B" if x >= 80 else "C"
    )

    # Apply to each row:
    def grade_label(row):
        if row["Score"] >= 90:
            return f"{row['Name']} is excellent!"
        return f"{row['Name']} needs improvement"

    df["Label"] = df.apply(grade_label, axis=1)

PIVOT TABLES:
    pivot = df.pivot_table(
        values="Score",
        index="Language",
        columns="Difficulty",
        aggfunc="mean"
    )

BASIC STATISTICS:
    print(df["Score"].mean())    # average
    print(df["Score"].median())  # middle value
    print(df["Score"].std())     # spread
    print(df["Score"].corr(df["Age"]))  # correlation

SAVING RESULTS:
    df.to_csv("analysis_results.csv", index=False)
    summary = df.groupby("Language")["Score"].describe()
    summary.to_excel("summary.xlsx")
)", 4},
        };

QSqlQuery q(m_db);
q.prepare(R"(
        INSERT INTO lessons
            (course_id, order_num, title, content)
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
    else qDebug() << "Lesson seed error:" << q.lastError().text();
}
qDebug() << "Lessons seeded:" << seeded << "/" << lessons.size();
}

