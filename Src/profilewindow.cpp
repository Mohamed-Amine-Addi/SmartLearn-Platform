#include "profilewindow.h"
#include "ui_profilewindow.h"
#include "databasemanager.h"
#include <QMessageBox>
#include <QRegularExpression>
#include <QDialog>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLineEdit>
#include <QPushButton>
#include <QLabel>

profilewindow::profilewindow(const QString& username,
                             QWidget* parent)
    : QWidget(parent)
    , ui(new Ui::profilewindow)
    , m_username(username)
{
    ui->setupUi(this);
    setWindowTitle("Langora — My Profile");
    setMinimumSize(780, 680);
    loadProfile();
}

profilewindow::~profilewindow() {
    delete ui;
}

void profilewindow::loadProfile() {
    auto p = databasemanager::instance()
                 .getUserProfile(m_username);

    // Store originals so we can detect changes
    m_originalFirstname = p.firstname;
    m_originalLastname  = p.lastname;
    m_originalUsername  = p.username;
    m_originalEmail     = p.email;

    // Avatar — first letter of firstname, uppercase
    QString initial = p.firstname.isEmpty()
        ? "?" : QString(p.firstname[0]).toUpper();
    ui->label_big_avatar->setText(initial);

    // Full name and join date
    ui->label_fullname->setText(
        p.firstname + " " + p.lastname);
    ui->label_joinedat->setText(
        "Member since " + p.createdAt);

    // XP and level pills
    ui->label_xp_pill->setText(
        QString::number(p.xp) + " XP");
    ui->label_level_pill->setText(
        "Level " + QString::number(p.level));

    // Fill the fields
    ui->lineEdit_firstname->setText(p.firstname);
    ui->lineEdit_lastname->setText(p.lastname);
    ui->lineEdit_newUsername->setText(p.username);
    ui->lineEdit_newEmail->setText(p.email);

    // Clear status messages
    ui->label_status->setText("");
    ui->label_email_status->setText("");
    ui->label_pw_status->setText("");
    ui->lineEdit_currentPassword->clear();
}

// Live validation — username field
void profilewindow::on_lineEdit_newUsername_textChanged(
    const QString& text)
{
    if (text == m_originalUsername) {
        ui->label_username_hint->setText(
            "Letters, numbers and underscores only");
        ui->label_username_hint->setStyleSheet(
            "QLabel{color:#334155;font-size:11px;"
            "background:transparent;}");
        return;
    }

    QRegularExpression re("^[a-zA-Z0-9_]+$");
    if (text.length() < 3) {
        ui->label_username_hint->setText(
            "⚠  At least 3 characters required");
        ui->label_username_hint->setStyleSheet(
            "QLabel{color:#f59e0b;font-size:11px;"
            "background:transparent;}");
    } else if (!re.match(text).hasMatch()) {
        ui->label_username_hint->setText(
            "⚠  Only letters, numbers, underscores");
        ui->label_username_hint->setStyleSheet(
            "QLabel{color:#f59e0b;font-size:11px;"
            "background:transparent;}");
    } else if (databasemanager::instance()
                   .usernameexists(text.toLower()) &&
               text.toLower() != m_originalUsername.toLower()) {
        ui->label_username_hint->setText(
            "✗  Username already taken");
        ui->label_username_hint->setStyleSheet(
            "QLabel{color:#ef4444;font-size:11px;"
            "background:transparent;}");
    } else {
        ui->label_username_hint->setText(
            "✓  Username available");
        ui->label_username_hint->setStyleSheet(
            "QLabel{color:#22c55e;font-size:11px;"
            "background:transparent;}");
    }
}

// Live validation — email field
void profilewindow::on_lineEdit_newEmail_textChanged(
    const QString& text)
{
    if (text == m_originalEmail) {
        ui->label_email_status->setText("");
        return;
    }
    QRegularExpression emailRe(R"(^[^@]+@[^@]+\.[^@]+$)");
    if (!emailRe.match(text).hasMatch()) {
        ui->label_email_status->setText(
            "⚠  Invalid email format");
        ui->label_email_status->setStyleSheet(
            "QLabel{color:#f59e0b;font-size:11px;"
            "background:transparent;}");
    } else {
        ui->label_email_status->setText("");
    }
}

// Save changes button
void profilewindow::on_pushButton_save_clicked() {
    QString firstname = ui->lineEdit_firstname->text().trimmed();
    QString lastname  = ui->lineEdit_lastname->text().trimmed();
    QString newUser   = ui->lineEdit_newUsername->text().trimmed();
    QString newEmail  = ui->lineEdit_newEmail->text().trimmed();
    QString password  = ui->lineEdit_currentPassword->text();

    // Basic validation
    if (firstname.isEmpty() || lastname.isEmpty() ||
        newUser.isEmpty()   || newEmail.isEmpty()) {
        ui->label_status->setText(
            "✗  Please fill in all fields.");
        ui->label_status->setStyleSheet(
            "QLabel{color:#ef4444;font-size:12px;"
            "background:transparent;}");
        return;
    }

    if (password.isEmpty()) {
        ui->label_status->setText(
            "✗  Current password is required to save changes.");
        ui->label_status->setStyleSheet(
            "QLabel{color:#ef4444;font-size:12px;"
            "background:transparent;}");
        ui->lineEdit_currentPassword->setFocus();
        return;
    }

    QRegularExpression re("^[a-zA-Z0-9_]+$");
    if (!re.match(newUser).hasMatch() || newUser.length() < 3) {
        ui->label_status->setText(
            "✗  Invalid username. Min 3 chars, letters/numbers/underscores.");
        ui->label_status->setStyleSheet(
            "QLabel{color:#ef4444;font-size:12px;"
            "background:transparent;}");
        return;
    }

    QRegularExpression emailRe(R"(^[^@]+@[^@]+\.[^@]+$)");
    if (!emailRe.match(newEmail).hasMatch()) {
        ui->label_status->setText(
            "✗  Invalid email address.");
        ui->label_status->setStyleSheet(
            "QLabel{color:#ef4444;font-size:12px;"
            "background:transparent;}");
        return;
    }

    // Attempt to save
    bool ok = databasemanager::instance().updateProfile(
        m_username, firstname, lastname,
        newUser, newEmail, password);

    if (!ok) {
        ui->label_status->setText(
            "✗  Could not save. Check your password, "
            "or the username/email may already be taken.");
        ui->label_status->setStyleSheet(
            "QLabel{color:#ef4444;font-size:12px;"
            "background:transparent;}");
        return;
    }

    // Success — update internal username if it changed
    bool usernameChanged = (newUser.toLower() !=
                            m_username.toLower());
    m_username = newUser.toLower();

    ui->label_status->setText(
        "✓  Profile saved successfully!");
    ui->label_status->setStyleSheet(
        "QLabel{color:#22c55e;font-size:12px;"
        "background:transparent;}");

    // Reload to show updated data
    loadProfile();

    // Notify the dashboard if username changed
    if (usernameChanged)
        emit profileUpdated(m_username);
}

