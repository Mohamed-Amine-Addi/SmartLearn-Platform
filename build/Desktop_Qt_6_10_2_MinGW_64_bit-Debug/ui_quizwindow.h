/********************************************************************************
** Form generated from reading UI file 'quizwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.10.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_QUIZWINDOW_H
#define UI_QUIZWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_quizwindow
{
public:
    QFrame *topbar;
    QPushButton *pushButton_back;
    QLabel *label_course_title;
    QLabel *label_progress;
    QFrame *progress_bg;
    QFrame *progress_fill;
    QFrame *question_card;
    QLabel *label_question_num;
    QLabel *label_question_text;
    QRadioButton *radio_0;
    QRadioButton *radio_1;
    QRadioButton *radio_2;
    QRadioButton *radio_3;
    QLineEdit *lineEdit_answer;
    QFrame *feedback_box;
    QLabel *label_feedback;
    QPushButton *pushButton_submit;

    void setupUi(QWidget *quizwindow)
    {
        if (quizwindow->objectName().isEmpty())
            quizwindow->setObjectName("quizwindow");
        quizwindow->resize(860, 620);
        quizwindow->setStyleSheet(QString::fromUtf8("QWidget#quizwindow { background-color: #050810; }"));
        topbar = new QFrame(quizwindow);
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
        label_course_title->setGeometry(QRect(130, 14, 400, 36));
        label_course_title->setStyleSheet(QString::fromUtf8("QLabel { color: #e2e8f0; font-size: 15px; font-weight: bold; background: transparent; }"));
        label_progress = new QLabel(topbar);
        label_progress->setObjectName("label_progress");
        label_progress->setGeometry(QRect(680, 14, 160, 36));
        label_progress->setStyleSheet(QString::fromUtf8("QLabel { color: #334155; font-size: 13px; background: transparent; }"));
        label_progress->setAlignment(Qt::AlignmentFlag::AlignRight|Qt::AlignmentFlag::AlignVCenter);
        progress_bg = new QFrame(quizwindow);
        progress_bg->setObjectName("progress_bg");
        progress_bg->setGeometry(QRect(0, 64, 860, 4));
        progress_bg->setStyleSheet(QString::fromUtf8("QFrame { background: #0f1629; border: none; }"));
        progress_fill = new QFrame(quizwindow);
        progress_fill->setObjectName("progress_fill");
        progress_fill->setGeometry(QRect(0, 64, 172, 4));
        progress_fill->setStyleSheet(QString::fromUtf8("QFrame { background: #1d4ed8; border: none; }"));
        question_card = new QFrame(quizwindow);
        question_card->setObjectName("question_card");
        question_card->setGeometry(QRect(60, 90, 740, 140));
        question_card->setStyleSheet(QString::fromUtf8("QFrame { background: #070b14; border: 1px solid #0f1629; border-radius: 14px; }"));
        question_card->setFrameShape(QFrame::Shape::StyledPanel);
        label_question_num = new QLabel(question_card);
        label_question_num->setObjectName("label_question_num");
        label_question_num->setGeometry(QRect(20, 16, 700, 16));
        label_question_num->setStyleSheet(QString::fromUtf8("QLabel { color: #1d4ed8; font-size: 11px; font-weight: bold; letter-spacing: 1px; background: transparent; }"));
        label_question_text = new QLabel(question_card);
        label_question_text->setObjectName("label_question_text");
        label_question_text->setGeometry(QRect(20, 38, 700, 86));
        label_question_text->setStyleSheet(QString::fromUtf8("QLabel { color: #e2e8f0; font-size: 16px; font-weight: bold; background: transparent; }"));
        label_question_text->setWordWrap(true);
        label_question_text->setAlignment(Qt::AlignmentFlag::AlignLeft|Qt::AlignmentFlag::AlignVCenter);
        radio_0 = new QRadioButton(quizwindow);
        radio_0->setObjectName("radio_0");
        radio_0->setGeometry(QRect(60, 246, 740, 52));
        radio_0->setStyleSheet(QString::fromUtf8("\n"
"QRadioButton {\n"
"    color: #cbd5e1; font-size: 14px; background: #070b14;\n"
"    border: 1px solid #0f1629; border-radius: 10px; padding: 0 16px;\n"
"}\n"
"QRadioButton:hover { border-color: #1d4ed8; background: #080d18; }\n"
"QRadioButton:checked { border-color: #1d4ed8; background: #0a1428; color: #60a5fa; font-weight: bold; }\n"
"QRadioButton::indicator { width: 16px; height: 16px; }\n"
"    "));
        radio_1 = new QRadioButton(quizwindow);
        radio_1->setObjectName("radio_1");
        radio_1->setGeometry(QRect(60, 306, 740, 52));
        radio_1->setStyleSheet(QString::fromUtf8("\n"
"QRadioButton {\n"
"    color: #cbd5e1; font-size: 14px; background: #070b14;\n"
"    border: 1px solid #0f1629; border-radius: 10px; padding: 0 16px;\n"
"}\n"
"QRadioButton:hover { border-color: #1d4ed8; background: #080d18; }\n"
"QRadioButton:checked { border-color: #1d4ed8; background: #0a1428; color: #60a5fa; font-weight: bold; }\n"
"QRadioButton::indicator { width: 16px; height: 16px; }\n"
"    "));
        radio_2 = new QRadioButton(quizwindow);
        radio_2->setObjectName("radio_2");
        radio_2->setGeometry(QRect(60, 366, 740, 52));
        radio_2->setStyleSheet(QString::fromUtf8("\n"
"QRadioButton {\n"
"    color: #cbd5e1; font-size: 14px; background: #070b14;\n"
"    border: 1px solid #0f1629; border-radius: 10px; padding: 0 16px;\n"
"}\n"
"QRadioButton:hover { border-color: #1d4ed8; background: #080d18; }\n"
"QRadioButton:checked { border-color: #1d4ed8; background: #0a1428; color: #60a5fa; font-weight: bold; }\n"
"QRadioButton::indicator { width: 16px; height: 16px; }\n"
"    "));
        radio_3 = new QRadioButton(quizwindow);
        radio_3->setObjectName("radio_3");
        radio_3->setGeometry(QRect(60, 426, 740, 52));
        radio_3->setStyleSheet(QString::fromUtf8("\n"
"QRadioButton {\n"
"    color: #cbd5e1; font-size: 14px; background: #070b14;\n"
"    border: 1px solid #0f1629; border-radius: 10px; padding: 0 16px;\n"
"}\n"
"QRadioButton:hover { border-color: #1d4ed8; background: #080d18; }\n"
"QRadioButton:checked { border-color: #1d4ed8; background: #0a1428; color: #60a5fa; font-weight: bold; }\n"
"QRadioButton::indicator { width: 16px; height: 16px; }\n"
"    "));
        lineEdit_answer = new QLineEdit(quizwindow);
        lineEdit_answer->setObjectName("lineEdit_answer");
        lineEdit_answer->setGeometry(QRect(60, 246, 740, 52));
        lineEdit_answer->setStyleSheet(QString::fromUtf8("\n"
"QLineEdit {\n"
"    background: #070b14; border: 1px solid #0f1629;\n"
"    border-radius: 10px; padding: 0 16px;\n"
"    color: #e2e8f0; font-size: 14px;\n"
"}\n"
"QLineEdit:focus { border-color: #1d4ed8; }\n"
"    "));
        feedback_box = new QFrame(quizwindow);
        feedback_box->setObjectName("feedback_box");
        feedback_box->setGeometry(QRect(60, 490, 740, 60));
        feedback_box->setStyleSheet(QString::fromUtf8("QFrame { background: #0a1428; border: 1px solid #1d4ed8; border-radius: 10px; }"));
        feedback_box->setFrameShape(QFrame::Shape::StyledPanel);
        label_feedback = new QLabel(feedback_box);
        label_feedback->setObjectName("label_feedback");
        label_feedback->setGeometry(QRect(16, 0, 708, 60));
        label_feedback->setStyleSheet(QString::fromUtf8("QLabel { color: #60a5fa; font-size: 13px; background: transparent; }"));
        label_feedback->setWordWrap(true);
        label_feedback->setAlignment(Qt::AlignmentFlag::AlignLeft|Qt::AlignmentFlag::AlignVCenter);
        pushButton_submit = new QPushButton(quizwindow);
        pushButton_submit->setObjectName("pushButton_submit");
        pushButton_submit->setGeometry(QRect(60, 562, 740, 48));
        pushButton_submit->setStyleSheet(QString::fromUtf8("\n"
"QPushButton {\n"
"    background: #1d4ed8; color: #eff6ff;\n"
"    border: none; border-radius: 10px;\n"
"    font-size: 15px; font-weight: bold;\n"
"}\n"
"QPushButton:hover { background: #2563eb; }\n"
"QPushButton:pressed { background: #1e40af; }\n"
"    "));

        retranslateUi(quizwindow);

        QMetaObject::connectSlotsByName(quizwindow);
    } // setupUi

    void retranslateUi(QWidget *quizwindow)
    {
        quizwindow->setWindowTitle(QCoreApplication::translate("quizwindow", "Langora \342\200\224 Quiz", nullptr));
        pushButton_back->setText(QCoreApplication::translate("quizwindow", "\342\206\220 Exit", nullptr));
        label_course_title->setText(QCoreApplication::translate("quizwindow", "Quiz", nullptr));
        label_progress->setText(QCoreApplication::translate("quizwindow", "Question 1 / 5", nullptr));
        label_question_num->setText(QCoreApplication::translate("quizwindow", "QUESTION 1", nullptr));
        label_question_text->setText(QCoreApplication::translate("quizwindow", "Question text goes here", nullptr));
        radio_0->setText(QCoreApplication::translate("quizwindow", "Option A", nullptr));
        radio_1->setText(QCoreApplication::translate("quizwindow", "Option B", nullptr));
        radio_2->setText(QCoreApplication::translate("quizwindow", "Option C", nullptr));
        radio_3->setText(QCoreApplication::translate("quizwindow", "Option D", nullptr));
        lineEdit_answer->setPlaceholderText(QCoreApplication::translate("quizwindow", "Type your answer here...", nullptr));
        label_feedback->setText(QCoreApplication::translate("quizwindow", "Feedback appears here after answering", nullptr));
        pushButton_submit->setText(QCoreApplication::translate("quizwindow", "Submit Answer", nullptr));
    } // retranslateUi

};

namespace Ui {
    class quizwindow: public Ui_quizwindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QUIZWINDOW_H
