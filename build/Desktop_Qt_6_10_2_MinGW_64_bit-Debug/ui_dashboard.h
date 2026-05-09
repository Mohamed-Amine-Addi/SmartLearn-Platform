/********************************************************************************
** Form generated from reading UI file 'dashboard.ui'
**
** Created by: Qt User Interface Compiler version 6.10.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DASHBOARD_H
#define UI_DASHBOARD_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_dashboard
{
public:
    QFrame *sidebar;
    QFrame *logo_area;
    QLabel *label_appname_side;
    QLabel *label_appslogan;
    QFrame *user_area;
    QLabel *label_avatar;
    QLabel *label_username_side;
    QLabel *label_level_side;
    QPushButton *nav_dashboard;
    QPushButton *pushButton_courses;
    QPushButton *pushButton_startQuiz;
    QPushButton *nav_progress;
    QPushButton *nav_badges;
    QPushButton *pushButton_logout;
    QFrame *main_area;
    QFrame *topbar;
    QLabel *label_welcome;
    QLabel *label_topbar_sub;
    QFrame *xp_badge;
    QLabel *label_xp;
    QFrame *level_badge;
    QLabel *level_label;
    QFrame *streak_bar;
    QLabel *label_streak_icon;
    QLabel *label_streak_title;
    QLabel *label_streak_sub;
    QFrame *stat1;
    QLabel *label_stat1_val;
    QLabel *label_stat1_lbl;
    QFrame *stat2;
    QLabel *label_stat2_val;
    QLabel *label_stat2_lbl;
    QFrame *stat3;
    QLabel *label_stat3_val;
    QLabel *label_stat3_lbl;
    QFrame *stat4;
    QLabel *label_stat4_val;
    QLabel *label_stat4_lbl;
    QLabel *label_section;
    QFrame *action_courses;
    QLabel *label_courses_title;
    QLabel *label_courses_sub;
    QPushButton *btn_go_courses;
    QFrame *action_quiz;
    QLabel *label_quiz_title;
    QLabel *label_quiz_sub;
    QPushButton *btn_go_quiz;
    QLabel *label_recent;
    QFrame *empty_activity;
    QLabel *label_empty;

    void setupUi(QWidget *dashboard)
    {
        if (dashboard->objectName().isEmpty())
            dashboard->setObjectName("dashboard");
        dashboard->resize(1000, 620);
        dashboard->setStyleSheet(QString::fromUtf8("QWidget#dashboard { background-color: #050810; }"));
        sidebar = new QFrame(dashboard);
        sidebar->setObjectName("sidebar");
        sidebar->setGeometry(QRect(0, 0, 200, 620));
        sidebar->setStyleSheet(QString::fromUtf8("\n"
"QFrame#sidebar {\n"
"    background-color: #070b14;\n"
"    border-right: 1px solid #0f1629;\n"
"}\n"
"    "));
        sidebar->setFrameShape(QFrame::Shape::StyledPanel);
        logo_area = new QFrame(sidebar);
        logo_area->setObjectName("logo_area");
        logo_area->setGeometry(QRect(0, 0, 200, 60));
        logo_area->setStyleSheet(QString::fromUtf8("QFrame { background: transparent; border-bottom: 1px solid #0f1629; border-right: none; }"));
        label_appname_side = new QLabel(logo_area);
        label_appname_side->setObjectName("label_appname_side");
        label_appname_side->setGeometry(QRect(16, 10, 168, 20));
        label_appname_side->setStyleSheet(QString::fromUtf8("QLabel { color: #e2e8f0; font-size: 14px; font-weight: bold; letter-spacing: 3px; background: transparent; }"));
        label_appslogan = new QLabel(logo_area);
        label_appslogan->setObjectName("label_appslogan");
        label_appslogan->setGeometry(QRect(16, 32, 168, 14));
        label_appslogan->setStyleSheet(QString::fromUtf8("QLabel { color: #1e3a5f; font-size: 9px; letter-spacing: 1px; background: transparent; }"));
        user_area = new QFrame(sidebar);
        user_area->setObjectName("user_area");
        user_area->setGeometry(QRect(0, 60, 200, 60));
        user_area->setStyleSheet(QString::fromUtf8("QFrame { background: transparent; border-bottom: 1px solid #0f1629; border-right: none; }"));
        label_avatar = new QLabel(user_area);
        label_avatar->setObjectName("label_avatar");
        label_avatar->setGeometry(QRect(14, 13, 34, 34));
        label_avatar->setStyleSheet(QString::fromUtf8("\n"
"QLabel {\n"
"    background-color: #0d1f5c;\n"
"    border-radius: 17px;\n"
"    border: 1px solid #1a3a99;\n"
"    color: #60a5fa;\n"
"    font-size: 14px;\n"
"    font-weight: bold;\n"
"}\n"
"      "));
        label_avatar->setAlignment(Qt::AlignmentFlag::AlignCenter);
        label_username_side = new QLabel(user_area);
        label_username_side->setObjectName("label_username_side");
        label_username_side->setGeometry(QRect(56, 14, 130, 16));
        label_username_side->setStyleSheet(QString::fromUtf8("QLabel { color: #cbd5e1; font-size: 12px; font-weight: bold; background: transparent; }"));
        label_level_side = new QLabel(user_area);
        label_level_side->setObjectName("label_level_side");
        label_level_side->setGeometry(QRect(56, 32, 130, 14));
        label_level_side->setStyleSheet(QString::fromUtf8("QLabel { color: #334155; font-size: 10px; background: transparent; }"));
        nav_dashboard = new QPushButton(sidebar);
        nav_dashboard->setObjectName("nav_dashboard");
        nav_dashboard->setGeometry(QRect(0, 136, 200, 40));
        nav_dashboard->setStyleSheet(QString::fromUtf8("\n"
"QPushButton {\n"
"    background-color: #070f24;\n"
"    color: #60a5fa;\n"
"    border: none;\n"
"    border-left: 3px solid #1d4ed8;\n"
"    border-radius: 0px;\n"
"    font-size: 12px;\n"
"    font-weight: bold;\n"
"    text-align: left;\n"
"    padding-left: 16px;\n"
"}\n"
"     "));
        pushButton_courses = new QPushButton(sidebar);
        pushButton_courses->setObjectName("pushButton_courses");
        pushButton_courses->setGeometry(QRect(0, 176, 200, 40));
        pushButton_courses->setStyleSheet(QString::fromUtf8("\n"
"QPushButton {\n"
"    background: transparent;\n"
"    color: #334155;\n"
"    border: none;\n"
"    border-left: 3px solid transparent;\n"
"    border-radius: 0px;\n"
"    font-size: 12px;\n"
"    text-align: left;\n"
"    padding-left: 16px;\n"
"}\n"
"QPushButton:hover {\n"
"    background-color: #070f1a;\n"
"    color: #60a5fa;\n"
"    border-left-color: #1d4ed8;\n"
"}\n"
"     "));
        pushButton_startQuiz = new QPushButton(sidebar);
        pushButton_startQuiz->setObjectName("pushButton_startQuiz");
        pushButton_startQuiz->setGeometry(QRect(0, 216, 200, 40));
        pushButton_startQuiz->setStyleSheet(QString::fromUtf8("\n"
"QPushButton {\n"
"    background: transparent;\n"
"    color: #334155;\n"
"    border: none;\n"
"    border-left: 3px solid transparent;\n"
"    border-radius: 0px;\n"
"    font-size: 12px;\n"
"    text-align: left;\n"
"    padding-left: 16px;\n"
"}\n"
"QPushButton:hover {\n"
"    background-color: #070f1a;\n"
"    color: #60a5fa;\n"
"    border-left-color: #1d4ed8;\n"
"}\n"
"     "));
        nav_progress = new QPushButton(sidebar);
        nav_progress->setObjectName("nav_progress");
        nav_progress->setGeometry(QRect(0, 256, 200, 40));
        nav_progress->setStyleSheet(QString::fromUtf8("\n"
"QPushButton {\n"
"    background: transparent;\n"
"    color: #334155;\n"
"    border: none;\n"
"    border-left: 3px solid transparent;\n"
"    border-radius: 0px;\n"
"    font-size: 12px;\n"
"    text-align: left;\n"
"    padding-left: 16px;\n"
"}\n"
"QPushButton:hover { background-color: #070f1a; color: #60a5fa; }\n"
"     "));
        nav_badges = new QPushButton(sidebar);
        nav_badges->setObjectName("nav_badges");
        nav_badges->setGeometry(QRect(0, 296, 200, 40));
        nav_badges->setStyleSheet(QString::fromUtf8("\n"
"QPushButton {\n"
"    background: transparent;\n"
"    color: #334155;\n"
"    border: none;\n"
"    border-left: 3px solid transparent;\n"
"    border-radius: 0px;\n"
"    font-size: 12px;\n"
"    text-align: left;\n"
"    padding-left: 16px;\n"
"}\n"
"QPushButton:hover { background-color: #070f1a; color: #60a5fa; }\n"
"     "));
        pushButton_logout = new QPushButton(sidebar);
        pushButton_logout->setObjectName("pushButton_logout");
        pushButton_logout->setGeometry(QRect(0, 560, 200, 60));
        pushButton_logout->setStyleSheet(QString::fromUtf8("\n"
"QPushButton {\n"
"    background: transparent;\n"
"    color: #ef4444;\n"
"    border: none;\n"
"    border-top: 1px solid #0f1629;\n"
"    border-left: 3px solid transparent;\n"
"    border-radius: 0px;\n"
"    font-size: 12px;\n"
"    text-align: left;\n"
"    padding-left: 16px;\n"
"}\n"
"QPushButton:hover {\n"
"    background-color: #150505;\n"
"    border-left-color: #ef4444;\n"
"}\n"
"     "));
        main_area = new QFrame(dashboard);
        main_area->setObjectName("main_area");
        main_area->setGeometry(QRect(200, 0, 800, 620));
        main_area->setStyleSheet(QString::fromUtf8("QFrame#main_area { background-color: #050810; border: none; }"));
        main_area->setFrameShape(QFrame::Shape::StyledPanel);
        topbar = new QFrame(main_area);
        topbar->setObjectName("topbar");
        topbar->setGeometry(QRect(0, 0, 800, 70));
        topbar->setStyleSheet(QString::fromUtf8("QFrame { background-color: #070b14; border-bottom: 1px solid #0f1629; border-left: none; border-right: none; border-top: none; }"));
        label_welcome = new QLabel(topbar);
        label_welcome->setObjectName("label_welcome");
        label_welcome->setGeometry(QRect(24, 10, 400, 26));
        label_welcome->setStyleSheet(QString::fromUtf8("QLabel { color: #e2e8f0; font-size: 16px; font-weight: bold; background: transparent; }"));
        label_topbar_sub = new QLabel(topbar);
        label_topbar_sub->setObjectName("label_topbar_sub");
        label_topbar_sub->setGeometry(QRect(24, 38, 400, 16));
        label_topbar_sub->setStyleSheet(QString::fromUtf8("QLabel { color: #1e3a5f; font-size: 11px; background: transparent; }"));
        xp_badge = new QFrame(topbar);
        xp_badge->setObjectName("xp_badge");
        xp_badge->setGeometry(QRect(580, 17, 90, 36));
        xp_badge->setStyleSheet(QString::fromUtf8("QFrame { background: #0d1f3c; border: 1px solid #1e3a5f; border-radius: 18px; }"));
        label_xp = new QLabel(xp_badge);
        label_xp->setObjectName("label_xp");
        label_xp->setGeometry(QRect(0, 0, 90, 36));
        label_xp->setStyleSheet(QString::fromUtf8("QLabel { color: #3b82f6; font-size: 13px; font-weight: bold; background: transparent; border: none; }"));
        label_xp->setAlignment(Qt::AlignmentFlag::AlignCenter);
        level_badge = new QFrame(topbar);
        level_badge->setObjectName("level_badge");
        level_badge->setGeometry(QRect(682, 17, 90, 36));
        level_badge->setStyleSheet(QString::fromUtf8("QFrame { background: #1a1200; border: 1px solid #3d2600; border-radius: 18px; }"));
        level_label = new QLabel(level_badge);
        level_label->setObjectName("level_label");
        level_label->setGeometry(QRect(0, 0, 90, 36));
        level_label->setStyleSheet(QString::fromUtf8("QLabel { color: #f59e0b; font-size: 13px; font-weight: bold; background: transparent; border: none; }"));
        level_label->setAlignment(Qt::AlignmentFlag::AlignCenter);
        streak_bar = new QFrame(main_area);
        streak_bar->setObjectName("streak_bar");
        streak_bar->setGeometry(QRect(24, 86, 752, 60));
        streak_bar->setStyleSheet(QString::fromUtf8("\n"
"QFrame {\n"
"    background-color: #0a0d18;\n"
"    border: 1px solid #1a2540;\n"
"    border-radius: 12px;\n"
"}\n"
"     "));
        label_streak_icon = new QLabel(streak_bar);
        label_streak_icon->setObjectName("label_streak_icon");
        label_streak_icon->setGeometry(QRect(14, 14, 32, 32));
        label_streak_icon->setStyleSheet(QString::fromUtf8("QLabel { background: #1a0f00; border: 1px solid #3d2600; border-radius: 8px; color: #f97316; font-size: 15px; font-weight: bold; }"));
        label_streak_icon->setAlignment(Qt::AlignmentFlag::AlignCenter);
        label_streak_title = new QLabel(streak_bar);
        label_streak_title->setObjectName("label_streak_title");
        label_streak_title->setGeometry(QRect(56, 12, 400, 18));
        label_streak_title->setStyleSheet(QString::fromUtf8("QLabel { color: #e2e8f0; font-size: 13px; font-weight: bold; background: transparent; }"));
        label_streak_sub = new QLabel(streak_bar);
        label_streak_sub->setObjectName("label_streak_sub");
        label_streak_sub->setGeometry(QRect(56, 32, 400, 14));
        label_streak_sub->setStyleSheet(QString::fromUtf8("QLabel { color: #334155; font-size: 11px; background: transparent; }"));
        stat1 = new QFrame(main_area);
        stat1->setObjectName("stat1");
        stat1->setGeometry(QRect(24, 164, 174, 80));
        stat1->setStyleSheet(QString::fromUtf8("QFrame { background: #070b14; border: 1px solid #0f1629; border-radius: 10px; }"));
        label_stat1_val = new QLabel(stat1);
        label_stat1_val->setObjectName("label_stat1_val");
        label_stat1_val->setGeometry(QRect(16, 14, 142, 28));
        label_stat1_val->setStyleSheet(QString::fromUtf8("QLabel { color: #3b82f6; font-size: 22px; font-weight: bold; background: transparent; }"));
        label_stat1_lbl = new QLabel(stat1);
        label_stat1_lbl->setObjectName("label_stat1_lbl");
        label_stat1_lbl->setGeometry(QRect(16, 44, 142, 16));
        label_stat1_lbl->setStyleSheet(QString::fromUtf8("QLabel { color: #1e3a5f; font-size: 11px; background: transparent; }"));
        stat2 = new QFrame(main_area);
        stat2->setObjectName("stat2");
        stat2->setGeometry(QRect(206, 164, 174, 80));
        stat2->setStyleSheet(QString::fromUtf8("QFrame { background: #070b14; border: 1px solid #0f1629; border-radius: 10px; }"));
        label_stat2_val = new QLabel(stat2);
        label_stat2_val->setObjectName("label_stat2_val");
        label_stat2_val->setGeometry(QRect(16, 14, 142, 28));
        label_stat2_val->setStyleSheet(QString::fromUtf8("QLabel { color: #22c55e; font-size: 22px; font-weight: bold; background: transparent; }"));
        label_stat2_lbl = new QLabel(stat2);
        label_stat2_lbl->setObjectName("label_stat2_lbl");
        label_stat2_lbl->setGeometry(QRect(16, 44, 142, 16));
        label_stat2_lbl->setStyleSheet(QString::fromUtf8("QLabel { color: #1e3a5f; font-size: 11px; background: transparent; }"));
        stat3 = new QFrame(main_area);
        stat3->setObjectName("stat3");
        stat3->setGeometry(QRect(388, 164, 174, 80));
        stat3->setStyleSheet(QString::fromUtf8("QFrame { background: #070b14; border: 1px solid #0f1629; border-radius: 10px; }"));
        label_stat3_val = new QLabel(stat3);
        label_stat3_val->setObjectName("label_stat3_val");
        label_stat3_val->setGeometry(QRect(16, 14, 142, 28));
        label_stat3_val->setStyleSheet(QString::fromUtf8("QLabel { color: #f59e0b; font-size: 22px; font-weight: bold; background: transparent; }"));
        label_stat3_lbl = new QLabel(stat3);
        label_stat3_lbl->setObjectName("label_stat3_lbl");
        label_stat3_lbl->setGeometry(QRect(16, 44, 142, 16));
        label_stat3_lbl->setStyleSheet(QString::fromUtf8("QLabel { color: #1e3a5f; font-size: 11px; background: transparent; }"));
        stat4 = new QFrame(main_area);
        stat4->setObjectName("stat4");
        stat4->setGeometry(QRect(570, 164, 206, 80));
        stat4->setStyleSheet(QString::fromUtf8("QFrame { background: #070b14; border: 1px solid #0f1629; border-radius: 10px; }"));
        label_stat4_val = new QLabel(stat4);
        label_stat4_val->setObjectName("label_stat4_val");
        label_stat4_val->setGeometry(QRect(16, 14, 174, 28));
        label_stat4_val->setStyleSheet(QString::fromUtf8("QLabel { color: #a855f7; font-size: 22px; font-weight: bold; background: transparent; }"));
        label_stat4_lbl = new QLabel(stat4);
        label_stat4_lbl->setObjectName("label_stat4_lbl");
        label_stat4_lbl->setGeometry(QRect(16, 44, 174, 16));
        label_stat4_lbl->setStyleSheet(QString::fromUtf8("QLabel { color: #1e3a5f; font-size: 11px; background: transparent; }"));
        label_section = new QLabel(main_area);
        label_section->setObjectName("label_section");
        label_section->setGeometry(QRect(24, 262, 400, 16));
        label_section->setStyleSheet(QString::fromUtf8("QLabel { color: #334155; font-size: 10px; font-weight: bold; letter-spacing: 1px; background: transparent; }"));
        action_courses = new QFrame(main_area);
        action_courses->setObjectName("action_courses");
        action_courses->setGeometry(QRect(24, 286, 366, 90));
        action_courses->setStyleSheet(QString::fromUtf8("\n"
"QFrame {\n"
"    background-color: #0a0f1e;\n"
"    border: 1px solid #1d4ed8;\n"
"    border-radius: 12px;\n"
"}\n"
"QFrame:hover { background-color: #0d1428; }\n"
"     "));
        label_courses_title = new QLabel(action_courses);
        label_courses_title->setObjectName("label_courses_title");
        label_courses_title->setGeometry(QRect(16, 16, 260, 22));
        label_courses_title->setStyleSheet(QString::fromUtf8("QLabel { color: #60a5fa; font-size: 14px; font-weight: bold; background: transparent; }"));
        label_courses_sub = new QLabel(action_courses);
        label_courses_sub->setObjectName("label_courses_sub");
        label_courses_sub->setGeometry(QRect(16, 40, 260, 16));
        label_courses_sub->setStyleSheet(QString::fromUtf8("QLabel { color: #334155; font-size: 11px; background: transparent; }"));
        btn_go_courses = new QPushButton(action_courses);
        btn_go_courses->setObjectName("btn_go_courses");
        btn_go_courses->setGeometry(QRect(280, 20, 76, 36));
        btn_go_courses->setStyleSheet(QString::fromUtf8("\n"
"QPushButton {\n"
"    background: #1d4ed8;\n"
"    color: white;\n"
"    border: none;\n"
"    border-radius: 8px;\n"
"    font-size: 12px;\n"
"    font-weight: bold;\n"
"}\n"
"QPushButton:hover { background: #2563eb; }\n"
"      "));
        action_quiz = new QFrame(main_area);
        action_quiz->setObjectName("action_quiz");
        action_quiz->setGeometry(QRect(408, 286, 368, 90));
        action_quiz->setStyleSheet(QString::fromUtf8("\n"
"QFrame {\n"
"    background-color: #0f0a00;\n"
"    border: 1px solid #f59e0b;\n"
"    border-radius: 12px;\n"
"}\n"
"QFrame:hover { background-color: #130d00; }\n"
"     "));
        label_quiz_title = new QLabel(action_quiz);
        label_quiz_title->setObjectName("label_quiz_title");
        label_quiz_title->setGeometry(QRect(16, 16, 260, 22));
        label_quiz_title->setStyleSheet(QString::fromUtf8("QLabel { color: #f59e0b; font-size: 14px; font-weight: bold; background: transparent; }"));
        label_quiz_sub = new QLabel(action_quiz);
        label_quiz_sub->setObjectName("label_quiz_sub");
        label_quiz_sub->setGeometry(QRect(16, 40, 260, 16));
        label_quiz_sub->setStyleSheet(QString::fromUtf8("QLabel { color: #334155; font-size: 11px; background: transparent; }"));
        btn_go_quiz = new QPushButton(action_quiz);
        btn_go_quiz->setObjectName("btn_go_quiz");
        btn_go_quiz->setGeometry(QRect(274, 27, 78, 36));
        btn_go_quiz->setStyleSheet(QString::fromUtf8("\n"
"QPushButton {\n"
"    background: #d97706;\n"
"    color: white;\n"
"    border: none;\n"
"    border-radius: 8px;\n"
"    font-size: 12px;\n"
"    font-weight: bold;\n"
"}\n"
"QPushButton:hover { background: #f59e0b; }\n"
"      "));
        label_recent = new QLabel(main_area);
        label_recent->setObjectName("label_recent");
        label_recent->setGeometry(QRect(24, 394, 400, 16));
        label_recent->setStyleSheet(QString::fromUtf8("QLabel { color: #334155; font-size: 10px; font-weight: bold; letter-spacing: 1px; background: transparent; }"));
        empty_activity = new QFrame(main_area);
        empty_activity->setObjectName("empty_activity");
        empty_activity->setGeometry(QRect(24, 418, 752, 80));
        empty_activity->setStyleSheet(QString::fromUtf8("QFrame { background: #070b14; border: 1px dashed #0f1629; border-radius: 10px; }"));
        label_empty = new QLabel(empty_activity);
        label_empty->setObjectName("label_empty");
        label_empty->setGeometry(QRect(0, 0, 752, 80));
        label_empty->setStyleSheet(QString::fromUtf8("QLabel { color: #1e3a5f; font-size: 12px; background: transparent; }"));
        label_empty->setAlignment(Qt::AlignmentFlag::AlignCenter);

        retranslateUi(dashboard);

        QMetaObject::connectSlotsByName(dashboard);
    } // setupUi

    void retranslateUi(QWidget *dashboard)
    {
        dashboard->setWindowTitle(QCoreApplication::translate("dashboard", "Langora", nullptr));
        label_appname_side->setText(QCoreApplication::translate("dashboard", "LANGORA", nullptr));
        label_appslogan->setText(QCoreApplication::translate("dashboard", "LEARN \302\267 QUIZ \302\267 GROW", nullptr));
        label_avatar->setText(QCoreApplication::translate("dashboard", "A", nullptr));
        label_username_side->setText(QCoreApplication::translate("dashboard", "username", nullptr));
        label_level_side->setText(QCoreApplication::translate("dashboard", "Level 1 learner", nullptr));
        nav_dashboard->setText(QCoreApplication::translate("dashboard", "  Dashboard", nullptr));
        pushButton_courses->setText(QCoreApplication::translate("dashboard", "  Courses", nullptr));
        pushButton_startQuiz->setText(QCoreApplication::translate("dashboard", "  Quiz", nullptr));
        nav_progress->setText(QCoreApplication::translate("dashboard", "  Progress", nullptr));
        nav_badges->setText(QCoreApplication::translate("dashboard", "  Badges", nullptr));
        pushButton_logout->setText(QCoreApplication::translate("dashboard", "  Log out", nullptr));
        label_welcome->setText(QCoreApplication::translate("dashboard", "Welcome back, username!", nullptr));
        label_topbar_sub->setText(QCoreApplication::translate("dashboard", "Keep learning every day", nullptr));
        label_xp->setText(QCoreApplication::translate("dashboard", "0 XP", nullptr));
        level_label->setText(QCoreApplication::translate("dashboard", "Level 1", nullptr));
        label_streak_icon->setText(QCoreApplication::translate("dashboard", "0", nullptr));
        label_streak_title->setText(QCoreApplication::translate("dashboard", "Start your streak today!", nullptr));
        label_streak_sub->setText(QCoreApplication::translate("dashboard", "Complete a lesson each day to build your streak", nullptr));
        label_stat1_val->setText(QCoreApplication::translate("dashboard", "0", nullptr));
        label_stat1_lbl->setText(QCoreApplication::translate("dashboard", "Total XP earned", nullptr));
        label_stat2_val->setText(QCoreApplication::translate("dashboard", "0", nullptr));
        label_stat2_lbl->setText(QCoreApplication::translate("dashboard", "Courses started", nullptr));
        label_stat3_val->setText(QCoreApplication::translate("dashboard", "0", nullptr));
        label_stat3_lbl->setText(QCoreApplication::translate("dashboard", "Quizzes completed", nullptr));
        label_stat4_val->setText(QCoreApplication::translate("dashboard", "0", nullptr));
        label_stat4_lbl->setText(QCoreApplication::translate("dashboard", "Badges earned", nullptr));
        label_section->setText(QCoreApplication::translate("dashboard", "QUICK ACTIONS", nullptr));
        label_courses_title->setText(QCoreApplication::translate("dashboard", "Browse Courses", nullptr));
        label_courses_sub->setText(QCoreApplication::translate("dashboard", "8 courses available \302\267 C++ and Python", nullptr));
        btn_go_courses->setText(QCoreApplication::translate("dashboard", "Open \342\206\222", nullptr));
        label_quiz_title->setText(QCoreApplication::translate("dashboard", "Start a Quiz", nullptr));
        label_quiz_sub->setText(QCoreApplication::translate("dashboard", "Test your knowledge \302\267 Earn XP rewards", nullptr));
        btn_go_quiz->setText(QCoreApplication::translate("dashboard", "Start \342\206\222", nullptr));
        label_recent->setText(QCoreApplication::translate("dashboard", "RECENT ACTIVITY", nullptr));
        label_empty->setText(QCoreApplication::translate("dashboard", "No activity yet \342\200\224 start a course or take a quiz to see your history here", nullptr));
    } // retranslateUi

};

namespace Ui {
    class dashboard: public Ui_dashboard {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DASHBOARD_H
