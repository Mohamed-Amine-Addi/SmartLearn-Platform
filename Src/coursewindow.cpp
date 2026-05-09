#include "coursewindow.h"
#include "ui_coursewindow.h"
#include "databasemanager.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QFrame>

coursewindow::coursewindow (const QString& username, QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::coursewindow)
    ,m_username(username)
{
    ui->setupUi(this);
    setWindowTitle("Langora - Courses");
    setMinimumSize(900,600);

    //update user info in top bar
    int xp = databasemanager::instance().getUserXp(username);
    int level = databasemanager::instance().getUserLevel(username);
    ui->label_userinfo->setText(
        QString("Level %1 | %2 XP").arg(level).arg(xp));

    //set up the cards layout inside the scroll area
    m_cardsLayout = new QVBoxLayout(ui->scrollContents);
    m_cardsLayout->setContentsMargins(20, 16, 20, 16);
    m_cardsLayout->setSpacing(10);
    m_cardsLayout->addStretch();

    //load all courses by default
    loadCourses("");
}

coursewindow::~coursewindow()
{
    delete ui;
}

// filter button slots
void coursewindow::on_btn_filter_all_clicked(){
    setActiveFilter("all");
    loadCourses("");
}

void coursewindow::on_btn_filter_cpp_clicked(){
    setActiveFilter("cpp");
    loadCourses("C++");
}

void coursewindow::on_btn_filter_python_clicked(){
    setActiveFilter("python");
    loadCourses("Python");
}

void coursewindow::setActiveFilter(const QString& filter){
    QString active = R"(
        QPushButton {
            background: #0d1f3c; color: #60a5fa;
            border: 1px solid #1d4ed8; border-radius: 14px;
            font-size: 11px; font-weight: bold;
        })";
    QString inactive = R"(
        QPushButton {
            background: transparent; color: #334155;
            border: 1px solid #0f1629; border-radius: 14px;
            font-size: 11px; font-weight: bold;
        })";

    ui->btn_filter_all->setStyleSheet(filter == "all" ? active : inactive);
    ui->btn_filter_cpp->setStyleSheet(filter == "cpp" ? active : inactive);
    ui->btn_filter_python->setStyleSheet(filter == "python" ? active : inactive);

}

//load courses and build cards
void coursewindow::loadCourses(const QString& languageFilter){
    //remove old  cards (keep the strength at the end)
    while(m_cardsLayout->count() > 1){
        QLayoutItem* item = m_cardsLayout->takeAt(0);
        if (item->widget()) item->widget()->deleteLater();
        delete item;
    }
    QList<course> courses = databasemanager::instance().getAllCourses();
    int shown = 0;
    for(const course& course : courses){
        if(!languageFilter.isEmpty() && course.language != languageFilter) continue;
        buildCourseCard(course, m_cardsLayout);
        shown++;
    }

    ui->label_count->setText(QString("%1 course%2 available").arg(shown).arg(shown == 1 ? "" : "s"));
}

// build one course card
void coursewindow::buildCourseCard(const course& course, QVBoxLayout* layout){
    QFrame* card = new QFrame();
    card->setFixedHeight(110);
    card->setStyleSheet(R"(
        QFrame {
            background-color: #070b14;
            border: 1px solid #0f1629;
            border-radius: 12px;
        }
        QFrame:hover {
            border-color: #1d4ed8;
            background-color: #080d18;
        }
    )");
    QHBoxLayout* row = new QHBoxLayout(card);
    row->setContentsMargins(18, 0, 18, 0);
    row->setSpacing(16);

    //language badge
    QFrame* badge = new QFrame(card);
    badge->setFixedSize(50, 50);
    QString color = (course.language == "C++") ? "#0d1f5c" : "#1a0a40";
    QString border = (course.language == "C++") ? "#1a3a99" : "#3b1a99";
    badge->setStyleSheet(QString(
            "QFrame { background: %1; border-radius: 12px;"
                             "border: 1px solid %2; }").arg(color, border));

    QLabel *badgeTxt = new QLabel(course.language == "C++" ? "C++" : "Py", badge);
    badgeTxt->setGeometry(0, 0, 50, 50);
    badgeTxt->setAlignment(Qt::AlignCenter);
    badgeTxt->setStyleSheet("color: #93c5fd; font-size: 11px; font-weight: bold;""background: transparent;");
    row->addWidget(badge);
     // info section
    QVBoxLayout* info = new QVBoxLayout();
    info->setSpacing(4);

    //title + difficulty pill
    QHBoxLayout* titleRow = new QHBoxLayout();
    titleRow->setSpacing(10);

    QLabel* title = new QLabel(course.title);
    title->setStyleSheet("color: #e2e8f0; font-size: 14px; font-weight: bold;""background: transparent");
    QLabel* diff = new QLabel(course.difficultytext());
    diff->setFixedHeight(20);
    diff->setMinimumWidth(90);
    diff->setAlignment(Qt::AlignCenter);
    diff->setStyleSheet(QString(R"(
        QLabel {
            color: %1;
            background: transparent;
            border: 1px solid %1;
            border-radius: 10px;
            font-size: 10px;
            font-weight: bold;
            padding: 0 8px;
        }
    )").arg(course.difficultycolor()));
    titleRow->addWidget(title);
    titleRow->addWidget(diff);
    titleRow->addStretch();
    info->addLayout(titleRow);

    //description
    QLabel* desc = new QLabel(course.description);
    desc->setStyleSheet("color: #334155; font-size: 12px; background: transparent;");
    desc->setWordWrap(true);
    info->addWidget(desc);

    //stats
    QHBoxLayout* stats = new QHBoxLayout();
    stats->setSpacing(20);
    auto makeStat = [](const QString& txt){
        QLabel* l = new QLabel(txt);
        l->setStyleSheet("color: #1e3a5f; font-size: 11px; background: transparent;");
        return l;
    };
    stats->addWidget(makeStat(QString("%1 lessons").arg(course.totallessons)));
    stats->addWidget(makeStat(QString("%1 XP on completion").arg(course.xpreward)));
    stats->addStretch();
    info->addLayout(stats);

    row->addLayout(info);

    // start button
    QPushButton* btn = new QPushButton("start →", card);
    btn->setFixedSize(88, 36);
    btn->setStyleSheet(R"(
        QPushButton {
            color: #eff6ff;
            background: #1d4ed8;
            border: none;
            border-radius: 8px;
            font-size: 12px;
            font-weight: bold;
        }
        QPushButton:hover { background: #2563eb; }
        QPushButton:pressed { background: #1e40af; }
    )");

    int cId = course.id;
    QString cTitle = course.title;
    connect(btn, &QPushButton::clicked,[this, cId, cTitle](){
        emit courseStarted(cId, cTitle);
    });

    row->addWidget(btn);

    //insert before the stretch
    layout->insertWidget(layout->count()-1, card);
}

void coursewindow::on_pushButton_back_clicked(){
    emit backRequested();
}
