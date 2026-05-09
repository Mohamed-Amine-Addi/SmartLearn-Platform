/********************************************************************************
** Form generated from reading UI file 'registerwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.10.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_REGISTERWINDOW_H
#define UI_REGISTERWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_registerwindow
{
public:
    QFrame *panel_left;
    QLabel *label_logo;
    QLabel *label_appname;
    QLabel *label_tagline;
    QFrame *line_divider;
    QLabel *label_feat1;
    QLabel *label_feat2;
    QLabel *label_feat3;
    QLabel *label_feat4;
    QFrame *panel_right;
    QLabel *label_title;
    QLabel *label_sub;
    QLabel *label_step;
    QFrame *line_accent;
    QLabel *label_fn;
    QLineEdit *lineEdit_firstName;
    QLabel *label_ln;
    QLineEdit *lineEdit_lastName;
    QLabel *label_un;
    QLineEdit *lineEdit_username;
    QLabel *label_em;
    QLineEdit *lineEdit_email;
    QLabel *label_pw;
    QLineEdit *lineEdit_password;
    QFrame *frame_bar1;
    QFrame *frame_bar2;
    QFrame *frame_bar3;
    QFrame *frame_bar4;
    QLabel *label_strength;
    QLabel *label_cp;
    QLineEdit *lineEdit_confirmPassword;
    QLabel *label_confirmMatch;
    QPushButton *pushButton_register;
    QPushButton *pushButton_back;

    void setupUi(QWidget *registerwindow)
    {
        if (registerwindow->objectName().isEmpty())
            registerwindow->setObjectName("registerwindow");
        registerwindow->resize(900, 750);
        registerwindow->setStyleSheet(QString::fromUtf8("\n"
"QWidget#registerwindow {\n"
"    background-color: #080c12;\n"
"}\n"
"   "));
        panel_left = new QFrame(registerwindow);
        panel_left->setObjectName("panel_left");
        panel_left->setGeometry(QRect(0, 0, 300, 750));
        panel_left->setStyleSheet(QString::fromUtf8("\n"
"QFrame#panel_left {\n"
"    background-color: #0d1117;\n"
"    border-right: 1px solid #21262d;\n"
"}\n"
"    "));
        panel_left->setFrameShape(QFrame::Shape::StyledPanel);
        label_logo = new QLabel(panel_left);
        label_logo->setObjectName("label_logo");
        label_logo->setGeometry(QRect(90, 180, 120, 120));
        label_logo->setStyleSheet(QString::fromUtf8("\n"
"QLabel {\n"
"    background: transparent;\n"
"    border-radius: 24px;\n"
"}\n"
"     "));
        label_logo->setPixmap(QPixmap(QString::fromUtf8("logo.png")));
        label_logo->setScaledContents(true);
        label_logo->setAlignment(Qt::AlignmentFlag::AlignCenter);
        label_appname = new QLabel(panel_left);
        label_appname->setObjectName("label_appname");
        label_appname->setGeometry(QRect(20, 320, 260, 40));
        label_appname->setStyleSheet(QString::fromUtf8("\n"
"QLabel {\n"
"    color: #e8eaf6;\n"
"    font-size: 26px;\n"
"    font-weight: bold;\n"
"    letter-spacing: 4px;\n"
"    background: transparent;\n"
"}\n"
"     "));
        label_appname->setAlignment(Qt::AlignmentFlag::AlignCenter);
        label_tagline = new QLabel(panel_left);
        label_tagline->setObjectName("label_tagline");
        label_tagline->setGeometry(QRect(20, 366, 260, 20));
        label_tagline->setStyleSheet(QString::fromUtf8("\n"
"QLabel {\n"
"    color: #546e7a;\n"
"    font-size: 11px;\n"
"    letter-spacing: 2px;\n"
"    background: transparent;\n"
"}\n"
"     "));
        label_tagline->setAlignment(Qt::AlignmentFlag::AlignCenter);
        line_divider = new QFrame(panel_left);
        line_divider->setObjectName("line_divider");
        line_divider->setGeometry(QRect(60, 410, 180, 1));
        line_divider->setStyleSheet(QString::fromUtf8("QFrame { background-color: #21262d; }"));
        label_feat1 = new QLabel(panel_left);
        label_feat1->setObjectName("label_feat1");
        label_feat1->setGeometry(QRect(30, 430, 240, 16));
        label_feat1->setStyleSheet(QString::fromUtf8("QLabel { color: #90caf9; font-size: 12px; background: transparent; }"));
        label_feat2 = new QLabel(panel_left);
        label_feat2->setObjectName("label_feat2");
        label_feat2->setGeometry(QRect(30, 456, 240, 16));
        label_feat2->setStyleSheet(QString::fromUtf8("QLabel { color: #90caf9; font-size: 12px; background: transparent; }"));
        label_feat3 = new QLabel(panel_left);
        label_feat3->setObjectName("label_feat3");
        label_feat3->setGeometry(QRect(30, 482, 240, 16));
        label_feat3->setStyleSheet(QString::fromUtf8("QLabel { color: #90caf9; font-size: 12px; background: transparent; }"));
        label_feat4 = new QLabel(panel_left);
        label_feat4->setObjectName("label_feat4");
        label_feat4->setGeometry(QRect(30, 508, 240, 16));
        label_feat4->setStyleSheet(QString::fromUtf8("QLabel { color: #90caf9; font-size: 12px; background: transparent; }"));
        panel_right = new QFrame(registerwindow);
        panel_right->setObjectName("panel_right");
        panel_right->setGeometry(QRect(300, 0, 600, 750));
        panel_right->setStyleSheet(QString::fromUtf8("\n"
"QFrame#panel_right {\n"
"    background-color: #080c12;\n"
"}\n"
"    "));
        panel_right->setFrameShape(QFrame::Shape::StyledPanel);
        label_title = new QLabel(panel_right);
        label_title->setObjectName("label_title");
        label_title->setGeometry(QRect(50, 50, 500, 36));
        label_title->setStyleSheet(QString::fromUtf8("\n"
"QLabel {\n"
"    color: #e8eaf6;\n"
"    font-size: 22px;\n"
"    font-weight: bold;\n"
"    letter-spacing: 1px;\n"
"    background: transparent;\n"
"}\n"
"     "));
        label_sub = new QLabel(panel_right);
        label_sub->setObjectName("label_sub");
        label_sub->setGeometry(QRect(50, 88, 500, 18));
        label_sub->setStyleSheet(QString::fromUtf8("QLabel { color: #546e7a; font-size: 12px; background: transparent; }"));
        label_step = new QLabel(panel_right);
        label_step->setObjectName("label_step");
        label_step->setGeometry(QRect(50, 114, 500, 14));
        label_step->setStyleSheet(QString::fromUtf8("QLabel { color: #1976d2; font-size: 11px; font-weight: bold; background: transparent; }"));
        line_accent = new QFrame(panel_right);
        line_accent->setObjectName("line_accent");
        line_accent->setGeometry(QRect(50, 135, 500, 2));
        line_accent->setStyleSheet(QString::fromUtf8("QFrame { background-color: #1565c0; border-radius: 1px; }"));
        label_fn = new QLabel(panel_right);
        label_fn->setObjectName("label_fn");
        label_fn->setGeometry(QRect(50, 152, 220, 14));
        label_fn->setStyleSheet(QString::fromUtf8("QLabel { color: #78909c; font-size: 10px; font-weight: bold; letter-spacing: 1px; background: transparent; }"));
        lineEdit_firstName = new QLineEdit(panel_right);
        lineEdit_firstName->setObjectName("lineEdit_firstName");
        lineEdit_firstName->setGeometry(QRect(50, 170, 220, 42));
        lineEdit_firstName->setStyleSheet(QString::fromUtf8("\n"
"QLineEdit {\n"
"    background: #0d1117;\n"
"    border: 1px solid #21262d;\n"
"    border-radius: 8px;\n"
"    padding: 0 14px;\n"
"    color: #e6edf3;\n"
"    font-size: 13px;\n"
"}\n"
"QLineEdit:focus { border: 1px solid #1976d2; }\n"
"     "));
        label_ln = new QLabel(panel_right);
        label_ln->setObjectName("label_ln");
        label_ln->setGeometry(QRect(290, 152, 260, 14));
        label_ln->setStyleSheet(QString::fromUtf8("QLabel { color: #78909c; font-size: 10px; font-weight: bold; letter-spacing: 1px; background: transparent; }"));
        lineEdit_lastName = new QLineEdit(panel_right);
        lineEdit_lastName->setObjectName("lineEdit_lastName");
        lineEdit_lastName->setGeometry(QRect(290, 170, 260, 42));
        lineEdit_lastName->setStyleSheet(QString::fromUtf8("\n"
"QLineEdit {\n"
"    background: #0d1117;\n"
"    border: 1px solid #21262d;\n"
"    border-radius: 8px;\n"
"    padding: 0 14px;\n"
"    color: #e6edf3;\n"
"    font-size: 13px;\n"
"}\n"
"QLineEdit:focus { border: 1px solid #1976d2; }\n"
"     "));
        label_un = new QLabel(panel_right);
        label_un->setObjectName("label_un");
        label_un->setGeometry(QRect(50, 228, 500, 14));
        label_un->setStyleSheet(QString::fromUtf8("QLabel { color: #78909c; font-size: 10px; font-weight: bold; letter-spacing: 1px; background: transparent; }"));
        lineEdit_username = new QLineEdit(panel_right);
        lineEdit_username->setObjectName("lineEdit_username");
        lineEdit_username->setGeometry(QRect(50, 246, 500, 42));
        lineEdit_username->setStyleSheet(QString::fromUtf8("\n"
"QLineEdit {\n"
"    background: #0d1117;\n"
"    border: 1px solid #21262d;\n"
"    border-radius: 8px;\n"
"    padding: 0 14px;\n"
"    color: #e6edf3;\n"
"    font-size: 13px;\n"
"}\n"
"QLineEdit:focus { border: 1px solid #1976d2; }\n"
"     "));
        label_em = new QLabel(panel_right);
        label_em->setObjectName("label_em");
        label_em->setGeometry(QRect(50, 304, 500, 14));
        label_em->setStyleSheet(QString::fromUtf8("QLabel { color: #78909c; font-size: 10px; font-weight: bold; letter-spacing: 1px; background: transparent; }"));
        lineEdit_email = new QLineEdit(panel_right);
        lineEdit_email->setObjectName("lineEdit_email");
        lineEdit_email->setGeometry(QRect(50, 322, 500, 42));
        lineEdit_email->setStyleSheet(QString::fromUtf8("\n"
"QLineEdit {\n"
"    background: #0d1117;\n"
"    border: 1px solid #21262d;\n"
"    border-radius: 8px;\n"
"    padding: 0 14px;\n"
"    color: #e6edf3;\n"
"    font-size: 13px;\n"
"}\n"
"QLineEdit:focus { border: 1px solid #1976d2; }\n"
"     "));
        label_pw = new QLabel(panel_right);
        label_pw->setObjectName("label_pw");
        label_pw->setGeometry(QRect(50, 380, 500, 14));
        label_pw->setStyleSheet(QString::fromUtf8("QLabel { color: #78909c; font-size: 10px; font-weight: bold; letter-spacing: 1px; background: transparent; }"));
        lineEdit_password = new QLineEdit(panel_right);
        lineEdit_password->setObjectName("lineEdit_password");
        lineEdit_password->setGeometry(QRect(50, 398, 500, 42));
        lineEdit_password->setStyleSheet(QString::fromUtf8("\n"
"QLineEdit {\n"
"    background: #0d1117;\n"
"    border: 1px solid #21262d;\n"
"    border-radius: 8px;\n"
"    padding: 0 14px;\n"
"    color: #e6edf3;\n"
"    font-size: 13px;\n"
"}\n"
"QLineEdit:focus { border: 1px solid #1976d2; }\n"
"     "));
        lineEdit_password->setEchoMode(QLineEdit::EchoMode::Password);
        frame_bar1 = new QFrame(panel_right);
        frame_bar1->setObjectName("frame_bar1");
        frame_bar1->setGeometry(QRect(50, 446, 116, 4));
        frame_bar1->setStyleSheet(QString::fromUtf8("QFrame { background: #21262d; border-radius: 2px; }"));
        frame_bar2 = new QFrame(panel_right);
        frame_bar2->setObjectName("frame_bar2");
        frame_bar2->setGeometry(QRect(172, 446, 116, 4));
        frame_bar2->setStyleSheet(QString::fromUtf8("QFrame { background: #21262d; border-radius: 2px; }"));
        frame_bar3 = new QFrame(panel_right);
        frame_bar3->setObjectName("frame_bar3");
        frame_bar3->setGeometry(QRect(294, 446, 116, 4));
        frame_bar3->setStyleSheet(QString::fromUtf8("QFrame { background: #21262d; border-radius: 2px; }"));
        frame_bar4 = new QFrame(panel_right);
        frame_bar4->setObjectName("frame_bar4");
        frame_bar4->setGeometry(QRect(416, 446, 134, 4));
        frame_bar4->setStyleSheet(QString::fromUtf8("QFrame { background: #21262d; border-radius: 2px; }"));
        label_strength = new QLabel(panel_right);
        label_strength->setObjectName("label_strength");
        label_strength->setGeometry(QRect(50, 455, 500, 14));
        label_strength->setStyleSheet(QString::fromUtf8("QLabel { font-size: 11px; background: transparent; }"));
        label_cp = new QLabel(panel_right);
        label_cp->setObjectName("label_cp");
        label_cp->setGeometry(QRect(50, 478, 500, 14));
        label_cp->setStyleSheet(QString::fromUtf8("QLabel { color: #78909c; font-size: 10px; font-weight: bold; letter-spacing: 1px; background: transparent; }"));
        lineEdit_confirmPassword = new QLineEdit(panel_right);
        lineEdit_confirmPassword->setObjectName("lineEdit_confirmPassword");
        lineEdit_confirmPassword->setGeometry(QRect(50, 496, 500, 42));
        lineEdit_confirmPassword->setStyleSheet(QString::fromUtf8("\n"
"QLineEdit {\n"
"    background: #0d1117;\n"
"    border: 1px solid #21262d;\n"
"    border-radius: 8px;\n"
"    padding: 0 14px;\n"
"    color: #e6edf3;\n"
"    font-size: 13px;\n"
"}\n"
"QLineEdit:focus { border: 1px solid #1976d2; }\n"
"     "));
        lineEdit_confirmPassword->setEchoMode(QLineEdit::EchoMode::Password);
        label_confirmMatch = new QLabel(panel_right);
        label_confirmMatch->setObjectName("label_confirmMatch");
        label_confirmMatch->setGeometry(QRect(50, 542, 500, 14));
        label_confirmMatch->setStyleSheet(QString::fromUtf8("QLabel { background: transparent; font-size: 11px; }"));
        pushButton_register = new QPushButton(panel_right);
        pushButton_register->setObjectName("pushButton_register");
        pushButton_register->setGeometry(QRect(50, 566, 500, 48));
        pushButton_register->setStyleSheet(QString::fromUtf8("\n"
"QPushButton {\n"
"    background: #1565c0;\n"
"    color: #e8f4fd;\n"
"    border: none;\n"
"    border-radius: 10px;\n"
"    font-size: 14px;\n"
"    font-weight: bold;\n"
"    letter-spacing: 1px;\n"
"}\n"
"QPushButton:hover { background: #1976d2; }\n"
"QPushButton:pressed { background: #0d47a1; }\n"
"     "));
        pushButton_back = new QPushButton(panel_right);
        pushButton_back->setObjectName("pushButton_back");
        pushButton_back->setGeometry(QRect(50, 626, 500, 42));
        pushButton_back->setStyleSheet(QString::fromUtf8("\n"
"QPushButton {\n"
"    background: transparent;\n"
"    color: #546e7a;\n"
"    border: 1px solid #21262d;\n"
"    border-radius: 10px;\n"
"    font-size: 12px;\n"
"}\n"
"QPushButton:hover {\n"
"    color: #90caf9;\n"
"    border-color: #1565c0;\n"
"    background: #0d1a2d;\n"
"}\n"
"     "));

        retranslateUi(registerwindow);

        QMetaObject::connectSlotsByName(registerwindow);
    } // setupUi

    void retranslateUi(QWidget *registerwindow)
    {
        registerwindow->setWindowTitle(QCoreApplication::translate("registerwindow", "Langora \342\200\224 Create Account", nullptr));
        label_logo->setText(QString());
        label_appname->setText(QCoreApplication::translate("registerwindow", "LANGORA", nullptr));
        label_tagline->setText(QCoreApplication::translate("registerwindow", "LEARN \302\267 QUIZ \302\267 PROGRESS", nullptr));
        label_feat1->setText(QCoreApplication::translate("registerwindow", "\342\226\270  Interactive programming courses", nullptr));
        label_feat2->setText(QCoreApplication::translate("registerwindow", "\342\226\270  Quizzes with XP rewards", nullptr));
        label_feat3->setText(QCoreApplication::translate("registerwindow", "\342\226\270  Track your progress and badges", nullptr));
        label_feat4->setText(QCoreApplication::translate("registerwindow", "\342\226\270  Daily streak system", nullptr));
        label_title->setText(QCoreApplication::translate("registerwindow", "Create your account", nullptr));
        label_sub->setText(QCoreApplication::translate("registerwindow", "Fill in your details to get started for free", nullptr));
        label_step->setText(QCoreApplication::translate("registerwindow", "STEP 1 OF 1 \342\200\224 PERSONAL DETAILS", nullptr));
        label_fn->setText(QCoreApplication::translate("registerwindow", "FIRST NAME", nullptr));
        lineEdit_firstName->setPlaceholderText(QCoreApplication::translate("registerwindow", "e.g. Ahmed", nullptr));
        label_ln->setText(QCoreApplication::translate("registerwindow", "LAST NAME", nullptr));
        lineEdit_lastName->setPlaceholderText(QCoreApplication::translate("registerwindow", "e.g. Benali", nullptr));
        label_un->setText(QCoreApplication::translate("registerwindow", "USERNAME", nullptr));
        lineEdit_username->setPlaceholderText(QCoreApplication::translate("registerwindow", "Letters, numbers and underscores only", nullptr));
        label_em->setText(QCoreApplication::translate("registerwindow", "EMAIL ADDRESS", nullptr));
        lineEdit_email->setPlaceholderText(QCoreApplication::translate("registerwindow", "you@example.com", nullptr));
        label_pw->setText(QCoreApplication::translate("registerwindow", "PASSWORD", nullptr));
        lineEdit_password->setPlaceholderText(QCoreApplication::translate("registerwindow", "Minimum 6 characters", nullptr));
        label_strength->setText(QString());
        label_cp->setText(QCoreApplication::translate("registerwindow", "CONFIRM PASSWORD", nullptr));
        lineEdit_confirmPassword->setPlaceholderText(QCoreApplication::translate("registerwindow", "Repeat your password", nullptr));
        label_confirmMatch->setText(QString());
        pushButton_register->setText(QCoreApplication::translate("registerwindow", "Create My Account", nullptr));
        pushButton_back->setText(QCoreApplication::translate("registerwindow", "Already have an account?  Sign In \342\206\222", nullptr));
    } // retranslateUi

};

namespace Ui {
    class registerwindow: public Ui_registerwindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_REGISTERWINDOW_H
