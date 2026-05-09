/********************************************************************************
** Form generated from reading UI file 'progresswindow.ui'
**
** Created by: Qt User Interface Compiler version 6.10.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PROGRESSWINDOW_H
#define UI_PROGRESSWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_progresswindow
{
public:
    QFrame *topbar;
    QPushButton *pushButton_back;
    QLabel *label_title;
    QFrame *card_xp;
    QLabel *label_xp_val;
    QLabel *label_xp_lbl;
    QFrame *card_level;
    QLabel *label_level_val;
    QLabel *label_level_lbl;
    QFrame *card_quizzes;
    QLabel *label_quizzes_val;
    QLabel *label_quizzes_lbl;
    QFrame *card_avg;
    QLabel *label_avg_val;
    QLabel *label_avg_lbl;
    QLabel *label_xp_section;
    QFrame *xp_bar_bg;
    QFrame *xp_bar_fill;
    QLabel *label_xp_bar_text;
    QLabel *label_history_section;
    QScrollArea *scrollArea;
    QWidget *scrollContents;

    void setupUi(QWidget *progresswindow)
    {
        if (progresswindow->objectName().isEmpty())
            progresswindow->setObjectName("progresswindow");
        progresswindow->resize(900, 660);
        progresswindow->setStyleSheet(QString::fromUtf8("QWidget#progresswindow { background-color: #050810; }"));
        topbar = new QFrame(progresswindow);
        topbar->setObjectName("topbar");
        topbar->setGeometry(QRect(0, 0, 900, 64));
        topbar->setStyleSheet(QString::fromUtf8("QFrame#topbar { background-color: #070b14; border-bottom: 1px solid #0f1629; }"));
        topbar->setFrameShape(QFrame::Shape::StyledPanel);
        pushButton_back = new QPushButton(topbar);
        pushButton_back->setObjectName("pushButton_back");
        pushButton_back->setGeometry(QRect(20, 14, 90, 36));
        pushButton_back->setStyleSheet(QString::fromUtf8("\n"
"QPushButton { background: transparent; color: #3b82f6; border: 1px solid #1e3a5f; border-radius: 8px; font-size: 13px; font-weight: bold; }\n"
"QPushButton:hover { background: #070f24; border-color: #1d4ed8; }\n"
"     "));
        label_title = new QLabel(topbar);
        label_title->setObjectName("label_title");
        label_title->setGeometry(QRect(130, 14, 300, 36));
        label_title->setStyleSheet(QString::fromUtf8("QLabel { color: #e2e8f0; font-size: 16px; font-weight: bold; background: transparent; }"));
        card_xp = new QFrame(progresswindow);
        card_xp->setObjectName("card_xp");
        card_xp->setGeometry(QRect(20, 80, 200, 90));
        card_xp->setStyleSheet(QString::fromUtf8("QFrame { background: #070b14; border: 1px solid #0f1629; border-radius: 12px; }"));
        label_xp_val = new QLabel(card_xp);
        label_xp_val->setObjectName("label_xp_val");
        label_xp_val->setGeometry(QRect(16, 14, 168, 34));
        label_xp_val->setStyleSheet(QString::fromUtf8("QLabel { color: #3b82f6; font-size: 26px; font-weight: bold; background: transparent; }"));
        label_xp_lbl = new QLabel(card_xp);
        label_xp_lbl->setObjectName("label_xp_lbl");
        label_xp_lbl->setGeometry(QRect(16, 52, 168, 16));
        label_xp_lbl->setStyleSheet(QString::fromUtf8("QLabel { color: #1e3a5f; font-size: 11px; background: transparent; }"));
        card_level = new QFrame(progresswindow);
        card_level->setObjectName("card_level");
        card_level->setGeometry(QRect(236, 80, 200, 90));
        card_level->setStyleSheet(QString::fromUtf8("QFrame { background: #070b14; border: 1px solid #0f1629; border-radius: 12px; }"));
        label_level_val = new QLabel(card_level);
        label_level_val->setObjectName("label_level_val");
        label_level_val->setGeometry(QRect(16, 14, 168, 34));
        label_level_val->setStyleSheet(QString::fromUtf8("QLabel { color: #f59e0b; font-size: 26px; font-weight: bold; background: transparent; }"));
        label_level_lbl = new QLabel(card_level);
        label_level_lbl->setObjectName("label_level_lbl");
        label_level_lbl->setGeometry(QRect(16, 52, 168, 16));
        label_level_lbl->setStyleSheet(QString::fromUtf8("QLabel { color: #1e3a5f; font-size: 11px; background: transparent; }"));
        card_quizzes = new QFrame(progresswindow);
        card_quizzes->setObjectName("card_quizzes");
        card_quizzes->setGeometry(QRect(452, 80, 200, 90));
        card_quizzes->setStyleSheet(QString::fromUtf8("QFrame { background: #070b14; border: 1px solid #0f1629; border-radius: 12px; }"));
        label_quizzes_val = new QLabel(card_quizzes);
        label_quizzes_val->setObjectName("label_quizzes_val");
        label_quizzes_val->setGeometry(QRect(16, 14, 168, 34));
        label_quizzes_val->setStyleSheet(QString::fromUtf8("QLabel { color: #22c55e; font-size: 26px; font-weight: bold; background: transparent; }"));
        label_quizzes_lbl = new QLabel(card_quizzes);
        label_quizzes_lbl->setObjectName("label_quizzes_lbl");
        label_quizzes_lbl->setGeometry(QRect(16, 52, 168, 16));
        label_quizzes_lbl->setStyleSheet(QString::fromUtf8("QLabel { color: #1e3a5f; font-size: 11px; background: transparent; }"));
        card_avg = new QFrame(progresswindow);
        card_avg->setObjectName("card_avg");
        card_avg->setGeometry(QRect(668, 80, 212, 90));
        card_avg->setStyleSheet(QString::fromUtf8("QFrame { background: #070b14; border: 1px solid #0f1629; border-radius: 12px; }"));
        label_avg_val = new QLabel(card_avg);
        label_avg_val->setObjectName("label_avg_val");
        label_avg_val->setGeometry(QRect(16, 14, 180, 34));
        label_avg_val->setStyleSheet(QString::fromUtf8("QLabel { color: #a855f7; font-size: 26px; font-weight: bold; background: transparent; }"));
        label_avg_lbl = new QLabel(card_avg);
        label_avg_lbl->setObjectName("label_avg_lbl");
        label_avg_lbl->setGeometry(QRect(16, 52, 180, 16));
        label_avg_lbl->setStyleSheet(QString::fromUtf8("QLabel { color: #1e3a5f; font-size: 11px; background: transparent; }"));
        label_xp_section = new QLabel(progresswindow);
        label_xp_section->setObjectName("label_xp_section");
        label_xp_section->setGeometry(QRect(20, 188, 860, 16));
        label_xp_section->setStyleSheet(QString::fromUtf8("QLabel { color: #334155; font-size: 10px; font-weight: bold; letter-spacing: 1px; background: transparent; }"));
        xp_bar_bg = new QFrame(progresswindow);
        xp_bar_bg->setObjectName("xp_bar_bg");
        xp_bar_bg->setGeometry(QRect(20, 212, 860, 14));
        xp_bar_bg->setStyleSheet(QString::fromUtf8("QFrame { background: #0f1629; border-radius: 7px; border: none; }"));
        xp_bar_fill = new QFrame(progresswindow);
        xp_bar_fill->setObjectName("xp_bar_fill");
        xp_bar_fill->setGeometry(QRect(20, 212, 86, 14));
        xp_bar_fill->setStyleSheet(QString::fromUtf8("QFrame { background: #1d4ed8; border-radius: 7px; border: none; }"));
        label_xp_bar_text = new QLabel(progresswindow);
        label_xp_bar_text->setObjectName("label_xp_bar_text");
        label_xp_bar_text->setGeometry(QRect(20, 230, 860, 16));
        label_xp_bar_text->setStyleSheet(QString::fromUtf8("QLabel { color: #1e3a5f; font-size: 11px; background: transparent; }"));
        label_history_section = new QLabel(progresswindow);
        label_history_section->setObjectName("label_history_section");
        label_history_section->setGeometry(QRect(20, 262, 860, 16));
        label_history_section->setStyleSheet(QString::fromUtf8("QLabel { color: #334155; font-size: 10px; font-weight: bold; letter-spacing: 1px; background: transparent; }"));
        scrollArea = new QScrollArea(progresswindow);
        scrollArea->setObjectName("scrollArea");
        scrollArea->setGeometry(QRect(0, 286, 900, 374));
        scrollArea->setStyleSheet(QString::fromUtf8("\n"
"QScrollArea { background: #050810; border: none; }\n"
"QScrollBar:vertical { background: #070b14; width: 6px; border-radius: 3px; }\n"
"QScrollBar::handle:vertical { background: #0f1629; border-radius: 3px; min-height: 20px; }\n"
"QScrollBar::handle:vertical:hover { background: #1d4ed8; }\n"
"QScrollBar::add-line:vertical, QScrollBar::sub-line:vertical { height: 0px; }\n"
"    "));
        scrollArea->setWidgetResizable(true);
        scrollArea->setFrameShape(QFrame::Shape::NoFrame);
        scrollContents = new QWidget();
        scrollContents->setObjectName("scrollContents");
        scrollContents->setGeometry(QRect(0, 0, 898, 372));
        scrollContents->setStyleSheet(QString::fromUtf8("QWidget { background: #050810; }"));
        scrollArea->setWidget(scrollContents);

        retranslateUi(progresswindow);

        QMetaObject::connectSlotsByName(progresswindow);
    } // setupUi

    void retranslateUi(QWidget *progresswindow)
    {
        progresswindow->setWindowTitle(QCoreApplication::translate("progresswindow", "Langora \342\200\224 My Progress", nullptr));
        pushButton_back->setText(QCoreApplication::translate("progresswindow", "\342\206\220 Back", nullptr));
        label_title->setText(QCoreApplication::translate("progresswindow", "My Progress", nullptr));
        label_xp_val->setText(QCoreApplication::translate("progresswindow", "0", nullptr));
        label_xp_lbl->setText(QCoreApplication::translate("progresswindow", "Total XP earned", nullptr));
        label_level_val->setText(QCoreApplication::translate("progresswindow", "1", nullptr));
        label_level_lbl->setText(QCoreApplication::translate("progresswindow", "Current level", nullptr));
        label_quizzes_val->setText(QCoreApplication::translate("progresswindow", "0", nullptr));
        label_quizzes_lbl->setText(QCoreApplication::translate("progresswindow", "Quizzes completed", nullptr));
        label_avg_val->setText(QCoreApplication::translate("progresswindow", "0%", nullptr));
        label_avg_lbl->setText(QCoreApplication::translate("progresswindow", "Average quiz score", nullptr));
        label_xp_section->setText(QCoreApplication::translate("progresswindow", "XP PROGRESS TO NEXT LEVEL", nullptr));
        label_xp_bar_text->setText(QCoreApplication::translate("progresswindow", "0 / 100 XP to next level", nullptr));
        label_history_section->setText(QCoreApplication::translate("progresswindow", "QUIZ HISTORY", nullptr));
    } // retranslateUi

};

namespace Ui {
    class progresswindow: public Ui_progresswindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PROGRESSWINDOW_H
