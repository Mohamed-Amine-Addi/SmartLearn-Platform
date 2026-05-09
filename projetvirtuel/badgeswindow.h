#ifndef BADGESWINDOW_H
#define BADGESWINDOW_H

#include <QWidget>
#include <QString>

namespace Ui {
class badgeswindow;
}

class badgeswindow : public QWidget
{
    Q_OBJECT
public:
    explicit badgeswindow(const QString& username, QWidget* parent = nullptr);
    ~badgeswindow();

signals:
    void backRequested();

private slots:
    void on_pushButton_back_clicked();

private:
    void buildBadgeCards();
    Ui::badgeswindow* ui;
    QString m_username;
};

#endif // BADGESWINDOW_H
