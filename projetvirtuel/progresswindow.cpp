#include "progresswindow.h"
#include "ui_progresswindow.h"
#include "databasemanager.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QFrame>

progresswindow::progresswindow(const QString& username,
                               QWidget* parent)
    : QWidget(parent)
    , ui(new Ui::progresswindow)
    , m_username(username)
{
    ui->setupUi(this);
    setWindowTitle("Langora — My Progress");
    setMinimumSize(900, 660);
    loadStats();
    buildHistoryCards();
}

progresswindow::~progresswindow() {
    delete ui;
}

void progresswindow::loadStats() {
    int xp      = databasemanager::instance().getUserXp(m_username);
    int level   = databasemanager::instance().getUserLevel(m_username);
    int quizzes = databasemanager::instance().getTotalQuizesDone(m_username);
    int avg     = databasemanager::instance().getAverageScore(m_username);

    ui->label_xp_val->setText(QString::number(xp));
    ui->label_level_val->setText(QString::number(level));
    ui->label_quizzes_val->setText(QString::number(quizzes));
    ui->label_avg_val->setText(QString::number(avg) + "%");

    // XP bar — level threshold = level * 100
    int threshold = level * 100;
    int barWidth  = (xp * 860) / qMax(threshold, 1);
    barWidth      = qMin(barWidth, 860);
    ui->xp_bar_fill->setFixedWidth(qMax(barWidth, 4));
    ui->label_xp_bar_text->setText(
        QString("%1 / %2 XP to level %3")
            .arg(xp).arg(threshold).arg(level + 1));
}

void progresswindow::buildHistoryCards() {
    // Set up layout inside scroll area
    QVBoxLayout* layout = new QVBoxLayout(ui->scrollContents);
    layout->setContentsMargins(20, 12, 20, 12);
    layout->setSpacing(10);

    auto history = databasemanager::instance().getQuizHistory(m_username);

    if (history.isEmpty()) {
        QLabel* empty = new QLabel("No quiz history yet — take a quiz to see your results here!");
        empty->setAlignment(Qt::AlignCenter);
        empty->setStyleSheet("color: #1e3a5f; font-size: 13px; background: transparent;");
        layout->addWidget(empty);
        layout->addStretch();
        return;
    }

    for (const auto& entry : history) {
        // Card
        QFrame* card = new QFrame();
        card->setFixedHeight(70);
        card->setStyleSheet(R"(
            QFrame {
                background: #070b14;
                border: 1px solid #0f1629;
                border-radius: 10px;
            }
        )");

        QHBoxLayout* row = new QHBoxLayout(card);
        row->setContentsMargins(16, 0, 16, 0);
        row->setSpacing(20);

        // Score circle color
        QString scoreColor = entry.score >= 80 ? "#22c55e" : entry.score >= 50 ? "#f59e0b" : "#ef4444";

        // Score badge
        QFrame* scoreBadge = new QFrame(card);
        scoreBadge->setFixedSize(50, 50);
        scoreBadge->setStyleSheet(QString(
                                      "QFrame { background: transparent; border: 2px solid %1;"
                                      "border-radius: 25px; }").arg(scoreColor));

        QLabel* scoreLabel = new QLabel(
            QString::number(entry.score) + "%", scoreBadge);
        scoreLabel->setGeometry(0, 0, 50, 50);
        scoreLabel->setAlignment(Qt::AlignCenter);
        scoreLabel->setStyleSheet(QString(
                                      "color: %1; font-size: 11px; font-weight: bold;"
                                      "background: transparent;").arg(scoreColor));

        row->addWidget(scoreBadge);

        // Course title and date
        QVBoxLayout* info = new QVBoxLayout();
        info->setSpacing(2);

        QLabel* titleLbl = new QLabel(entry.courseTitle);
        titleLbl->setStyleSheet(
            "color: #e2e8f0; font-size: 13px; font-weight: bold;"
            "background: transparent;");

        QLabel* dateLbl = new QLabel(
            QString("%1 correct of %2  ·  %3")
                .arg(entry.correct)
                .arg(entry.total)
                .arg(entry.takenAt));
        dateLbl->setStyleSheet(
            "color: #334155; font-size: 11px; background: transparent;");

        info->addWidget(titleLbl);
        info->addWidget(dateLbl);
        row->addLayout(info);
        row->addStretch();

        // XP earned
        QLabel* xpLbl = new QLabel(
            "+" + QString::number(entry.xpEarned) + " XP");
        xpLbl->setStyleSheet(
            "color: #3b82f6; font-size: 13px; font-weight: bold;"
            "background: transparent;");
        row->addWidget(xpLbl);

        layout->addWidget(card);
    }

    layout->addStretch();
}

void progresswindow::on_pushButton_back_clicked() {
    emit backRequested();
}
