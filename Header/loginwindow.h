#ifndef LOGINWINDOW_H
#define LOGINWINDOW_H


#include <QObject>
#include <QWidget>

namespace Ui{
class loginwindow;

}

class loginwindow : public QWidget
{
    Q_OBJECT
public:
    explicit loginwindow(QWidget *parent = nullptr);
    ~loginwindow();
signals:
    void loginSuccess(const QString& username);

private slots:
    void on_pushButton_login_clicked();
    void on_pushButton_register_clicked();
private:
    Ui::loginwindow *ui;
};


#endif
