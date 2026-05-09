#ifndef LOGINWINDOW_H
#define LOGINWINDOW_H

#include <QObject>
#include <QWidget>
#include <QTimer>
#include <QGraphicsOpacityEffect>

namespace Ui {
class loginwindow;
}

class loginwindow : public QWidget
{
    Q_OBJECT
public:
    explicit loginwindow(QWidget* parent = nullptr);
    ~loginwindow();

signals:
    void loginSuccess(const QString& username);

protected:
    void paintEvent(QPaintEvent* event) override;

private slots:
    void on_pushButton_login_clicked();
    void on_pushButton_register_clicked();
    void on_pushButton_showPassword_clicked();
    void on_pushButton_forgotPassword_clicked();
    void shakeAnimation();

private:
    void setupAnimations();
    void showError(const QString& msg);

    Ui::loginwindow* ui;
    bool m_passwordVisible = false;
    QTimer* m_shakeTimer   = nullptr;
    int     m_shakeStep    = 0;
    int     m_shakeOriginX = 0;
};

#endif // LOGINWINDOW_H
