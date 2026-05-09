#include "coursedetailwindow.h"
#include "ui_coursedetailwindow.h"

coursedetailwindow::coursedetailwindow(const course& c, const QString& username, QWidget* parent)
    : QWidget(parent)
    , ui(new Ui::coursedetailwindow)
    , m_course(c)
    , m_username(username)
{
    ui->setupUi(this);
    setWindowTitle("Langora — " + c.title);
    setMinimumSize(860, 580);

    //Top bar title
    ui->label_course_title->setText(c.title);

    //info card
    ui->label_lang_badge->setText(
        c.language == "C++" ? "C++" : "Py");
    ui->label_lang_badge->setStyleSheet(
        c.language == "C++" ? "QLabel { background:#0d1f5c; border-radius:12px; border:1px solid #1a3a99; color:#93c5fd; font-size:13px; font-weight:bold; }" : "QLabel { background:#1a0a40; border-radius:12px; border:1px solid #3b1a99; color:#c4b5fd; font-size:13px; font-weight:bold; }");

    ui->label_title_card->setText(c.title);
    ui->label_description->setText(c.description);

    //difficulty badge
    ui->label_difficulty_badge->setText(c.difficultytext());
    ui->label_difficulty_badge->setStyleSheet(QString(
                                                  "QLabel { color:%1; border:1px solid %1; border-radius:11px;"
                                                  "font-size:11px; font-weight:bold; background:transparent;"
                                                  "padding:0 8px; }").arg(c.difficultycolor()));

    //stats
    ui->label_lessons_val->setText(
        QString::number(c.totallessons));
    ui->label_xp_val->setText(
        "+" + QString::number(c.xpreward) + " XP");
    ui->label_diff_val->setText(c.difficultytext());
    ui->label_diff_val->setStyleSheet(QString(
                                          "QLabel { color:%1; font-size:18px; font-weight:bold;"
                                          "background:transparent; }").arg(c.difficultycolor()));
    ui->label_lang_val->setText(c.language);

    //what you will learn — build from description
    QStringList topics;
    if (c.language == "C++") {
        if (c.difficulty == Difficulty::Beginner)
            topics << "• Variables, data types and operators"
                   << "• Control flow: if, for, while loops"
                   << "• Functions and scope"
                   << "• Basic input and output with cin/cout";
        else if (c.difficulty == Difficulty::Intermediate)
            topics << "• Classes and objects"
                   << "• Inheritance and polymorphism"
                   << "• Encapsulation with access specifiers"
                   << "• Constructors and destructors";
        else
            topics << "• Templates and generic programming"
                   << "• STL containers: vector, map, set"
                   << "• Smart pointers and memory management"
                   << "• Lambda functions and C++17 features";
    } else {
        if (c.difficulty == Difficulty::Beginner)
            topics << "• Python syntax and indentation rules"
                   << "• Variables, lists, and dictionaries"
                   << "• if/else statements and loops"
                   << "• Built-in functions like len, print, input";
        else if (c.difficulty == Difficulty::Intermediate)
            topics << "• Defining and calling functions"
                   << "• Modules and the import system"
                   << "• File reading and writing"
                   << "• Exception handling with try/except";
        else
            topics << "• NumPy arrays and vectorized operations"
                   << "• Pandas DataFrames and data manipulation"
                   << "• Reading CSV files and cleaning data"
                   << "• Basic statistical analysis with describe()";
    }
    ui->label_learn_content->setText(topics.join("\n"));
}

coursedetailwindow::~coursedetailwindow() {
    delete ui;
}

void coursedetailwindow::on_pushButton_back_clicked() {
    emit backRequested();
}

// Change on_pushButton_startQuiz_clicked to:
void coursedetailwindow::on_pushButton_startQuiz_clicked() {
    emit startLearningRequested(m_course.id, m_course.title);
}
