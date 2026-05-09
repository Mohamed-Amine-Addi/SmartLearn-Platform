#include "loginwindow.h"
#include "ui_loginwindow.h"
#include "databasemanager.h"
#include"registerwindow.h"
#include <QMessageBox>
#include "loginwindow.h"
#include <QString>

loginwindow::loginwindow(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::loginwindow)
{
    ui->setupUi(this);
}

loginwindow::~loginwindow(){
    delete ui;
}



void loginwindow::on_pushButton_login_clicked(){
    QString name = ui->lineEdit_username->text().trimmed();
    QString pass = ui->lineEdit_password->text();
    if(name.isEmpty() || pass.isEmpty()){
        QMessageBox::warning(this,"Error", "Please fill in all fields.");
        return;
    }
    if(databasemanager::instance().loginuser(name, pass)){
        emit loginSuccess(name);
    }else{
        QMessageBox::warning(this,"Error", "Invalid Username or Password.");
    }

}


void loginwindow::on_pushButton_register_clicked(){
    // hide login, show register window
    registerwindow* regWin = new registerwindow();
     // where register done => close register, show login
    QObject::connect(regWin, &registerwindow::registerSuccess, [this, regWin](){
        regWin->close();
        regWin->deleteLater();
        this->show();
    });
    QObject::connect(regWin, &registerwindow::backToLoginRequested, [this, regWin](){
        regWin->close();
        regWin->deleteLater();
        this->show();
    });
    this->hide();
    regWin->show();
}
