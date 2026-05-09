#ifndef PROGRESSWINDOW_H
#define PROGRESSWINDOW_H

#include <QWidget>
#include <QString>
#include "quizhistoryentry.h"

namespace Ui {
class progresswindow;
}

class progresswindow : public QWidget
{
    Q_OBJECT
public:
    explicit progresswindow(const QString& username, QWidget* parent = nullptr);
    ~progresswindow();

signals:
    void backRequested();

private slots:
    void on_pushButton_back_clicked();

private:
    void loadStats();
    void buildHistoryCards();

    Ui::progresswindow* ui;
    QString m_username;
};

#endif
