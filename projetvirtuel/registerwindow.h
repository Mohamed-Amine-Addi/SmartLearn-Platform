#ifndef REGISTERWINDOW_H
#define REGISTERWINDOW_H
#include <QString>
#include <QWidget>

namespace Ui {
class registerwindow;
}

class registerwindow : public QWidget
{
    Q_OBJECT
public:
    explicit registerwindow(QWidget *parent = nullptr);
    ~registerwindow();

signals:
    //emitted when account created successfuly, goes back to login
    void registerSuccess();
    //emitted when user clicked already have an account
    void backToLoginRequested();
private slots:
    void on_pushButton_register_clicked();
    void on_pushButton_back_clicked();
    void on_lineEdit_password_textChanged(const QString &text);
    void on_lineEdit_confirmPassword_textChanged(const QString& text);

private:
    //returns true if all fields are valis , shows error and return false if not
    bool validateFields();
    //check password strength 0=weak,1=medium,2=strong
    int passwordStrength(const QString &password);
    //updtae the strength bar colors
    void updateStrengthBar(const QString &password);

    Ui::registerwindow *ui;
};

#endif // REGISTERWINDOW_H
