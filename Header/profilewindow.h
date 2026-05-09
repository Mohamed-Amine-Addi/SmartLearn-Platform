#ifndef PROFILEWINDOW_H
#define PROFILEWINDOW_H

#include <QWidget>
#include <QString>

namespace Ui {
class profilewindow;
}

class profilewindow : public QWidget
{
    Q_OBJECT
public:
    explicit profilewindow(const QString& username,
                           QWidget* parent = nullptr);
    ~profilewindow();

signals:
    void backRequested();
    // Emitted when username changes so dashboard can update
    void profileUpdated(const QString& newUsername);

private slots:
    void on_pushButton_back_clicked();
    void on_pushButton_save_clicked();
    void on_pushButton_changePassword_clicked();
    void on_lineEdit_newUsername_textChanged(const QString& text);
    void on_lineEdit_newEmail_textChanged(const QString& text);

private:
    void loadProfile();
    void setFieldEditable(bool editable);

    Ui::profilewindow* ui;
    QString m_username;  // current username (may change after save)

    // Track original values to detect changes
    QString m_originalUsername;
    QString m_originalEmail;
    QString m_originalFirstname;
    QString m_originalLastname;
};

#endif // PROFILEWINDOW_H
