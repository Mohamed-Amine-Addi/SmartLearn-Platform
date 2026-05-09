#include "loginwindow.h"
#include "ui_loginwindow.h"
#include "databasemanager.h"
#include "registerwindow.h"
#include <QMessageBox>
#include <QTimer>
#include <QPainter>
#include <QRadialGradient>

loginwindow::loginwindow(QWidget* parent)
    : QWidget(parent)
    , ui(new Ui::loginwindow)
{
    ui->setupUi(this);
    setWindowTitle("Langora");
    setFixedSize(860, 580);

    ui->label_error->setText("");

    m_shakeTimer = new QTimer(this);
    m_shakeTimer->setInterval(28);
    connect(m_shakeTimer, &QTimer::timeout,
            this, &loginwindow::shakeAnimation);
}

loginwindow::~loginwindow() { delete ui; }

void loginwindow::paintEvent(QPaintEvent* event) {
    QWidget::paintEvent(event);
    QPainter p(this);
    p.setRenderHint(QPainter::Antialiasing);

    // Glow on right panel
    QRadialGradient g1(640, 160, 160);
    g1.setColorAt(0, QColor(29, 78, 216, 45));
    g1.setColorAt(1, QColor(29, 78, 216, 0));
    p.setBrush(g1); p.setPen(Qt::NoPen);
    p.drawEllipse(480, 0, 320, 320);

    QRadialGradient g2(780, 480, 130);
    g2.setColorAt(0, QColor(124, 58, 237, 35));
    g2.setColorAt(1, QColor(124, 58, 237, 0));
    p.setBrush(g2);
    p.drawEllipse(650, 350, 260, 260);

    // Subtle glow behind the card
    QRadialGradient g3(235, 290, 210);
    g3.setColorAt(0, QColor(29, 78, 216, 12));
    g3.setColorAt(1, QColor(29, 78, 216, 0));
    p.setBrush(g3);
    p.drawEllipse(25, 80, 420, 420);
}

void loginwindow::showError(const QString& msg) {
    ui->label_error->setText(msg);
    m_shakeStep    = 0;
    m_shakeOriginX = ui->card->x();
    m_shakeTimer->start();
}

void loginwindow::shakeAnimation() {
    static const int offsets[] =
        {-8, 8, -6, 6, -4, 4, -2, 2, 0};
    if (m_shakeStep < 9) {
        ui->card->move(
            m_shakeOriginX + offsets[m_shakeStep],
            ui->card->y());
        m_shakeStep++;
    } else {
        m_shakeTimer->stop();
        ui->card->move(m_shakeOriginX, ui->card->y());
    }
}

void loginwindow::on_pushButton_showPassword_clicked() {
    m_passwordVisible = !m_passwordVisible;
    ui->lineEdit_password->setEchoMode(
        m_passwordVisible ? QLineEdit::Normal
                          : QLineEdit::Password);
    ui->pushButton_showPassword->setText(
        m_passwordVisible ? "🙈" : "👁");
}

void loginwindow::on_pushButton_forgotPassword_clicked() {
    QMessageBox::information(this,
        "Forgot Password",
        "To reset your password, please contact\n"
        "the administrator or create a new account.\n\n"
        "Your password was set during registration.");
}

void loginwindow::on_pushButton_login_clicked() {
    QString name = ui->lineEdit_username->text().trimmed();
    QString pass = ui->lineEdit_password->text();
    ui->label_error->setText("");

    if (name.isEmpty() || pass.isEmpty()) {
        showError("Please fill in all fields.");
        return;
    }
    if (databasemanager::instance().loginuser(name, pass)) {
        databasemanager::instance().updateStreak(name);
        emit loginSuccess(name);
    } else {
        showError("Invalid username or password.");
    }
}

void loginwindow::on_pushButton_register_clicked() {
    registerwindow* regWin = new registerwindow();
    QObject::connect(regWin,
        &registerwindow::registerSuccess,
        [this, regWin]() {
            regWin->close(); regWin->deleteLater();
            this->show();
        });
    QObject::connect(regWin,
        &registerwindow::backToLoginRequested,
        [this, regWin]() {
            regWin->close(); regWin->deleteLater();
            this->show();
        });
    this->hide();
    regWin->show();
}
