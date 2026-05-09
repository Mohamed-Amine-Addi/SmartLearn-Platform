#include "quizselectwindow.h"
#include "ui_quizselectwindow.h"
#include "databasemanager.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QFrame>

quizselectwindow::quizselectwindow(const QString& username, QWidget* parent)
    : QWidget(parent)
    , ui(new Ui::quizselectwindow)
    , m_username(username)
{
    ui->setupUi(this);
    setWindowTitle("Langora — Select Quiz");
    setMinimumSize(900, 600);

    m_cardsLayout = new QVBoxLayout(ui->scrollContents);
    m_cardsLayout->setContentsMargins(20, 16, 20, 16);
    m_cardsLayout->setSpacing(10);
    m_cardsLayout->addStretch();

    QList<course> courses =
        databasemanager::instance().getAllCourses();

    for (const course& c : courses)
        buildCourseCard(c, m_cardsLayout);
}

quizselectwindow::~quizselectwindow() {
    delete ui;
}

void quizselectwindow::buildCourseCard(const course& c, QVBoxLayout* layout)
{
    QFrame* card = new QFrame();
    card->setFixedHeight(100);
    card->setStyleSheet(R"(
        QFrame {
            background-color: #070b14;
            border: 1px solid #0f1629;
            border-radius: 12px;
        }
        QFrame:hover {
            border-color: #f59e0b;
            background-color: #080d18;
        }
    )");

    QHBoxLayout* row = new QHBoxLayout(card);
    row->setContentsMargins(18, 0, 18, 0);
    row->setSpacing(16);

    // Language badge
    QFrame* badge = new QFrame(card);
    badge->setFixedSize(50, 50);
    QString color  = (c.language == "C++") ? "#0d1f5c" : "#1a0a40";
    QString border = (c.language == "C++") ? "#1a3a99" : "#3b1a99";
    badge->setStyleSheet(QString(
                             "QFrame{background:%1;border-radius:12px;"
                             "border:1px solid %2;}").arg(color, border));
    QLabel* badgeTxt = new QLabel(
        c.language == "C++" ? "C++" : "Py", badge);
    badgeTxt->setGeometry(0, 0, 50, 50);
    badgeTxt->setAlignment(Qt::AlignCenter);
    badgeTxt->setStyleSheet(
        "color:#93c5fd;font-size:11px;font-weight:bold;"
        "background:transparent;");
    row->addWidget(badge);

    // Info
    QVBoxLayout* info = new QVBoxLayout();
    info->setSpacing(4);

    QHBoxLayout* titleRow = new QHBoxLayout();
    QLabel* title = new QLabel(c.title);
    title->setStyleSheet(
        "color:#e2e8f0;font-size:14px;"
        "font-weight:bold;background:transparent;");
    QLabel* diff = new QLabel(c.difficultytext());
    diff->setFixedHeight(20);
    diff->setMinimumWidth(90);
    diff->setAlignment(Qt::AlignCenter);
    diff->setStyleSheet(QString(
                            "QLabel{color:%1;background:transparent;"
                            "border:1px solid %1;border-radius:10px;"
                            "font-size:10px;font-weight:bold;padding:0 8px;}").arg(c.difficultycolor()));
    titleRow->addWidget(title);
    titleRow->addWidget(diff);
    titleRow->addStretch();
    info->addLayout(titleRow);

    QLabel* desc = new QLabel(c.description);
    desc->setStyleSheet("color:#334155;font-size:12px;background:transparent;");
    desc->setWordWrap(true);
    info->addWidget(desc);

    QLabel* stat = new QLabel(
        QString("%1 questions  ·  +%2 XP").arg(databasemanager::instance().getQuestionsForCourse(c.id).size()).arg(c.xpreward));
    stat->setStyleSheet("color:#1e3a5f;font-size:11px;background:transparent;");
    info->addWidget(stat);

    row->addLayout(info);

    //Quiz button : orange to distinguish from course button
    QPushButton* btn = new QPushButton("Start Quiz →", card);
    btn->setFixedSize(110, 36);
    btn->setStyleSheet(R"(
        QPushButton {
            background: #d97706;
            color: white;
            border: none;
            border-radius: 8px;
            font-size: 12px;
            font-weight: bold;
        }
        QPushButton:hover { background: #f59e0b; }
        QPushButton:pressed { background: #b45309; }
    )");

    int cId = c.id;
    QString cTitle = c.title;
    connect(btn, &QPushButton::clicked,
            [this, cId, cTitle]() {
                emit quizSelected(cId, cTitle);
            });

    row->addWidget(btn);
    layout->insertWidget(layout->count() - 1, card);
}

void quizselectwindow::on_pushButton_back_clicked() {
    emit backRequested();
}
