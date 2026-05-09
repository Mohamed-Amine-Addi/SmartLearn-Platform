/********************************************************************************
** Form generated from reading UI file 'quizresultwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.10.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_QUIZRESULTWINDOW_H
#define UI_QUIZRESULTWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_quizresultwindow
{
public:
    QLabel *label_icon;
    QLabel *label_score;
    QLabel *label_course;
    QFrame *stat_correct;
    QLabel *label_correct_val;
    QLabel *label_correct_lbl;
    QFrame *stat_wrong;
    QLabel *label_wrong_val;
    QLabel *label_wrong_lbl;
    QFrame *stat_xp;
    QLabel *label_xp_val;
    QLabel *label_xp_lbl;
    QPushButton *pushButton_dashboard;
    QPushButton *pushButton_retry;
    QLabel *label_message;

    void setupUi(QWidget *quizresultwindow)
    {
        if (quizresultwindow->objectName().isEmpty())
            quizresultwindow->setObjectName("quizresultwindow");
        quizresultwindow->resize(700, 500);
        quizresultwindow->setStyleSheet(QString::fromUtf8("QWidget#quizresultwindow { background-color: #050810; }"));
        label_icon = new QLabel(quizresultwindow);
        label_icon->setObjectName("label_icon");
        label_icon->setGeometry(QRect(270, 40, 160, 80));
        label_icon->setStyleSheet(QString::fromUtf8("QLabel { color: #22c55e; font-size: 52px; background: transparent; }"));
        label_icon->setAlignment(Qt::AlignmentFlag::AlignCenter);
        label_score = new QLabel(quizresultwindow);
        label_score->setObjectName("label_score");
        label_score->setGeometry(QRect(100, 130, 500, 60));
        label_score->setStyleSheet(QString::fromUtf8("QLabel { color: #e2e8f0; font-size: 42px; font-weight: bold; background: transparent; }"));
        label_score->setAlignment(Qt::AlignmentFlag::AlignCenter);
        label_course = new QLabel(quizresultwindow);
        label_course->setObjectName("label_course");
        label_course->setGeometry(QRect(100, 192, 500, 24));
        label_course->setStyleSheet(QString::fromUtf8("QLabel { color: #334155; font-size: 13px; background: transparent; }"));
        label_course->setAlignment(Qt::AlignmentFlag::AlignCenter);
        stat_correct = new QFrame(quizresultwindow);
        stat_correct->setObjectName("stat_correct");
        stat_correct->setGeometry(QRect(80, 236, 160, 80));
        stat_correct->setStyleSheet(QString::fromUtf8("QFrame { background: #070b14; border: 1px solid #0f1629; border-radius: 12px; }"));
        label_correct_val = new QLabel(stat_correct);
        label_correct_val->setObjectName("label_correct_val");
        label_correct_val->setGeometry(QRect(0, 12, 160, 32));
        label_correct_val->setStyleSheet(QString::fromUtf8("QLabel { color: #22c55e; font-size: 26px; font-weight: bold; background: transparent; }"));
        label_correct_val->setAlignment(Qt::AlignmentFlag::AlignCenter);
        label_correct_lbl = new QLabel(stat_correct);
        label_correct_lbl->setObjectName("label_correct_lbl");
        label_correct_lbl->setGeometry(QRect(0, 48, 160, 18));
        label_correct_lbl->setStyleSheet(QString::fromUtf8("QLabel { color: #1e3a5f; font-size: 11px; background: transparent; }"));
        label_correct_lbl->setAlignment(Qt::AlignmentFlag::AlignCenter);
        stat_wrong = new QFrame(quizresultwindow);
        stat_wrong->setObjectName("stat_wrong");
        stat_wrong->setGeometry(QRect(270, 236, 160, 80));
        stat_wrong->setStyleSheet(QString::fromUtf8("QFrame { background: #070b14; border: 1px solid #0f1629; border-radius: 12px; }"));
        label_wrong_val = new QLabel(stat_wrong);
        label_wrong_val->setObjectName("label_wrong_val");
        label_wrong_val->setGeometry(QRect(0, 12, 160, 32));
        label_wrong_val->setStyleSheet(QString::fromUtf8("QLabel { color: #ef4444; font-size: 26px; font-weight: bold; background: transparent; }"));
        label_wrong_val->setAlignment(Qt::AlignmentFlag::AlignCenter);
        label_wrong_lbl = new QLabel(stat_wrong);
        label_wrong_lbl->setObjectName("label_wrong_lbl");
        label_wrong_lbl->setGeometry(QRect(0, 48, 160, 18));
        label_wrong_lbl->setStyleSheet(QString::fromUtf8("QLabel { color: #1e3a5f; font-size: 11px; background: transparent; }"));
        label_wrong_lbl->setAlignment(Qt::AlignmentFlag::AlignCenter);
        stat_xp = new QFrame(quizresultwindow);
        stat_xp->setObjectName("stat_xp");
        stat_xp->setGeometry(QRect(460, 236, 160, 80));
        stat_xp->setStyleSheet(QString::fromUtf8("QFrame { background: #070b14; border: 1px solid #0f1629; border-radius: 12px; }"));
        label_xp_val = new QLabel(stat_xp);
        label_xp_val->setObjectName("label_xp_val");
        label_xp_val->setGeometry(QRect(0, 12, 160, 32));
        label_xp_val->setStyleSheet(QString::fromUtf8("QLabel { color: #3b82f6; font-size: 26px; font-weight: bold; background: transparent; }"));
        label_xp_val->setAlignment(Qt::AlignmentFlag::AlignCenter);
        label_xp_lbl = new QLabel(stat_xp);
        label_xp_lbl->setObjectName("label_xp_lbl");
        label_xp_lbl->setGeometry(QRect(0, 48, 160, 18));
        label_xp_lbl->setStyleSheet(QString::fromUtf8("QLabel { color: #1e3a5f; font-size: 11px; background: transparent; }"));
        label_xp_lbl->setAlignment(Qt::AlignmentFlag::AlignCenter);
        pushButton_dashboard = new QPushButton(quizresultwindow);
        pushButton_dashboard->setObjectName("pushButton_dashboard");
        pushButton_dashboard->setGeometry(QRect(80, 346, 260, 48));
        pushButton_dashboard->setStyleSheet(QString::fromUtf8("\n"
"QPushButton { background: #1d4ed8; color: white; border: none; border-radius: 10px; font-size: 14px; font-weight: bold; }\n"
"QPushButton:hover { background: #2563eb; }\n"
"    "));
        pushButton_retry = new QPushButton(quizresultwindow);
        pushButton_retry->setObjectName("pushButton_retry");
        pushButton_retry->setGeometry(QRect(360, 346, 260, 48));
        pushButton_retry->setStyleSheet(QString::fromUtf8("\n"
"QPushButton { background: transparent; color: #3b82f6; border: 1px solid #1e3a5f; border-radius: 10px; font-size: 14px; font-weight: bold; }\n"
"QPushButton:hover { background: #070f24; border-color: #1d4ed8; }\n"
"    "));
        label_message = new QLabel(quizresultwindow);
        label_message->setObjectName("label_message");
        label_message->setGeometry(QRect(80, 412, 540, 30));
        label_message->setStyleSheet(QString::fromUtf8("QLabel { color: #334155; font-size: 12px; background: transparent; }"));
        label_message->setAlignment(Qt::AlignmentFlag::AlignCenter);

        retranslateUi(quizresultwindow);

        QMetaObject::connectSlotsByName(quizresultwindow);
    } // setupUi

    void retranslateUi(QWidget *quizresultwindow)
    {
        quizresultwindow->setWindowTitle(QCoreApplication::translate("quizresultwindow", "Langora \342\200\224 Results", nullptr));
        label_icon->setText(QCoreApplication::translate("quizresultwindow", "\342\234\223", nullptr));
        label_score->setText(QCoreApplication::translate("quizresultwindow", "85%", nullptr));
        label_course->setText(QCoreApplication::translate("quizresultwindow", "C++ Fundamentals", nullptr));
        label_correct_val->setText(QCoreApplication::translate("quizresultwindow", "4", nullptr));
        label_correct_lbl->setText(QCoreApplication::translate("quizresultwindow", "Correct", nullptr));
        label_wrong_val->setText(QCoreApplication::translate("quizresultwindow", "1", nullptr));
        label_wrong_lbl->setText(QCoreApplication::translate("quizresultwindow", "Wrong", nullptr));
        label_xp_val->setText(QCoreApplication::translate("quizresultwindow", "+40 XP", nullptr));
        label_xp_lbl->setText(QCoreApplication::translate("quizresultwindow", "XP Earned", nullptr));
        pushButton_dashboard->setText(QCoreApplication::translate("quizresultwindow", "Back to Dashboard", nullptr));
        pushButton_retry->setText(QCoreApplication::translate("quizresultwindow", "Try Again \342\206\222", nullptr));
        label_message->setText(QCoreApplication::translate("quizresultwindow", "XP has been added to your account. Keep learning!", nullptr));
    } // retranslateUi

};

namespace Ui {
    class quizresultwindow: public Ui_quizresultwindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QUIZRESULTWINDOW_H
