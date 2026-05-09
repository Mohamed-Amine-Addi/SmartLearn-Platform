/********************************************************************************
** Form generated from reading UI file 'lessonviewerwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.10.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LESSONVIEWERWINDOW_H
#define UI_LESSONVIEWERWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_lessonviewerwindow
{
public:
    QFrame *topbar;
    QPushButton *pushButton_back;
    QLabel *label_course_name;
    QLabel *label_progress;
    QFrame *prog_bg;
    QFrame *prog_fill;
    QLabel *label_lesson_title;
    QScrollArea *scrollArea;
    QWidget *scrollContents;
    QLabel *label_content;
    QPushButton *pushButton_prev;
    QPushButton *pushButton_next;

    void setupUi(QWidget *lessonviewerwindow)
    {
        if (lessonviewerwindow->objectName().isEmpty())
            lessonviewerwindow->setObjectName("lessonviewerwindow");
        lessonviewerwindow->resize(900, 680);
        lessonviewerwindow->setStyleSheet(QString::fromUtf8("QWidget#lessonviewerwindow { background-color: #050810; }"));
        topbar = new QFrame(lessonviewerwindow);
        topbar->setObjectName("topbar");
        topbar->setGeometry(QRect(0, 0, 900, 64));
        topbar->setStyleSheet(QString::fromUtf8("QFrame#topbar { background-color: #070b14; border-bottom: 1px solid #0f1629; }"));
        topbar->setFrameShape(QFrame::Shape::StyledPanel);
        pushButton_back = new QPushButton(topbar);
        pushButton_back->setObjectName("pushButton_back");
        pushButton_back->setGeometry(QRect(20, 14, 90, 36));
        pushButton_back->setStyleSheet(QString::fromUtf8("QPushButton { background: transparent; color: #3b82f6; border: 1px solid #1e3a5f; border-radius: 8px; font-size: 13px; font-weight: bold; } QPushButton:hover { background: #070f24; border-color: #1d4ed8; }"));
        label_course_name = new QLabel(topbar);
        label_course_name->setObjectName("label_course_name");
        label_course_name->setGeometry(QRect(130, 14, 500, 36));
        label_course_name->setStyleSheet(QString::fromUtf8("QLabel { color: #e2e8f0; font-size: 15px; font-weight: bold; background: transparent; }"));
        label_progress = new QLabel(topbar);
        label_progress->setObjectName("label_progress");
        label_progress->setGeometry(QRect(730, 14, 150, 36));
        label_progress->setStyleSheet(QString::fromUtf8("QLabel { color: #334155; font-size: 12px; background: transparent; }"));
        label_progress->setAlignment(Qt::AlignmentFlag::AlignRight|Qt::AlignmentFlag::AlignVCenter);
        prog_bg = new QFrame(lessonviewerwindow);
        prog_bg->setObjectName("prog_bg");
        prog_bg->setGeometry(QRect(0, 64, 900, 5));
        prog_bg->setStyleSheet(QString::fromUtf8("QFrame { background: #0f1629; border: none; }"));
        prog_fill = new QFrame(lessonviewerwindow);
        prog_fill->setObjectName("prog_fill");
        prog_fill->setGeometry(QRect(0, 64, 112, 5));
        prog_fill->setStyleSheet(QString::fromUtf8("QFrame { background: #1d4ed8; border: none; }"));
        label_lesson_title = new QLabel(lessonviewerwindow);
        label_lesson_title->setObjectName("label_lesson_title");
        label_lesson_title->setGeometry(QRect(30, 84, 840, 36));
        label_lesson_title->setStyleSheet(QString::fromUtf8("QLabel { color: #e2e8f0; font-size: 20px; font-weight: bold; background: transparent; }"));
        scrollArea = new QScrollArea(lessonviewerwindow);
        scrollArea->setObjectName("scrollArea");
        scrollArea->setGeometry(QRect(0, 130, 900, 470));
        scrollArea->setStyleSheet(QString::fromUtf8("\n"
"QScrollArea { background: #050810; border: none; }\n"
"QScrollBar:vertical { background: #070b14; width: 6px; border-radius: 3px; }\n"
"QScrollBar::handle:vertical { background: #1d4ed8; border-radius: 3px; min-height: 20px; }\n"
"QScrollBar::add-line:vertical, QScrollBar::sub-line:vertical { height: 0; }\n"
"    "));
        scrollArea->setWidgetResizable(true);
        scrollArea->setFrameShape(QFrame::Shape::NoFrame);
        scrollContents = new QWidget();
        scrollContents->setObjectName("scrollContents");
        scrollContents->setGeometry(QRect(0, 0, 898, 468));
        scrollContents->setStyleSheet(QString::fromUtf8("QWidget { background: #050810; }"));
        label_content = new QLabel(scrollContents);
        label_content->setObjectName("label_content");
        label_content->setGeometry(QRect(30, 20, 840, 420));
        label_content->setStyleSheet(QString::fromUtf8("\n"
"QLabel {\n"
"    color: #94a3b8;\n"
"    font-size: 13px;\n"
"    font-family: \"Consolas\", \"Courier New\", monospace;\n"
"    background: #0a0f1e;\n"
"    border: 1px solid #0f1629;\n"
"    border-radius: 10px;\n"
"    padding: 20px;\n"
"    line-height: 1.8;\n"
"}\n"
"      "));
        label_content->setWordWrap(true);
        label_content->setAlignment(Qt::AlignmentFlag::AlignTop|Qt::AlignmentFlag::AlignLeft);
        scrollArea->setWidget(scrollContents);
        pushButton_prev = new QPushButton(lessonviewerwindow);
        pushButton_prev->setObjectName("pushButton_prev");
        pushButton_prev->setGeometry(QRect(30, 614, 180, 46));
        pushButton_prev->setStyleSheet(QString::fromUtf8("\n"
"QPushButton { background: transparent; color: #3b82f6; border: 1px solid #1e3a5f; border-radius: 10px; font-size: 14px; font-weight: bold; }\n"
"QPushButton:hover { background: #070f24; border-color: #1d4ed8; }\n"
"QPushButton:disabled { color: #1e3a5f; border-color: #0a0f1e; }\n"
"    "));
        pushButton_next = new QPushButton(lessonviewerwindow);
        pushButton_next->setObjectName("pushButton_next");
        pushButton_next->setGeometry(QRect(690, 614, 180, 46));
        pushButton_next->setStyleSheet(QString::fromUtf8("\n"
"QPushButton { background: #1d4ed8; color: #eff6ff; border: none; border-radius: 10px; font-size: 14px; font-weight: bold; }\n"
"QPushButton:hover { background: #2563eb; }\n"
"QPushButton:pressed { background: #1e40af; }\n"
"    "));

        retranslateUi(lessonviewerwindow);

        QMetaObject::connectSlotsByName(lessonviewerwindow);
    } // setupUi

    void retranslateUi(QWidget *lessonviewerwindow)
    {
        lessonviewerwindow->setWindowTitle(QCoreApplication::translate("lessonviewerwindow", "Langora \342\200\224 Lesson", nullptr));
        pushButton_back->setText(QCoreApplication::translate("lessonviewerwindow", "\342\206\220 Back", nullptr));
        label_course_name->setText(QCoreApplication::translate("lessonviewerwindow", "Course Name", nullptr));
        label_progress->setText(QCoreApplication::translate("lessonviewerwindow", "Lesson 1 / 8", nullptr));
        label_lesson_title->setText(QCoreApplication::translate("lessonviewerwindow", "Lesson Title", nullptr));
        label_content->setText(QCoreApplication::translate("lessonviewerwindow", "Lesson content loads here...", nullptr));
        pushButton_prev->setText(QCoreApplication::translate("lessonviewerwindow", "\342\206\220 Previous", nullptr));
        pushButton_next->setText(QCoreApplication::translate("lessonviewerwindow", "Next \342\206\222", nullptr));
    } // retranslateUi

};

namespace Ui {
    class lessonviewerwindow: public Ui_lessonviewerwindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LESSONVIEWERWINDOW_H
