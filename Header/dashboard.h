#ifndef DASHBOARD_H
#define DASHBOARD_H
#include <QString>
#include <QWidget>
#include <QPushButton>
#include "badge.h"

namespace Ui {
class dashboard;
}
class dashboard : public QWidget
{
    Q_OBJECT
public:
    explicit dashboard(const QString &username, QWidget *parent = nullptr);
    ~dashboard();
    void loadUserStats();

signals:
    void logoutRequested();
    void openCoursesRequested();
    void openQuizRequested();
    void openProgressRequested();
    void openBadgesRequested();


private slots:
    void on_pushButton_logout_clicked();
    void on_pushButton_courses_clicked();
    void on_pushButton_startQuiz_clicked();
    void on_nav_progress_clicked();
    void on_nav_badges_clicked();

private:
    void loadUserStats();
    void loadRecentActivity();
    Ui::dashboard *ui;
    QString m_username;
};

#endif // DASHBOARD_H
