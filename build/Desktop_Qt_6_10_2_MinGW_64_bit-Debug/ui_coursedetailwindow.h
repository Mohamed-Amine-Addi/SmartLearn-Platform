/********************************************************************************
** Form generated from reading UI file 'coursedetailwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.10.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_COURSEDETAILWINDOW_H
#define UI_COURSEDETAILWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_coursedetailwindow
{
public:
    QFrame *topbar;
    QPushButton *pushButton_back;
    QLabel *label_course_title;
    QFrame *info_card;
    QLabel *label_lang_badge;
    QLabel *label_title_card;
    QLabel *label_difficulty_badge;
    QLabel *label_description;
    QFrame *stat_lessons;
    QLabel *label_lessons_val;
    QLabel *label_lessons_lbl;
    QFrame *stat_xp;
    QLabel *label_xp_val;
    QLabel *label_xp_lbl;
    QFrame *stat_difficulty;
    QLabel *label_diff_val;
    QLabel *label_diff_lbl;
    QFrame *stat_lang;
    QLabel *label_lang_val;
    QLabel *label_lang_lbl;
    QLabel *label_section;
    QFrame *learn_card;
    QLabel *label_learn_content;
    QPushButton *pushButton_startQuiz;

    void setupUi(QWidget *coursedetailwindow)
    {
        if (coursedetailwindow->objectName().isEmpty())
            coursedetailwindow->setObjectName("coursedetailwindow");
        coursedetailwindow->resize(860, 580);
        coursedetailwindow->setStyleSheet(QString::fromUtf8("QWidget#coursedetailwindow { background-color: #050810; }"));
        topbar = new QFrame(coursedetailwindow);
        topbar->setObjectName("topbar");
        topbar->setGeometry(QRect(0, 0, 860, 64));
        topbar->setStyleSheet(QString::fromUtf8("QFrame#topbar { background-color: #070b14; border-bottom: 1px solid #0f1629; }"));
        topbar->setFrameShape(QFrame::Shape::StyledPanel);
        pushButton_back = new QPushButton(topbar);
        pushButton_back->setObjectName("pushButton_back");
        pushButton_back->setGeometry(QRect(20, 14, 90, 36));
        pushButton_back->setStyleSheet(QString::fromUtf8("\n"
"QPushButton { background: transparent; color: #3b82f6; border: 1px solid #1e3a5f; border-radius: 8px; font-size: 13px; font-weight: bold; }\n"
"QPushButton:hover { background: #070f24; border-color: #1d4ed8; }\n"
"     "));
        label_course_title = new QLabel(topbar);
        label_course_title->setObjectName("label_course_title");
        label_course_title->setGeometry(QRect(130, 14, 500, 36));
        label_course_title->setStyleSheet(QString::fromUtf8("QLabel { color: #e2e8f0; font-size: 16px; font-weight: bold; background: transparent; }"));
        info_card = new QFrame(coursedetailwindow);
        info_card->setObjectName("info_card");
        info_card->setGeometry(QRect(30, 84, 800, 130));
        info_card->setStyleSheet(QString::fromUtf8("QFrame { background: #070b14; border: 1px solid #0f1629; border-radius: 14px; }"));
        info_card->setFrameShape(QFrame::Shape::StyledPanel);
        label_lang_badge = new QLabel(info_card);
        label_lang_badge->setObjectName("label_lang_badge");
        label_lang_badge->setGeometry(QRect(20, 20, 60, 60));
        label_lang_badge->setStyleSheet(QString::fromUtf8("QLabel { background: #0d1f5c; border-radius: 12px; border: 1px solid #1a3a99; color: #93c5fd; font-size: 13px; font-weight: bold; }"));
        label_lang_badge->setAlignment(Qt::AlignmentFlag::AlignCenter);
        label_title_card = new QLabel(info_card);
        label_title_card->setObjectName("label_title_card");
        label_title_card->setGeometry(QRect(96, 16, 500, 28));
        label_title_card->setStyleSheet(QString::fromUtf8("QLabel { color: #e2e8f0; font-size: 18px; font-weight: bold; background: transparent; }"));
        label_difficulty_badge = new QLabel(info_card);
        label_difficulty_badge->setObjectName("label_difficulty_badge");
        label_difficulty_badge->setGeometry(QRect(96, 48, 100, 22));
        label_difficulty_badge->setStyleSheet(QString::fromUtf8("QLabel { color: #22c55e; border: 1px solid #22c55e; border-radius: 11px; font-size: 11px; font-weight: bold; background: transparent; padding: 0 8px; }"));
        label_description = new QLabel(info_card);
        label_description->setObjectName("label_description");
        label_description->setGeometry(QRect(96, 76, 680, 40));
        label_description->setStyleSheet(QString::fromUtf8("QLabel { color: #334155; font-size: 13px; background: transparent; }"));
        label_description->setWordWrap(true);
        stat_lessons = new QFrame(coursedetailwindow);
        stat_lessons->setObjectName("stat_lessons");
        stat_lessons->setGeometry(QRect(30, 234, 190, 80));
        stat_lessons->setStyleSheet(QString::fromUtf8("QFrame { background: #070b14; border: 1px solid #0f1629; border-radius: 10px; }"));
        label_lessons_val = new QLabel(stat_lessons);
        label_lessons_val->setObjectName("label_lessons_val");
        label_lessons_val->setGeometry(QRect(0, 12, 190, 30));
        label_lessons_val->setStyleSheet(QString::fromUtf8("QLabel { color: #3b82f6; font-size: 24px; font-weight: bold; background: transparent; }"));
        label_lessons_val->setAlignment(Qt::AlignmentFlag::AlignCenter);
        label_lessons_lbl = new QLabel(stat_lessons);
        label_lessons_lbl->setObjectName("label_lessons_lbl");
        label_lessons_lbl->setGeometry(QRect(0, 46, 190, 18));
        label_lessons_lbl->setStyleSheet(QString::fromUtf8("QLabel { color: #1e3a5f; font-size: 11px; background: transparent; }"));
        label_lessons_lbl->setAlignment(Qt::AlignmentFlag::AlignCenter);
        stat_xp = new QFrame(coursedetailwindow);
        stat_xp->setObjectName("stat_xp");
        stat_xp->setGeometry(QRect(236, 234, 190, 80));
        stat_xp->setStyleSheet(QString::fromUtf8("QFrame { background: #070b14; border: 1px solid #0f1629; border-radius: 10px; }"));
        label_xp_val = new QLabel(stat_xp);
        label_xp_val->setObjectName("label_xp_val");
        label_xp_val->setGeometry(QRect(0, 12, 190, 30));
        label_xp_val->setStyleSheet(QString::fromUtf8("QLabel { color: #f59e0b; font-size: 24px; font-weight: bold; background: transparent; }"));
        label_xp_val->setAlignment(Qt::AlignmentFlag::AlignCenter);
        label_xp_lbl = new QLabel(stat_xp);
        label_xp_lbl->setObjectName("label_xp_lbl");
        label_xp_lbl->setGeometry(QRect(0, 46, 190, 18));
        label_xp_lbl->setStyleSheet(QString::fromUtf8("QLabel { color: #1e3a5f; font-size: 11px; background: transparent; }"));
        label_xp_lbl->setAlignment(Qt::AlignmentFlag::AlignCenter);
        stat_difficulty = new QFrame(coursedetailwindow);
        stat_difficulty->setObjectName("stat_difficulty");
        stat_difficulty->setGeometry(QRect(442, 234, 190, 80));
        stat_difficulty->setStyleSheet(QString::fromUtf8("QFrame { background: #070b14; border: 1px solid #0f1629; border-radius: 10px; }"));
        label_diff_val = new QLabel(stat_difficulty);
        label_diff_val->setObjectName("label_diff_val");
        label_diff_val->setGeometry(QRect(0, 12, 190, 30));
        label_diff_val->setStyleSheet(QString::fromUtf8("QLabel { color: #22c55e; font-size: 18px; font-weight: bold; background: transparent; }"));
        label_diff_val->setAlignment(Qt::AlignmentFlag::AlignCenter);
        label_diff_lbl = new QLabel(stat_difficulty);
        label_diff_lbl->setObjectName("label_diff_lbl");
        label_diff_lbl->setGeometry(QRect(0, 46, 190, 18));
        label_diff_lbl->setStyleSheet(QString::fromUtf8("QLabel { color: #1e3a5f; font-size: 11px; background: transparent; }"));
        label_diff_lbl->setAlignment(Qt::AlignmentFlag::AlignCenter);
        stat_lang = new QFrame(coursedetailwindow);
        stat_lang->setObjectName("stat_lang");
        stat_lang->setGeometry(QRect(648, 234, 182, 80));
        stat_lang->setStyleSheet(QString::fromUtf8("QFrame { background: #070b14; border: 1px solid #0f1629; border-radius: 10px; }"));
        label_lang_val = new QLabel(stat_lang);
        label_lang_val->setObjectName("label_lang_val");
        label_lang_val->setGeometry(QRect(0, 12, 182, 30));
        label_lang_val->setStyleSheet(QString::fromUtf8("QLabel { color: #a855f7; font-size: 18px; font-weight: bold; background: transparent; }"));
        label_lang_val->setAlignment(Qt::AlignmentFlag::AlignCenter);
        label_lang_lbl = new QLabel(stat_lang);
        label_lang_lbl->setObjectName("label_lang_lbl");
        label_lang_lbl->setGeometry(QRect(0, 46, 182, 18));
        label_lang_lbl->setStyleSheet(QString::fromUtf8("QLabel { color: #1e3a5f; font-size: 11px; background: transparent; }"));
        label_lang_lbl->setAlignment(Qt::AlignmentFlag::AlignCenter);
        label_section = new QLabel(coursedetailwindow);
        label_section->setObjectName("label_section");
        label_section->setGeometry(QRect(30, 334, 800, 16));
        label_section->setStyleSheet(QString::fromUtf8("QLabel { color: #334155; font-size: 10px; font-weight: bold; letter-spacing: 1px; background: transparent; }"));
        learn_card = new QFrame(coursedetailwindow);
        learn_card->setObjectName("learn_card");
        learn_card->setGeometry(QRect(30, 358, 800, 100));
        learn_card->setStyleSheet(QString::fromUtf8("QFrame { background: #070b14; border: 1px solid #0f1629; border-radius: 12px; }"));
        label_learn_content = new QLabel(learn_card);
        label_learn_content->setObjectName("label_learn_content");
        label_learn_content->setGeometry(QRect(20, 14, 760, 72));
        label_learn_content->setStyleSheet(QString::fromUtf8("QLabel { color: #546e7a; font-size: 13px; background: transparent; line-height: 1.6; }"));
        label_learn_content->setWordWrap(true);
        label_learn_content->setAlignment(Qt::AlignmentFlag::AlignTop|Qt::AlignmentFlag::AlignLeft);
        pushButton_startQuiz = new QPushButton(coursedetailwindow);
        pushButton_startQuiz->setObjectName("pushButton_startQuiz");
        pushButton_startQuiz->setGeometry(QRect(30, 476, 800, 52));
        pushButton_startQuiz->setStyleSheet(QString::fromUtf8("\n"
"QPushButton {\n"
"    background: #1d4ed8; color: #eff6ff;\n"
"    border: none; border-radius: 10px;\n"
"    font-size: 16px; font-weight: bold; letter-spacing: 1px;\n"
"}\n"
"QPushButton:hover { background: #2563eb; }\n"
"QPushButton:pressed { background: #1e40af; }\n"
"    "));

        retranslateUi(coursedetailwindow);

        QMetaObject::connectSlotsByName(coursedetailwindow);
    } // setupUi

    void retranslateUi(QWidget *coursedetailwindow)
    {
        coursedetailwindow->setWindowTitle(QCoreApplication::translate("coursedetailwindow", "Langora \342\200\224 Course", nullptr));
        pushButton_back->setText(QCoreApplication::translate("coursedetailwindow", "\342\206\220 Back", nullptr));
        label_course_title->setText(QCoreApplication::translate("coursedetailwindow", "Course Title", nullptr));
        label_lang_badge->setText(QCoreApplication::translate("coursedetailwindow", "C++", nullptr));
        label_title_card->setText(QCoreApplication::translate("coursedetailwindow", "Course Title", nullptr));
        label_difficulty_badge->setText(QCoreApplication::translate("coursedetailwindow", "Beginner", nullptr));
        label_description->setText(QCoreApplication::translate("coursedetailwindow", "Course description goes here.", nullptr));
        label_lessons_val->setText(QCoreApplication::translate("coursedetailwindow", "8", nullptr));
        label_lessons_lbl->setText(QCoreApplication::translate("coursedetailwindow", "Lessons", nullptr));
        label_xp_val->setText(QCoreApplication::translate("coursedetailwindow", "+150 XP", nullptr));
        label_xp_lbl->setText(QCoreApplication::translate("coursedetailwindow", "XP on completion", nullptr));
        label_diff_val->setText(QCoreApplication::translate("coursedetailwindow", "Beginner", nullptr));
        label_diff_lbl->setText(QCoreApplication::translate("coursedetailwindow", "Difficulty level", nullptr));
        label_lang_val->setText(QCoreApplication::translate("coursedetailwindow", "C++", nullptr));
        label_lang_lbl->setText(QCoreApplication::translate("coursedetailwindow", "Language", nullptr));
        label_section->setText(QCoreApplication::translate("coursedetailwindow", "WHAT YOU WILL LEARN", nullptr));
        label_learn_content->setText(QCoreApplication::translate("coursedetailwindow", "Loading course content...", nullptr));
        pushButton_startQuiz->setText(QCoreApplication::translate("coursedetailwindow", "Take the Quiz \342\206\222", nullptr));
    } // retranslateUi

};

namespace Ui {
    class coursedetailwindow: public Ui_coursedetailwindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_COURSEDETAILWINDOW_H
