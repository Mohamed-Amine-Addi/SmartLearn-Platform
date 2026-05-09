#include "registerwindow.h"
#include "ui_registerwindow.h"
#include "databasemanager.h"
#include <QMessageBox>
#include <QRegularExpression>
#include <QLineEdit>
#include <QPixmap>

registerwindow::registerwindow(QWidget* parent)
    : QWidget(parent)
    , ui(new Ui::registerwindow)
{
    ui->setupUi(this);
    setWindowTitle("Langora - Create Account");
    //load logo from resources
    QPixmap logo(":/logo.png");
    ui->label_logo->setPixmap(logo.scaled(120,120,Qt::KeepAspectRatio,Qt::SmoothTransformation));

    // Password field hides characters
    ui->lineEdit_password->setEchoMode(QLineEdit::Password);
    ui->lineEdit_confirmPassword->setEchoMode(QLineEdit::Password);
    // start with hidden strenght bar
    ui->label_strength->setText("");
}

registerwindow::~registerwindow(){
    delete ui;
}
void registerwindow::on_lineEdit_confirmPassword_textChanged(const QString& text){
    QString pass = ui->lineEdit_password->text();
    if(text.isEmpty()){
        ui->label_confirmMatch->setText("");
        return;
    }
    if (text == pass){
        ui->label_confirmMatch->setText("passords match");
        ui->label_confirmMatch->setStyleSheet("color: #66bb6a; font-size: 11px;");
    }else{
        ui->label_confirmMatch->setText("passords do not match");
        ui->label_confirmMatch->setStyleSheet("color: #e53935; font-size: 11px;");
    }
}

//password strength logic
int registerwindow::passwordStrength(const QString& password){
    if(password.length()<6) return 0;

    bool hasUpper = password.contains(QRegularExpression("[A-Z]"));
    bool hasLower = password.contains(QRegularExpression("[a-z]"));
    bool hasDigit = password.contains(QRegularExpression("[0-9]"));
    bool hasSymbol = password.contains(QRegularExpression("[^a-zA-Z0-9]"));
    bool longEnough = password.length()>=10;

    int score = (hasUpper ? 1:0) + (hasLower ? 1:0) + (hasDigit ? 1:0) + (hasSymbol ? 1:0) + (longEnough ? 1:0);
    if(score<=2) return 0; //weak
    if(score<=3) return 1; //medium
    return 2; //strong
}
void registerwindow::updateStrengthBar(const QString& password){
    if(password.isEmpty()){
        ui->label_strength->setText("");
        // reset all 4 segments to grey
        ui->frame_bar1->setStyleSheet("background:#21262d; border-radius:2px;");
        ui->frame_bar2->setStyleSheet("background:#21262d; border-radius:2px;");
        ui->frame_bar3->setStyleSheet("background:#21262d; border-radius:2px;");
        ui->frame_bar4->setStyleSheet("background:#21262d; border-radius:2px;");
        return;
    }

    int strength = passwordStrength(password);
    QString weakColor = "background:#e53935; border-radius:2px";
    QString medColor = "background:#ffa726; border-radius:2px";
    QString strongColor = "background:#66bb6a; border-radius:2px";
    QString emptyColor = "background:#21262d; border-radius:2px";

    if(strength == 0){ // weak , 1 red bar
        ui->frame_bar1->setStyleSheet(weakColor);
        ui->frame_bar2->setStyleSheet(emptyColor);
        ui->frame_bar3->setStyleSheet(emptyColor);
        ui->frame_bar4->setStyleSheet(emptyColor);
        ui->label_strength->setText("Weak password");
        ui->label_strength->setStyleSheet("color:#66bb6a; font-size:11px;");
    }else if(strength == 1){ // medium, 3 orange bars
        ui->frame_bar1->setStyleSheet(medColor);
        ui->frame_bar2->setStyleSheet(medColor);
        ui->frame_bar3->setStyleSheet(medColor);
        ui->frame_bar4->setStyleSheet(emptyColor);
        ui->label_strength->setText("Medium password");
        ui->label_strength->setStyleSheet("color:#e53935; font-size:11px;");
    }else{ // strong, 4 green bars
        ui->frame_bar1->setStyleSheet(strongColor);
        ui->frame_bar2->setStyleSheet(strongColor);
        ui->frame_bar3->setStyleSheet(strongColor);
        ui->frame_bar4->setStyleSheet(strongColor);
        ui->label_strength->setText("Strong passprd");
        ui->label_strength->setStyleSheet("color:#ffa726; font-size:11px;");
    }

}
void registerwindow::on_lineEdit_password_textChanged(const QString& text) {
    updateStrengthBar(text);
}

//Full validation after submitting

bool registerwindow::validateFields(){
    QString firstname = ui->lineEdit_firstName->text().trimmed();
    QString lastname = ui->lineEdit_lastName->text().trimmed();
    QString username = ui->lineEdit_username->text().trimmed();
    QString email = ui->lineEdit_email->text().trimmed();
    QString password = ui->lineEdit_password->text();
    QString confirm = ui->lineEdit_confirmPassword->text();

    //check nothing is empty
    if(firstname.isEmpty() || lastname.isEmpty() || username.isEmpty() || email.isEmpty() || password.isEmpty()|| confirm.isEmpty()){
        QMessageBox::warning(this,"Missing Fields","Please fill in all fields.");
        return false;
    }

    //username must be at least 3 characters
    if(username.length()<3){
        QMessageBox::warning(this,"Username Invalid","Username must be at least 3 characters.");
        return false;
    }

    QRegularExpression usernameRegex("^[a-zA-Z0-9_]+$");
    if(!usernameRegex.match(username).hasMatch()){
        QMessageBox::warning(this,"Username Invalid","Username can only contain letters, numbers, and underscores.");
        return false;
    }

    QRegularExpression emailRegex(R"(^[^@]+@[^@]+\.[^@]+$)");
    if(!emailRegex.match(email).hasMatch()){
        QMessageBox::warning(this,"Username Invalid","Username can only contain letters, numbers, and underscores.");
        return false;
    }

    //password must be at least 6 characters
    if(password.length()<6){
        QMessageBox::warning(this,"Passwrd Too Short","Password must be at least 6 characters.");
        return false;
    }

    if(password != confirm){
        QMessageBox::warning(this,"Passwrd Don't Match","Password and confirm password must be the same.");
        return false;
    }

    //check username not already taken
    if(databasemanager::instance().usernameexists(username)){
        QMessageBox::warning(this,"Username Taken","This username is already taken. Please choose another one");
        return false;
    }

    //check email is not already registered
    if(databasemanager::instance().emailexists(email)){
        QMessageBox::warning(this,"Email Already Registered","An account with this email already exists.");
        return false;
    }
    return true;
}

//create account button clicked
void registerwindow::on_pushButton_register_clicked() {
    if(!validateFields()) return; // stop if any field is wrong

    QString firstname = ui->lineEdit_firstName->text().trimmed();
    QString lastname = ui->lineEdit_lastName->text().trimmed();
    QString username = ui->lineEdit_username->text().trimmed();
    QString email = ui->lineEdit_email->text().trimmed();
    QString password = ui->lineEdit_password->text();

    if(databasemanager::instance().registeruser(firstname, lastname, username, email, password)){
        QMessageBox::information(this,"Account Created","Welcome to Langora, " + firstname + "!\n");
        emit registerSuccess();
    }else{
        QMessageBox::critical(this,"Error", "Something went wrong. Please try again.");
    }
}

//back to login button clicked
void registerwindow::on_pushButton_back_clicked(){
    emit backToLoginRequested();
}

