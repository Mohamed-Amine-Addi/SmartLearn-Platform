/********************************************************************************
** Form generated from reading UI file 'badgeswindow.ui'
**
** Created by: Qt User Interface Compiler version 6.10.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_BADGESWINDOW_H
#define UI_BADGESWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_badgeswindow
{
public:
    QFrame *topbar;
    QPushButton *pushButton_back;
    QLabel *label_title;
    QLabel *label_count;
    QScrollArea *scrollArea;
    QWidget *scrollContents;

    void setupUi(QWidget *badgeswindow)
    {
        if (badgeswindow->objectName().isEmpty())
            badgeswindow->setObjectName("badgeswindow");
        badgeswindow->resize(900, 620);
        badgeswindow->setStyleSheet(QString::fromUtf8("QWidget#badgeswindow { background-color: #050810; }"));
        topbar = new QFrame(badgeswindow);
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
        label_title->setGeometry(QRect(130, 14, 400, 36));
        label_title->setStyleSheet(QString::fromUtf8("QLabel { color: #e2e8f0; font-size: 16px; font-weight: bold; background: transparent; }"));
        label_count = new QLabel(topbar);
        label_count->setObjectName("label_count");
        label_count->setGeometry(QRect(720, 14, 160, 36));
        label_count->setStyleSheet(QString::fromUtf8("QLabel { color: #334155; font-size: 12px; background: transparent; }"));
        label_count->setAlignment(Qt::AlignmentFlag::AlignRight|Qt::AlignmentFlag::AlignVCenter);
        scrollArea = new QScrollArea(badgeswindow);
        scrollArea->setObjectName("scrollArea");
        scrollArea->setGeometry(QRect(0, 64, 900, 556));
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
        scrollContents->setGeometry(QRect(0, 0, 898, 554));
        scrollContents->setStyleSheet(QString::fromUtf8("QWidget { background: #050810; }"));
        scrollArea->setWidget(scrollContents);

        retranslateUi(badgeswindow);

        QMetaObject::connectSlotsByName(badgeswindow);
    } // setupUi

    void retranslateUi(QWidget *badgeswindow)
    {
        badgeswindow->setWindowTitle(QCoreApplication::translate("badgeswindow", "Langora \342\200\224 Badges", nullptr));
        pushButton_back->setText(QCoreApplication::translate("badgeswindow", "\342\206\220 Back", nullptr));
        label_title->setText(QCoreApplication::translate("badgeswindow", "My Badges", nullptr));
        label_count->setText(QCoreApplication::translate("badgeswindow", "0 / 9 unlocked", nullptr));
    } // retranslateUi

};

namespace Ui {
    class badgeswindow: public Ui_badgeswindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_BADGESWINDOW_H
