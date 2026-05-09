#include "dashboard.h"
#include "ui_dashboard.h"
#include "databasemanager.h"
#include "badge.h"
#include "quizhistoryentry.h"
#include <QFrame>
#include <QLabel>

dashboard::dashboard(const QString& username, QWidget* parent)
    : QWidget(parent)
    , ui(new Ui::dashboard)
    , m_username(username)
{
    ui->setupUi(this);
    setWindowTitle("Langora");
    loadUserStats();
    connect(ui->btn_go_courses, &QPushButton::clicked,
            this, &dashboard::openCoursesRequested);
    connect(ui->btn_go_quiz, &QPushButton::clicked,
            this, &dashboard::openQuizRequested);
}

dashboard::~dashboard() {
    delete ui;
}

void dashboard::loadUserStats() {
    QString firstName = databasemanager::instance()
                            .getUserFirstname(m_username);
    int xp      = databasemanager::instance().getUserXp(m_username);
    int level   = databasemanager::instance().getUserLevel(m_username);
    int streak  = databasemanager::instance().getUserStreak(m_username);
    int quizzes = databasemanager::instance()
                      .getTotalQuizesDone(m_username);
    int started = databasemanager::instance()
                      .getCoursesStarted(m_username);

    // Count unlocked badges
    int unlockedBadges = 0;
    for (const Badge& b :
         databasemanager::instance().getUserBadges(m_username))
        if (b.unlocked) unlockedBadges++;

    // Welcome + sidebar
    ui->label_welcome->setText(
        "Welcome back, " + firstName + "!");
    ui->label_username_side->setText(m_username);
    ui->label_level_side->setText(
        "Level " + QString::number(level) + " learner");
    ui->label_xp->setText(QString::number(xp) + " XP");
    ui->level_label->setText("Level " + QString::number(level));
    if (!firstName.isEmpty())
        ui->label_avatar->setText(
            QString(firstName[0]).toUpper());

    // Streak icon — orange border when active
    ui->label_streak_icon->setText(QString::number(streak));
    if (streak > 0) {
        ui->label_streak_icon->setStyleSheet(
            "QLabel{background:#1a0f00;border:2px solid #f97316;"
            "border-radius:8px;color:#f97316;"
            "font-size:15px;font-weight:bold;}");
        ui->label_streak_title->setText(
            QString("%1-day streak — keep it going!").arg(streak));
        ui->label_streak_sub->setText(
            QString("You last studied today · %1 XP total").arg(xp));
    } else {
        ui->label_streak_icon->setStyleSheet(
            "QLabel{background:#0a0f1e;border:1px solid #0f1629;"
            "border-radius:8px;color:#1e3a5f;"
            "font-size:15px;font-weight:bold;}");
        ui->label_streak_title->setText("Start your streak today!");
        ui->label_streak_sub->setText(
            "Complete a lesson each day to build your streak");
    }

    // XP progress bar — fills proportionally toward next level
    int threshold = level * 100;
    int barWidth  = qMin((xp * 172) / qMax(threshold, 1), 172);
    ui->xp_bar_fill->setFixedWidth(qMax(barWidth, 4));
    ui->label_xp_bar_text->setText(
        QString("%1 / %2 XP to level %3")
            .arg(xp).arg(threshold).arg(level + 1));

    // 4 stat cards — values only (icons are in the .ui)
    ui->label_stat1_val->setText(QString::number(xp));
    ui->label_stat2_val->setText(QString::number(started));
    ui->label_stat3_val->setText(QString::number(quizzes));
    ui->label_stat4_val->setText(QString::number(unlockedBadges));

    // Recent activity
    loadRecentActivity();
}

void dashboard::loadRecentActivity() {
    auto history = databasemanager::instance()
                       .getQuizHistory(m_username);

    // Remove any old dynamically-created activity cards
    QList<QFrame*> old =
        ui->main_area->findChildren<QFrame*>("activity_card");
    for (QFrame* c : old) c->deleteLater();

    if (history.isEmpty()) {
        ui->empty_activity->show();
        return;
    }

    // Hide "no activity" placeholder
    ui->empty_activity->hide();

    // Show last 3 quiz results as small cards
    int count = qMin(history.size(), 3);
    for (int i = 0; i < count; i++) {
        const QuizHistoryEntry& e = history[i];

        QFrame* card = new QFrame(ui->main_area);
        card->setObjectName("activity_card");
        // Stack cards vertically starting at y=418
        card->setGeometry(24, 418 + i * 58, 752, 50);
        card->setStyleSheet(
            "QFrame{"
            "background:#070b14;"
            "border:1px solid #0f1629;"
            "border-radius:8px;"
            "}");
        card->show();

        QString col = e.score >= 80 ? "#22c55e"
                    : e.score >= 50 ? "#f59e0b" : "#ef4444";

        // Score
        QLabel* scoreLbl = new QLabel(
            QString::number(e.score) + "%", card);
        scoreLbl->setGeometry(12, 0, 54, 50);
        scoreLbl->setAlignment(Qt::AlignCenter);
        scoreLbl->setStyleSheet(QString(
            "QLabel{color:%1;font-size:15px;"
            "font-weight:bold;background:transparent;}")
            .arg(col));
        scoreLbl->show();

        // Course title
        QLabel* titleLbl = new QLabel(e.courseTitle, card);
        titleLbl->setGeometry(72, 7, 430, 18);
        titleLbl->setStyleSheet(
            "QLabel{color:#e2e8f0;font-size:12px;"
            "font-weight:bold;background:transparent;}");
        titleLbl->show();

        // Details
        QLabel* detLbl = new QLabel(
            QString("%1 correct of %2  ·  %3")
                .arg(e.correct).arg(e.total).arg(e.takenAt),
            card);
        detLbl->setGeometry(72, 27, 430, 16);
        detLbl->setStyleSheet(
            "QLabel{color:#334155;font-size:11px;"
            "background:transparent;}");
        detLbl->show();

        // XP earned
        QLabel* xpLbl = new QLabel(
            "+" + QString::number(e.xpEarned) + " XP", card);
        xpLbl->setGeometry(590, 0, 100, 50);
        xpLbl->setAlignment(Qt::AlignCenter);
        xpLbl->setStyleSheet(
            "QLabel{color:#3b82f6;font-size:12px;"
            "font-weight:bold;background:transparent;}");
        xpLbl->show();
    }
}

void dashboard::on_pushButton_logout_clicked() {
    emit logoutRequested();
}

void dashboard::on_pushButton_courses_clicked() {
    emit openCoursesRequested();
}

void dashboard::on_pushButton_startQuiz_clicked() {
    emit openQuizRequested();
}

void dashboard::on_nav_progress_clicked() {
    emit openProgressRequested();
}

void dashboard::on_nav_badges_clicked() {
    emit openBadgesRequested();
}

void dashboard::on_nav_profile_clicked() {
    emit openProfileRequested();
}
