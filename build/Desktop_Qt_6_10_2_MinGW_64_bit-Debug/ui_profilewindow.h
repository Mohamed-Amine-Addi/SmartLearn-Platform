/********************************************************************************
** Form generated from reading UI file 'profilewindow.ui'
**
** Created by: Qt User Interface Compiler version 6.10.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PROFILEWINDOW_H
#define UI_PROFILEWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_profilewindow
{
public:
    QFrame *topbar;
    QPushButton *pushButton_back;
    QLabel *label_title;
    QFrame *avatar_section;
    QLabel *label_big_avatar;
    QLabel *label_fullname;
    QLabel *label_joinedat;
    QFrame *xp_pill;
    QLabel *label_xp_pill;
    QFrame *level_pill;
    QLabel *label_level_pill;
    QLabel *label_section_info;
    QFrame *info_card;
    QLabel *lbl_fn;
    QLineEdit *lineEdit_firstname;
    QLabel *lbl_ln;
    QLineEdit *lineEdit_lastname;
    QLabel *lbl_un;
    QLineEdit *lineEdit_newUsername;
    QLabel *label_username_hint;
    QLabel *lbl_em;
    QLineEdit *lineEdit_newEmail;
    QLabel *label_email_status;
    QLabel *label_section_pw;
    QFrame *password_card;
    QLabel *lbl_pw;
    QLineEdit *lineEdit_currentPassword;
    QPushButton *pushButton_changePassword;
    QLabel *label_pw_status;
    QLabel *label_status;
    QPushButton *pushButton_save;

    void setupUi(QWidget *profilewindow)
    {
        if (profilewindow->objectName().isEmpty())
            profilewindow->setObjectName("profilewindow");
        profilewindow->resize(780, 680);
        profilewindow->setStyleSheet(QString::fromUtf8("QWidget#profilewindow { background-color: #050810; }"));
        topbar = new QFrame(profilewindow);
        topbar->setObjectName("topbar");
        topbar->setGeometry(QRect(0, 0, 780, 64));
        topbar->setStyleSheet(QString::fromUtf8("QFrame#topbar { background-color:#070b14; border-bottom:1px solid #0f1629; }"));
        topbar->setFrameShape(QFrame::Shape::StyledPanel);
        pushButton_back = new QPushButton(topbar);
        pushButton_back->setObjectName("pushButton_back");
        pushButton_back->setGeometry(QRect(20, 14, 90, 36));
        pushButton_back->setStyleSheet(QString::fromUtf8("QPushButton{background:transparent;color:#3b82f6;border:1px solid #1e3a5f;border-radius:8px;font-size:13px;font-weight:bold;}QPushButton:hover{background:#070f24;border-color:#1d4ed8;}"));
        label_title = new QLabel(topbar);
        label_title->setObjectName("label_title");
        label_title->setGeometry(QRect(130, 14, 300, 36));
        label_title->setStyleSheet(QString::fromUtf8("QLabel{color:#e2e8f0;font-size:16px;font-weight:bold;background:transparent;}"));
        avatar_section = new QFrame(profilewindow);
        avatar_section->setObjectName("avatar_section");
        avatar_section->setGeometry(QRect(0, 64, 780, 120));
        avatar_section->setStyleSheet(QString::fromUtf8("QFrame{background:#070b14;border-bottom:1px solid #0f1629;border-top:none;border-left:none;border-right:none;}"));
        avatar_section->setFrameShape(QFrame::Shape::StyledPanel);
        label_big_avatar = new QLabel(avatar_section);
        label_big_avatar->setObjectName("label_big_avatar");
        label_big_avatar->setGeometry(QRect(30, 20, 80, 80));
        label_big_avatar->setStyleSheet(QString::fromUtf8("QLabel{background:#0d1f5c;border-radius:40px;border:2px solid #1d4ed8;color:#60a5fa;font-size:32px;font-weight:bold;}"));
        label_big_avatar->setAlignment(Qt::AlignmentFlag::AlignCenter);
        label_fullname = new QLabel(avatar_section);
        label_fullname->setObjectName("label_fullname");
        label_fullname->setGeometry(QRect(128, 24, 400, 28));
        label_fullname->setStyleSheet(QString::fromUtf8("QLabel{color:#e2e8f0;font-size:20px;font-weight:bold;background:transparent;}"));
        label_joinedat = new QLabel(avatar_section);
        label_joinedat->setObjectName("label_joinedat");
        label_joinedat->setGeometry(QRect(128, 56, 400, 16));
        label_joinedat->setStyleSheet(QString::fromUtf8("QLabel{color:#334155;font-size:12px;background:transparent;}"));
        xp_pill = new QFrame(avatar_section);
        xp_pill->setObjectName("xp_pill");
        xp_pill->setGeometry(QRect(128, 78, 90, 26));
        xp_pill->setStyleSheet(QString::fromUtf8("QFrame{background:#0d1f3c;border:1px solid #1e3a5f;border-radius:13px;}"));
        label_xp_pill = new QLabel(xp_pill);
        label_xp_pill->setObjectName("label_xp_pill");
        label_xp_pill->setGeometry(QRect(0, 0, 90, 26));
        label_xp_pill->setStyleSheet(QString::fromUtf8("QLabel{color:#3b82f6;font-size:11px;font-weight:bold;background:transparent;border:none;}"));
        label_xp_pill->setAlignment(Qt::AlignmentFlag::AlignCenter);
        level_pill = new QFrame(avatar_section);
        level_pill->setObjectName("level_pill");
        level_pill->setGeometry(QRect(228, 78, 90, 26));
        level_pill->setStyleSheet(QString::fromUtf8("QFrame{background:#1a1200;border:1px solid #3d2600;border-radius:13px;}"));
        label_level_pill = new QLabel(level_pill);
        label_level_pill->setObjectName("label_level_pill");
        label_level_pill->setGeometry(QRect(0, 0, 90, 26));
        label_level_pill->setStyleSheet(QString::fromUtf8("QLabel{color:#f59e0b;font-size:11px;font-weight:bold;background:transparent;border:none;}"));
        label_level_pill->setAlignment(Qt::AlignmentFlag::AlignCenter);
        label_section_info = new QLabel(profilewindow);
        label_section_info->setObjectName("label_section_info");
        label_section_info->setGeometry(QRect(30, 202, 720, 16));
        label_section_info->setStyleSheet(QString::fromUtf8("QLabel{color:#334155;font-size:10px;font-weight:bold;letter-spacing:1px;background:transparent;}"));
        info_card = new QFrame(profilewindow);
        info_card->setObjectName("info_card");
        info_card->setGeometry(QRect(30, 226, 720, 200));
        info_card->setStyleSheet(QString::fromUtf8("QFrame{background:#070b14;border:1px solid #0f1629;border-radius:12px;}"));
        info_card->setFrameShape(QFrame::Shape::StyledPanel);
        lbl_fn = new QLabel(info_card);
        lbl_fn->setObjectName("lbl_fn");
        lbl_fn->setGeometry(QRect(20, 18, 100, 16));
        lbl_fn->setStyleSheet(QString::fromUtf8("QLabel{color:#334155;font-size:11px;background:transparent;}"));
        lineEdit_firstname = new QLineEdit(info_card);
        lineEdit_firstname->setObjectName("lineEdit_firstname");
        lineEdit_firstname->setGeometry(QRect(20, 36, 320, 36));
        lineEdit_firstname->setStyleSheet(QString::fromUtf8("QLineEdit{background:#0a0f1e;border:1px solid #0f1629;border-radius:8px;color:#e2e8f0;font-size:13px;padding:0 12px;}QLineEdit:focus{border-color:#1d4ed8;}QLineEdit:disabled{color:#334155;background:#070b14;}"));
        lbl_ln = new QLabel(info_card);
        lbl_ln->setObjectName("lbl_ln");
        lbl_ln->setGeometry(QRect(380, 18, 100, 16));
        lbl_ln->setStyleSheet(QString::fromUtf8("QLabel{color:#334155;font-size:11px;background:transparent;}"));
        lineEdit_lastname = new QLineEdit(info_card);
        lineEdit_lastname->setObjectName("lineEdit_lastname");
        lineEdit_lastname->setGeometry(QRect(380, 36, 320, 36));
        lineEdit_lastname->setStyleSheet(QString::fromUtf8("QLineEdit{background:#0a0f1e;border:1px solid #0f1629;border-radius:8px;color:#e2e8f0;font-size:13px;padding:0 12px;}QLineEdit:focus{border-color:#1d4ed8;}QLineEdit:disabled{color:#334155;background:#070b14;}"));
        lbl_un = new QLabel(info_card);
        lbl_un->setObjectName("lbl_un");
        lbl_un->setGeometry(QRect(20, 90, 100, 16));
        lbl_un->setStyleSheet(QString::fromUtf8("QLabel{color:#334155;font-size:11px;background:transparent;}"));
        lineEdit_newUsername = new QLineEdit(info_card);
        lineEdit_newUsername->setObjectName("lineEdit_newUsername");
        lineEdit_newUsername->setGeometry(QRect(20, 108, 320, 36));
        lineEdit_newUsername->setStyleSheet(QString::fromUtf8("QLineEdit{background:#0a0f1e;border:1px solid #0f1629;border-radius:8px;color:#e2e8f0;font-size:13px;padding:0 12px;}QLineEdit:focus{border-color:#1d4ed8;}QLineEdit:disabled{color:#334155;background:#070b14;}"));
        label_username_hint = new QLabel(info_card);
        label_username_hint->setObjectName("label_username_hint");
        label_username_hint->setGeometry(QRect(350, 115, 360, 22));
        label_username_hint->setStyleSheet(QString::fromUtf8("QLabel{color:#334155;font-size:11px;background:transparent;}"));
        lbl_em = new QLabel(info_card);
        lbl_em->setObjectName("lbl_em");
        lbl_em->setGeometry(QRect(20, 156, 100, 16));
        lbl_em->setStyleSheet(QString::fromUtf8("QLabel{color:#334155;font-size:11px;background:transparent;}"));
        lineEdit_newEmail = new QLineEdit(info_card);
        lineEdit_newEmail->setObjectName("lineEdit_newEmail");
        lineEdit_newEmail->setGeometry(QRect(20, 174, 320, 36));
        lineEdit_newEmail->setStyleSheet(QString::fromUtf8("QLineEdit{background:#0a0f1e;border:1px solid #0f1629;border-radius:8px;color:#e2e8f0;font-size:13px;padding:0 12px;}QLineEdit:focus{border-color:#1d4ed8;}QLineEdit:disabled{color:#334155;background:#070b14;}"));
        label_email_status = new QLabel(info_card);
        label_email_status->setObjectName("label_email_status");
        label_email_status->setGeometry(QRect(350, 181, 360, 22));
        label_email_status->setStyleSheet(QString::fromUtf8("QLabel{color:#334155;font-size:11px;background:transparent;}"));
        label_section_pw = new QLabel(profilewindow);
        label_section_pw->setObjectName("label_section_pw");
        label_section_pw->setGeometry(QRect(30, 444, 720, 16));
        label_section_pw->setStyleSheet(QString::fromUtf8("QLabel{color:#334155;font-size:10px;font-weight:bold;letter-spacing:1px;background:transparent;}"));
        password_card = new QFrame(profilewindow);
        password_card->setObjectName("password_card");
        password_card->setGeometry(QRect(30, 468, 720, 120));
        password_card->setStyleSheet(QString::fromUtf8("QFrame{background:#070b14;border:1px solid #0f1629;border-radius:12px;}"));
        password_card->setFrameShape(QFrame::Shape::StyledPanel);
        lbl_pw = new QLabel(password_card);
        lbl_pw->setObjectName("lbl_pw");
        lbl_pw->setGeometry(QRect(20, 18, 200, 16));
        lbl_pw->setStyleSheet(QString::fromUtf8("QLabel{color:#334155;font-size:11px;background:transparent;}"));
        lineEdit_currentPassword = new QLineEdit(password_card);
        lineEdit_currentPassword->setObjectName("lineEdit_currentPassword");
        lineEdit_currentPassword->setGeometry(QRect(20, 36, 320, 36));
        lineEdit_currentPassword->setStyleSheet(QString::fromUtf8("QLineEdit{background:#0a0f1e;border:1px solid #0f1629;border-radius:8px;color:#e2e8f0;font-size:13px;padding:0 12px;}QLineEdit:focus{border-color:#1d4ed8;}"));
        lineEdit_currentPassword->setEchoMode(QLineEdit::EchoMode::Password);
        pushButton_changePassword = new QPushButton(password_card);
        pushButton_changePassword->setObjectName("pushButton_changePassword");
        pushButton_changePassword->setGeometry(QRect(380, 36, 160, 36));
        pushButton_changePassword->setStyleSheet(QString::fromUtf8("QPushButton{background:transparent;color:#3b82f6;border:1px solid #1e3a5f;border-radius:8px;font-size:12px;font-weight:bold;}QPushButton:hover{background:#070f24;border-color:#1d4ed8;}"));
        label_pw_status = new QLabel(password_card);
        label_pw_status->setObjectName("label_pw_status");
        label_pw_status->setGeometry(QRect(20, 80, 680, 22));
        label_pw_status->setStyleSheet(QString::fromUtf8("QLabel{color:#334155;font-size:11px;background:transparent;}"));
        label_status = new QLabel(profilewindow);
        label_status->setObjectName("label_status");
        label_status->setGeometry(QRect(30, 600, 500, 22));
        label_status->setStyleSheet(QString::fromUtf8("QLabel{color:#334155;font-size:12px;background:transparent;}"));
        pushButton_save = new QPushButton(profilewindow);
        pushButton_save->setObjectName("pushButton_save");
        pushButton_save->setGeometry(QRect(550, 594, 200, 46));
        pushButton_save->setStyleSheet(QString::fromUtf8("QPushButton{background:#1d4ed8;color:#eff6ff;border:none;border-radius:10px;font-size:14px;font-weight:bold;}QPushButton:hover{background:#2563eb;}QPushButton:pressed{background:#1e40af;}"));

        retranslateUi(profilewindow);

        QMetaObject::connectSlotsByName(profilewindow);
    } // setupUi

    void retranslateUi(QWidget *profilewindow)
    {
        profilewindow->setWindowTitle(QCoreApplication::translate("profilewindow", "Langora \342\200\224 My Profile", nullptr));
        pushButton_back->setText(QCoreApplication::translate("profilewindow", "\342\206\220 Back", nullptr));
        label_title->setText(QCoreApplication::translate("profilewindow", "My Profile", nullptr));
        label_big_avatar->setText(QCoreApplication::translate("profilewindow", "A", nullptr));
        label_fullname->setText(QCoreApplication::translate("profilewindow", "Full Name", nullptr));
        label_joinedat->setText(QCoreApplication::translate("profilewindow", "Joined on \342\200\246", nullptr));
        label_xp_pill->setText(QCoreApplication::translate("profilewindow", "0 XP", nullptr));
        label_level_pill->setText(QCoreApplication::translate("profilewindow", "Level 1", nullptr));
        label_section_info->setText(QCoreApplication::translate("profilewindow", "PERSONAL INFORMATION", nullptr));
        lbl_fn->setText(QCoreApplication::translate("profilewindow", "First name", nullptr));
        lbl_ln->setText(QCoreApplication::translate("profilewindow", "Last name", nullptr));
        lbl_un->setText(QCoreApplication::translate("profilewindow", "Username", nullptr));
        label_username_hint->setText(QCoreApplication::translate("profilewindow", "Letters, numbers and underscores only", nullptr));
        lbl_em->setText(QCoreApplication::translate("profilewindow", "Email address", nullptr));
        label_email_status->setText(QString());
        label_section_pw->setText(QCoreApplication::translate("profilewindow", "SECURITY", nullptr));
        lbl_pw->setText(QCoreApplication::translate("profilewindow", "Current password (required to save changes)", nullptr));
        lineEdit_currentPassword->setPlaceholderText(QCoreApplication::translate("profilewindow", "Enter current password", nullptr));
        pushButton_changePassword->setText(QCoreApplication::translate("profilewindow", "Change Password", nullptr));
        label_pw_status->setText(QString());
        label_status->setText(QString());
        pushButton_save->setText(QCoreApplication::translate("profilewindow", "Save Changes", nullptr));
    } // retranslateUi

};

namespace Ui {
    class profilewindow: public Ui_profilewindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PROFILEWINDOW_H
