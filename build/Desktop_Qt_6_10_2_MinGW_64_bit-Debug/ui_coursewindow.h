/********************************************************************************
** Form generated from reading UI file 'coursewindow.ui'
**
** Created by: Qt User Interface Compiler version 6.10.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_COURSEWINDOW_H
#define UI_COURSEWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_coursewindow
{
public:
    QFrame *topbar;
    QPushButton *pushButton_back;
    QLabel *label_title;
    QLabel *label_userinfo;
    QFrame *filterbar;
    QLabel *label_filter;
    QPushButton *btn_filter_all;
    QPushButton *btn_filter_cpp;
    QPushButton *btn_filter_python;
    QLabel *label_count;
    QScrollArea *scrollArea;
    QWidget *scrollContents;

    void setupUi(QWidget *coursewindow)
    {
        if (coursewindow->objectName().isEmpty())
            coursewindow->setObjectName("coursewindow");
        coursewindow->resize(1000, 680);
        coursewindow->setStyleSheet(QString::fromUtf8("QWidget#coursewindow { background-color: #050810; }"));
        topbar = new QFrame(coursewindow);
        topbar->setObjectName("topbar");
        topbar->setGeometry(QRect(0, 0, 1000, 64));
        topbar->setStyleSheet(QString::fromUtf8("\n"
"QFrame#topbar {\n"
"    background-color: #070b14;\n"
"    border-bottom: 1px solid #0f1629;\n"
"}\n"
"    "));
        topbar->setFrameShape(QFrame::Shape::StyledPanel);
        pushButton_back = new QPushButton(topbar);
        pushButton_back->setObjectName("pushButton_back");
        pushButton_back->setGeometry(QRect(20, 14, 100, 36));
        pushButton_back->setStyleSheet(QString::fromUtf8("\n"
"QPushButton {\n"
"    background: transparent;\n"
"    color: #3b82f6;\n"
"    border: 1px solid #1e3a5f;\n"
"    border-radius: 8px;\n"
"    font-size: 13px;\n"
"    font-weight: bold;\n"
"}\n"
"QPushButton:hover {\n"
"    background: #070f24;\n"
"    border-color: #1d4ed8;\n"
"}\n"
"     "));
        label_title = new QLabel(topbar);
        label_title->setObjectName("label_title");
        label_title->setGeometry(QRect(140, 14, 400, 36));
        label_title->setStyleSheet(QString::fromUtf8("QLabel { color: #e2e8f0; font-size: 18px; font-weight: bold; background: transparent; }"));
        label_userinfo = new QLabel(topbar);
        label_userinfo->setObjectName("label_userinfo");
        label_userinfo->setGeometry(QRect(760, 14, 220, 36));
        label_userinfo->setStyleSheet(QString::fromUtf8("QLabel { color: #334155; font-size: 12px; background: transparent; }"));
        label_userinfo->setAlignment(Qt::AlignmentFlag::AlignRight|Qt::AlignmentFlag::AlignTrailing|Qt::AlignmentFlag::AlignVCenter);
        filterbar = new QFrame(coursewindow);
        filterbar->setObjectName("filterbar");
        filterbar->setGeometry(QRect(0, 64, 1000, 48));
        filterbar->setStyleSheet(QString::fromUtf8("\n"
"QFrame#filterbar {\n"
"    background-color: #070b14;\n"
"    border-bottom: 1px solid #0a0f1e;\n"
"}\n"
"    "));
        filterbar->setFrameShape(QFrame::Shape::StyledPanel);
        label_filter = new QLabel(filterbar);
        label_filter->setObjectName("label_filter");
        label_filter->setGeometry(QRect(20, 14, 40, 20));
        label_filter->setStyleSheet(QString::fromUtf8("QLabel { color: #334155; font-size: 11px; background: transparent; }"));
        btn_filter_all = new QPushButton(filterbar);
        btn_filter_all->setObjectName("btn_filter_all");
        btn_filter_all->setGeometry(QRect(66, 10, 60, 28));
        btn_filter_all->setStyleSheet(QString::fromUtf8("\n"
"QPushButton {\n"
"    background: #0d1f3c;\n"
"    color: #60a5fa;\n"
"    border: 1px solid #1d4ed8;\n"
"    border-radius: 14px;\n"
"    font-size: 11px;\n"
"    font-weight: bold;\n"
"}\n"
"QPushButton:hover { background: #0f2448; }\n"
"     "));
        btn_filter_cpp = new QPushButton(filterbar);
        btn_filter_cpp->setObjectName("btn_filter_cpp");
        btn_filter_cpp->setGeometry(QRect(134, 10, 60, 28));
        btn_filter_cpp->setStyleSheet(QString::fromUtf8("\n"
"QPushButton {\n"
"    background: transparent;\n"
"    color: #334155;\n"
"    border: 1px solid #0f1629;\n"
"    border-radius: 14px;\n"
"    font-size: 8px;\n"
"    font-weight: bold;\n"
"}\n"
"QPushButton:hover {\n"
"    background: #0d1f3c;\n"
"    color: #60a5fa;\n"
"    border-color: #1d4ed8;\n"
"}\n"
"     "));
        btn_filter_python = new QPushButton(filterbar);
        btn_filter_python->setObjectName("btn_filter_python");
        btn_filter_python->setGeometry(QRect(202, 10, 70, 28));
        btn_filter_python->setStyleSheet(QString::fromUtf8("\n"
"QPushButton {\n"
"    background: transparent;\n"
"    color: #334155;\n"
"    border: 1px solid #0f1629;\n"
"    border-radius: 14px;\n"
"    font-size: 11px;\n"
"    font-weight: bold;\n"
"}\n"
"QPushButton:hover {\n"
"    background: #0d1f3c;\n"
"    color: #60a5fa;\n"
"    border-color: #1d4ed8;\n"
"}\n"
"     "));
        label_count = new QLabel(filterbar);
        label_count->setObjectName("label_count");
        label_count->setGeometry(QRect(820, 14, 160, 20));
        label_count->setStyleSheet(QString::fromUtf8("QLabel { color: #1e3a5f; font-size: 11px; background: transparent; }"));
        label_count->setAlignment(Qt::AlignmentFlag::AlignRight|Qt::AlignmentFlag::AlignTrailing|Qt::AlignmentFlag::AlignVCenter);
        scrollArea = new QScrollArea(coursewindow);
        scrollArea->setObjectName("scrollArea");
        scrollArea->setGeometry(QRect(0, 112, 1000, 568));
        scrollArea->setStyleSheet(QString::fromUtf8("\n"
"QScrollArea {\n"
"    background-color: #050810;\n"
"    border: none;\n"
"}\n"
"QScrollBar:vertical {\n"
"    background: #070b14;\n"
"    width: 6px;\n"
"    border-radius: 3px;\n"
"}\n"
"QScrollBar::handle:vertical {\n"
"    background: #0f1629;\n"
"    border-radius: 3px;\n"
"    min-height: 20px;\n"
"}\n"
"QScrollBar::handle:vertical:hover { background: #1d4ed8; }\n"
"QScrollBar::add-line:vertical,\n"
"QScrollBar::sub-line:vertical { height: 0px; }\n"
"    "));
        scrollArea->setFrameShape(QFrame::Shape::NoFrame);
        scrollArea->setWidgetResizable(true);
        scrollContents = new QWidget();
        scrollContents->setObjectName("scrollContents");
        scrollContents->setGeometry(QRect(0, 0, 1000, 568));
        scrollContents->setStyleSheet(QString::fromUtf8("QWidget { background-color: #050810; }"));
        scrollArea->setWidget(scrollContents);

        retranslateUi(coursewindow);

        QMetaObject::connectSlotsByName(coursewindow);
    } // setupUi

    void retranslateUi(QWidget *coursewindow)
    {
        coursewindow->setWindowTitle(QCoreApplication::translate("coursewindow", "Langora \342\200\224 Courses", nullptr));
        pushButton_back->setText(QCoreApplication::translate("coursewindow", "\342\206\220 Back", nullptr));
        label_title->setText(QCoreApplication::translate("coursewindow", "Programming Courses", nullptr));
        label_userinfo->setText(QCoreApplication::translate("coursewindow", "Level 1  |  0 XP", nullptr));
        label_filter->setText(QCoreApplication::translate("coursewindow", "Filter:", nullptr));
        btn_filter_all->setText(QCoreApplication::translate("coursewindow", "All", nullptr));
        btn_filter_cpp->setText(QCoreApplication::translate("coursewindow", "C++", nullptr));
        btn_filter_python->setText(QCoreApplication::translate("coursewindow", "Python", nullptr));
        label_count->setText(QCoreApplication::translate("coursewindow", "8 courses available", nullptr));
    } // retranslateUi

};

namespace Ui {
    class coursewindow: public Ui_coursewindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_COURSEWINDOW_H
