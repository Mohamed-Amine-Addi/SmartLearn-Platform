/********************************************************************************
** Form generated from reading UI file 'loginwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.10.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LOGINWINDOW_H
#define UI_LOGINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_loginwindow
{
public:
    QFrame *card;
    QLabel *label_icon;
    QLabel *label_appname;
    QLabel *label_subtitle;
    QLabel *label_username;
    QLineEdit *lineEdit_username;
    QLabel *label_password;
    QLineEdit *lineEdit_password;
    QPushButton *pushButton_login;
    QFrame *line_left;
    QLabel *label_or;
    QFrame *line_right;
    QPushButton *pushButton_register;

    void setupUi(QWidget *loginwindow)
    {
        if (loginwindow->objectName().isEmpty())
            loginwindow->setObjectName("loginwindow");
        loginwindow->resize(780, 600);
        loginwindow->setStyleSheet(QString::fromUtf8("QWidget#loginwindow {\n"
"    background-color: #080c12;\n"
"}"));
        card = new QFrame(loginwindow);
        card->setObjectName("card");
        card->setGeometry(QRect(139, 19, 391, 541));
        card->setStyleSheet(QString::fromUtf8("QFrame#card {\n"
"    background-color: #0d1117;\n"
"    border-radius: 16px;\n"
"    border: 1px solid #21262d;\n"
"}"));
        card->setFrameShape(QFrame::Shape::StyledPanel);
        label_icon = new QLabel(card);
        label_icon->setObjectName("label_icon");
        label_icon->setGeometry(QRect(170, 30, 56, 56));
        label_icon->setStyleSheet(QString::fromUtf8("QLabel {\n"
"    background-color: #1565c0;\n"
"    border-radius: 14px;\n"
"    color: #90caf9;\n"
"    font-size: 24px;\n"
"    font-weight: bold;\n"
"}"));
        label_icon->setPixmap(QPixmap(QString::fromUtf8("logo.png")));
        label_icon->setScaledContents(true);
        label_icon->setAlignment(Qt::AlignmentFlag::AlignCenter);
        label_appname = new QLabel(card);
        label_appname->setObjectName("label_appname");
        label_appname->setGeometry(QRect(50, 100, 300, 36));
        label_appname->setStyleSheet(QString::fromUtf8("QLabel {\n"
"    color: #e8eaf6;\n"
"    font-size: 22px;\n"
"    font-weight: bold;\n"
"    letter-spacing: 3px;\n"
"    background: transparent;\n"
"}"));
        label_appname->setAlignment(Qt::AlignmentFlag::AlignCenter);
        label_subtitle = new QLabel(card);
        label_subtitle->setObjectName("label_subtitle");
        label_subtitle->setGeometry(QRect(50, 138, 300, 20));
        label_subtitle->setStyleSheet(QString::fromUtf8("QLabel {\n"
"    color: #546e7a;\n"
"    font-size: 11px;\n"
"    letter-spacing: 2px;\n"
"    background: transparent;\n"
"}"));
        label_subtitle->setAlignment(Qt::AlignmentFlag::AlignCenter);
        label_username = new QLabel(card);
        label_username->setObjectName("label_username");
        label_username->setGeometry(QRect(30, 180, 340, 16));
        label_username->setStyleSheet(QString::fromUtf8("QLabel {\n"
"    color: #78909c;\n"
"    font-size: 11px;\n"
"    font-weight: bold;\n"
"    letter-spacing: 1px;\n"
"    background: transparent;\n"
"}"));
        lineEdit_username = new QLineEdit(card);
        lineEdit_username->setObjectName("lineEdit_username");
        lineEdit_username->setGeometry(QRect(30, 200, 340, 44));
        lineEdit_username->setStyleSheet(QString::fromUtf8("QLineEdit {\n"
"    background-color: #161b22;\n"
"    border: 1px solid #21262d;\n"
"    border-radius: 8px;\n"
"    padding: 0px 14px;\n"
"    color: #e6edf3;\n"
"    font-size: 14px;\n"
"}\n"
"QLineEdit:focus {\n"
"    border: 1px solid #1976d2;\n"
"}"));
        label_password = new QLabel(card);
        label_password->setObjectName("label_password");
        label_password->setGeometry(QRect(30, 258, 340, 16));
        label_password->setStyleSheet(QString::fromUtf8("QLabel {\n"
"    color: #78909c;\n"
"    font-size: 11px;\n"
"    font-weight: bold;\n"
"    letter-spacing: 1px;\n"
"    background: transparent;\n"
"}"));
        lineEdit_password = new QLineEdit(card);
        lineEdit_password->setObjectName("lineEdit_password");
        lineEdit_password->setGeometry(QRect(30, 278, 340, 44));
        lineEdit_password->setStyleSheet(QString::fromUtf8("QLineEdit {\n"
"    background-color: #161b22;\n"
"    border: 1px solid #21262d;\n"
"    border-radius: 8px;\n"
"    padding: 0px 14px;\n"
"    color: #e6edf3;\n"
"    font-size: 14px;\n"
"}\n"
"QLineEdit:focus {\n"
"    border: 1px solid #1976d2;\n"
"}"));
        lineEdit_password->setEchoMode(QLineEdit::EchoMode::Password);
        pushButton_login = new QPushButton(card);
        pushButton_login->setObjectName("pushButton_login");
        pushButton_login->setGeometry(QRect(30, 340, 340, 44));
        pushButton_login->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    background-color: #1565c0;\n"
"    color: #e8f4fd;\n"
"    border: none;\n"
"    border-radius: 8px;\n"
"    font-size: 14px;\n"
"    font-weight: bold;\n"
"    letter-spacing: 1px;\n"
"}\n"
"QPushButton:hover {\n"
"    background-color: #1976d2;\n"
"}\n"
"QPushButton:pressed {\n"
"    background-color: #0d47a1;\n"
"}"));
        line_left = new QFrame(card);
        line_left->setObjectName("line_left");
        line_left->setGeometry(QRect(30, 406, 120, 2));
        line_left->setStyleSheet(QString::fromUtf8("QFrame { background-color: #21262d; }"));
        line_left->setFrameShape(QFrame::Shape::HLine);
        label_or = new QLabel(card);
        label_or->setObjectName("label_or");
        label_or->setGeometry(QRect(165, 398, 30, 16));
        label_or->setStyleSheet(QString::fromUtf8("QLabel {\n"
"    color: #3d4f5a;\n"
"    font-size: 11px;\n"
"    background: transparent;\n"
"}"));
        label_or->setAlignment(Qt::AlignmentFlag::AlignCenter);
        line_right = new QFrame(card);
        line_right->setObjectName("line_right");
        line_right->setGeometry(QRect(210, 406, 120, 2));
        line_right->setStyleSheet(QString::fromUtf8("QFrame { background-color: #21262d; }"));
        line_right->setFrameShape(QFrame::Shape::HLine);
        pushButton_register = new QPushButton(card);
        pushButton_register->setObjectName("pushButton_register");
        pushButton_register->setGeometry(QRect(30, 424, 340, 44));
        pushButton_register->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    background-color: transparent;\n"
"    color: #90caf9;\n"
"    border: 1px solid #1565c0;\n"
"    border-radius: 8px;\n"
"    font-size: 13px;\n"
"    font-weight: bold;\n"
"}\n"
"QPushButton:hover {\n"
"    background-color: #0d2137;\n"
"}\n"
"QPushButton:pressed {\n"
"    background-color: #0a1a2e;\n"
"}"));

        retranslateUi(loginwindow);

        QMetaObject::connectSlotsByName(loginwindow);
    } // setupUi

    void retranslateUi(QWidget *loginwindow)
    {
        loginwindow->setWindowTitle(QCoreApplication::translate("loginwindow", "Langora", nullptr));
        label_icon->setText(QString());
        label_appname->setText(QCoreApplication::translate("loginwindow", "LANGORA", nullptr));
        label_subtitle->setText(QCoreApplication::translate("loginwindow", "LEARN \302\267 QUIZ \302\267 PROGRESS", nullptr));
        label_username->setText(QCoreApplication::translate("loginwindow", "USERNAME", nullptr));
        lineEdit_username->setPlaceholderText(QCoreApplication::translate("loginwindow", "Enter your username", nullptr));
        label_password->setText(QCoreApplication::translate("loginwindow", "PASSWORD", nullptr));
        lineEdit_password->setPlaceholderText(QCoreApplication::translate("loginwindow", "\342\200\242\342\200\242\342\200\242\342\200\242\342\200\242\342\200\242\342\200\242\342\200\242", nullptr));
        pushButton_login->setText(QCoreApplication::translate("loginwindow", "Sign In", nullptr));
        label_or->setText(QCoreApplication::translate("loginwindow", "OR", nullptr));
        pushButton_register->setText(QCoreApplication::translate("loginwindow", "Create an account", nullptr));
    } // retranslateUi

};

namespace Ui {
    class loginwindow: public Ui_loginwindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOGINWINDOW_H