// Change password button — opens a small dialog
void profilewindow::on_pushButton_changePassword_clicked() {
    QString currentPw = ui->lineEdit_currentPassword->text();
    if (currentPw.isEmpty()) {
        ui->label_pw_status->setText(
            "✗  Enter your current password first.");
        ui->label_pw_status->setStyleSheet(
            "QLabel{color:#ef4444;font-size:11px;"
            "background:transparent;}");
        return;
    }

    // Small dialog for new password
    QDialog* dlg = new QDialog(this);
    dlg->setWindowTitle("Change Password");
    dlg->setFixedSize(400, 240);
    dlg->setStyleSheet("QDialog{background:#050810;}");

    QVBoxLayout* lay = new QVBoxLayout(dlg);
    lay->setContentsMargins(24, 24, 24, 24);
    lay->setSpacing(12);

    QString labelStyle =
        "QLabel{color:#334155;font-size:11px;background:transparent;}";
    QString editStyle =
        "QLineEdit{background:#0a0f1e;border:1px solid #0f1629;"
        "border-radius:8px;color:#e2e8f0;font-size:13px;"
        "padding:0 12px;}QLineEdit:focus{border-color:#1d4ed8;}";

    QLabel* lbl1 = new QLabel("New password (min 6 characters):", dlg);
    lbl1->setStyleSheet(labelStyle);
    QLineEdit* newPw = new QLineEdit(dlg);
    newPw->setEchoMode(QLineEdit::Password);
    newPw->setFixedHeight(36);
    newPw->setStyleSheet(editStyle);

    QLabel* lbl2 = new QLabel("Confirm new password:", dlg);
    lbl2->setStyleSheet(labelStyle);
    QLineEdit* confirmPw = new QLineEdit(dlg);
    confirmPw->setEchoMode(QLineEdit::Password);
    confirmPw->setFixedHeight(36);
    confirmPw->setStyleSheet(editStyle);

    QLabel* statusLbl = new QLabel("", dlg);
    statusLbl->setStyleSheet(
        "QLabel{color:#ef4444;font-size:11px;background:transparent;}");

    QHBoxLayout* btns = new QHBoxLayout();
    QPushButton* cancelBtn = new QPushButton("Cancel", dlg);
    cancelBtn->setFixedHeight(36);
    cancelBtn->setStyleSheet(
        "QPushButton{background:transparent;color:#3b82f6;"
        "border:1px solid #1e3a5f;border-radius:8px;"
        "font-size:12px;font-weight:bold;}"
        "QPushButton:hover{background:#070f24;}");

    QPushButton* confirmBtn = new QPushButton("Change Password", dlg);
    confirmBtn->setFixedHeight(36);
    confirmBtn->setStyleSheet(
        "QPushButton{background:#1d4ed8;color:white;"
        "border:none;border-radius:8px;"
        "font-size:12px;font-weight:bold;}"
        "QPushButton:hover{background:#2563eb;}");

    btns->addWidget(cancelBtn);
    btns->addWidget(confirmBtn);

    lay->addWidget(lbl1);
    lay->addWidget(newPw);
    lay->addWidget(lbl2);
    lay->addWidget(confirmPw);
    lay->addWidget(statusLbl);
    lay->addLayout(btns);

    connect(cancelBtn, &QPushButton::clicked,
            dlg, &QDialog::reject);

    connect(confirmBtn, &QPushButton::clicked,
            [this, dlg, newPw, confirmPw,
             statusLbl, &currentPw]()
    {
        QString np = newPw->text();
        QString cp = confirmPw->text();

        if (np.length() < 6) {
            statusLbl->setText(
                "✗  Password must be at least 6 characters.");
            return;
        }
        if (np != cp) {
            statusLbl->setText(
                "✗  Passwords do not match.");
            return;
        }

        bool ok = databasemanager::instance().changePassword(
            m_username, currentPw, np);

        if (!ok) {
            statusLbl->setText(
                "✗  Wrong current password.");
            return;
        }

        dlg->accept();
        ui->label_pw_status->setText(
            "✓  Password changed successfully!");
        ui->label_pw_status->setStyleSheet(
            "QLabel{color:#22c55e;font-size:11px;"
            "background:transparent;}");
        ui->lineEdit_currentPassword->clear();
    });

    dlg->exec();
    dlg->deleteLater();
}

void profilewindow::on_pushButton_back_clicked() {
    emit backRequested();
}
