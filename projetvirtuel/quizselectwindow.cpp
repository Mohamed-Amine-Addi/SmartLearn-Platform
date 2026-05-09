#include "quizselectwindow.h"
#include "ui_quizselectwindow.h"
#include "databasemanager.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QFrame>

quizselectwindow::quizselectwindow(const QString& username,
                                   QWidget* parent)
    : QWidget(parent)
    , ui(new Ui::quizselectwindow)
    , m_username(username)
{
    ui->setupUi(this);
    setWindowTitle("Langora — Select Quiz");
    setMinimumSize(900, 600);

    m_layout = new QVBoxLayout(ui->scrollContents);
    m_layout->setContentsMargins(20, 16, 20, 16);
    m_layout->setSpacing(10);
    m_layout->addStretch();

    loadCards("");
}

quizselectwindow::~quizselectwindow() { delete ui; }

void quizselectwindow::on_btn_filter_all_clicked() {
    setFilter("all");
    loadCards("");
}
void quizselectwindow::on_btn_filter_cpp_clicked() {
    setFilter("cpp");
    loadCards("C++");
}
void quizselectwindow::on_btn_filter_python_clicked() {
    setFilter("python");
    loadCards("Python");
}

void quizselectwindow::setFilter(const QString& active) {
    QString on  = "QPushButton{background:#0d1f3c;color:#60a5fa;"
                  "border:1px solid #1d4ed8;border-radius:14px;"
                  "font-size:11px;font-weight:bold;}";
    QString off = "QPushButton{background:transparent;color:#334155;"
                  "border:1px solid #0f1629;border-radius:14px;"
                  "font-size:11px;font-weight:bold;}"
                  "QPushButton:hover{background:#0d1f3c;"
                  "color:#60a5fa;border-color:#1d4ed8;}";
    ui->btn_filter_all->setStyleSheet(active=="all"?on:off);
    ui->btn_filter_cpp->setStyleSheet(active=="cpp"?on:off);
    ui->btn_filter_python->setStyleSheet(active=="python"?on:off);
}

void quizselectwindow::loadCards(const QString& filter) {
    // Remove old cards
    while (m_layout->count() > 1) {
        QLayoutItem* item = m_layout->takeAt(0);
        if (item->widget()) item->widget()->deleteLater();
        delete item;
    }
    QList<course> courses =
        databasemanager::instance().getAllCourses();
    for (const course& c : courses) {
        if (!filter.isEmpty() && c.language != filter)
            continue;
        buildCard(c, m_layout);
    }
}

void quizselectwindow::buildCard(const course& c,
                                  QVBoxLayout* layout)
{
    // How many questions does this course have?
    int qCount = databasemanager::instance()
                     .getQuestionsForCourse(c.id).size();

    QFrame* card = new QFrame();
    card->setFixedHeight(100);
    card->setStyleSheet(R"(
        QFrame{background:#070b14;border:1px solid #0f1629;
               border-radius:12px;}
        QFrame:hover{border-color:#f59e0b;background:#080d18;})");

    QHBoxLayout* row = new QHBoxLayout(card);
    row->setContentsMargins(18, 0, 18, 0);
    row->setSpacing(16);

    // Language badge
    QFrame* badge = new QFrame(card);
    badge->setFixedSize(50, 50);
    QString bg  = (c.language=="C++") ? "#0d1f5c" : "#1a0a40";
    QString bdr = (c.language=="C++") ? "#1a3a99" : "#3b1a99";
    badge->setStyleSheet(QString(
        "QFrame{background:%1;border-radius:12px;"
        "border:1px solid %2;}").arg(bg, bdr));
    QLabel* blbl = new QLabel(
        c.language=="C++" ? "C++" : "Py", badge);
    blbl->setGeometry(0, 0, 50, 50);
    blbl->setAlignment(Qt::AlignCenter);
    blbl->setStyleSheet("color:#93c5fd;font-size:11px;"
                        "font-weight:bold;background:transparent;");
    row->addWidget(badge);

    // Info
    QVBoxLayout* info = new QVBoxLayout();
    info->setSpacing(4);

    QHBoxLayout* titleRow = new QHBoxLayout();
    titleRow->setSpacing(10);
    QLabel* title = new QLabel(c.title);
    title->setStyleSheet("color:#e2e8f0;font-size:14px;"
                         "font-weight:bold;background:transparent;");
    QLabel* diff = new QLabel(c.difficultytext());
    diff->setFixedHeight(20);
    diff->setMinimumWidth(90);
    diff->setAlignment(Qt::AlignCenter);
    diff->setStyleSheet(QString(
        "QLabel{color:%1;background:transparent;"
        "border:1px solid %1;border-radius:10px;"
        "font-size:10px;font-weight:bold;padding:0 8px;}")
        .arg(c.difficultycolor()));
    titleRow->addWidget(title);
    titleRow->addWidget(diff);
    titleRow->addStretch();
    info->addLayout(titleRow);

    QLabel* desc = new QLabel(c.description);
    desc->setStyleSheet("color:#334155;font-size:12px;"
                        "background:transparent;");
    desc->setWordWrap(true);
    info->addWidget(desc);

    // Stats row
    QHBoxLayout* stats = new QHBoxLayout();
    stats->setSpacing(20);
    auto mkStat = [](const QString& t) {
        QLabel* l = new QLabel(t);
        l->setStyleSheet("color:#1e3a5f;font-size:11px;"
                         "background:transparent;");
        return l;
    };
    stats->addWidget(mkStat(QString("%1 questions").arg(qCount)));
    stats->addWidget(mkStat(QString("+%1 XP on completion")
                                .arg(c.xpreward)));
    stats->addStretch();
    info->addLayout(stats);
    row->addLayout(info);

    // Orange quiz button
    QPushButton* btn = new QPushButton("Start Quiz →", card);
    btn->setFixedSize(110, 38);
    btn->setStyleSheet(R"(
        QPushButton{background:#d97706;color:white;
        border:none;border-radius:8px;
        font-size:12px;font-weight:bold;}
        QPushButton:hover{background:#f59e0b;}
        QPushButton:pressed{background:#b45309;})");

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
