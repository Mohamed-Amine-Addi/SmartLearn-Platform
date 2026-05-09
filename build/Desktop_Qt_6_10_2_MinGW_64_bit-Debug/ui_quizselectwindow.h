/********************************************************************************
** Form generated from reading UI file 'quizselectwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.10.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_QUIZSELECTWINDOW_H
#define UI_QUIZSELECTWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_quizselectwindow
{
public:
    QFrame *topbar;
    QPushButton *pushButton_back;
    QLabel *label_title;
    QLabel *label_subtitle;
    QScrollArea *scrollArea;
    QWidget *scrollContents;

    void setupUi(QWidget *quizselectwindow)
    {
        if (quizselectwindow->objectName().isEmpty())
            quizselectwindow->setObjectName("quizselectwindow");
        quizselectwindow->resize(1000, 680);
        quizselectwindow->setStyleSheet(QString::fromUtf8("QWidget#quizselectwindow { background-color: #050810; }"));
        topbar = new QFrame(quizselectwindow);
        topbar->setObjectName("topbar");
        topbar->setGeometry(QRect(0, 0, 1000, 64));
        topbar->setStyleSheet(QString::fromUtf8("QFrame#topbar { background-color: #070b14; border-bottom: 1px solid #0f1629; }"));
        topbar->setFrameShape(QFrame::Shape::StyledPanel);
        pushButton_back = new QPushButton(topbar);
        pushButton_back->setObjectName("pushButton_back");
        pushButton_back->setGeometry(QRect(20, 14, 100, 36));
        pushButton_back->setStyleSheet(QString::fromUtf8("QPushButton{background:transparent;color:#3b82f6;border:1px solid #1e3a5f;border-radius:8px;font-size:13px;font-weight:bold;}QPushButton:hover{background:#070f24;border-color:#1d4ed8;}"));
        label_title = new QLabel(topbar);
        label_title->setObjectName("label_title");
        label_title->setGeometry(QRect(140, 14, 500, 36));
        label_title->setStyleSheet(QString::fromUtf8("QLabel{color:#e2e8f0;font-size:18px;font-weight:bold;background:transparent;}"));
        label_subtitle = new QLabel(topbar);
        label_subtitle->setObjectName("label_subtitle");
        label_subtitle->setGeometry(QRect(700, 14, 280, 36));
        label_subtitle->setStyleSheet(QString::fromUtf8("QLabel{color:#334155;font-size:12px;background:transparent;}"));
        label_subtitle->setAlignment(Qt::AlignmentFlag::AlignRight|Qt::AlignmentFlag::AlignVCenter);
        scrollArea = new QScrollArea(quizselectwindow);
        scrollArea->setObjectName("scrollArea");
        scrollArea->setGeometry(QRect(0, 64, 1000, 616));
        scrollArea->setStyleSheet(QString::fromUtf8("QScrollArea{background:#050810;border:none;}QScrollBar:vertical{background:#070b14;width:6px;border-radius:3px;}QScrollBar::handle:vertical{background:#0f1629;border-radius:3px;min-height:20px;}QScrollBar::handle:vertical:hover{background:#1d4ed8;}QScrollBar::add-line:vertical,QScrollBar::sub-line:vertical{height:0px;}"));
        scrollArea->setWidgetResizable(true);
        scrollArea->setFrameShape(QFrame::Shape::NoFrame);
        scrollContents = new QWidget();
        scrollContents->setObjectName("scrollContents");
        scrollContents->setGeometry(QRect(0, 0, 998, 614));
        scrollContents->setStyleSheet(QString::fromUtf8("QWidget{background:#050810;}"));
        scrollArea->setWidget(scrollContents);

        retranslateUi(quizselectwindow);

        QMetaObject::connectSlotsByName(quizselectwindow);
    } // setupUi

    void retranslateUi(QWidget *quizselectwindow)
    {
        quizselectwindow->setWindowTitle(QCoreApplication::translate("quizselectwindow", "Langora \342\200\224 Select Quiz", nullptr));
        pushButton_back->setText(QCoreApplication::translate("quizselectwindow", "\342\206\220 Back", nullptr));
        label_title->setText(QCoreApplication::translate("quizselectwindow", "Select a Quiz", nullptr));
        label_subtitle->setText(QCoreApplication::translate("quizselectwindow", "Choose a course to quiz yourself on", nullptr));
    } // retranslateUi

};

namespace Ui {
    class quizselectwindow: public Ui_quizselectwindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QUIZSELECTWINDOW_H
