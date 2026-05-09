#ifndef LESSONVIEWERWINDOW_H
#define LESSONVIEWERWINDOW_H

#include <QWidget>
#include <QList>
#include "databasemanager.h"

namespace Ui { class lessonviewerwindow; }

class lessonviewerwindow : public QWidget
{
    Q_OBJECT
public:
    explicit lessonviewerwindow(int courseId,
                                const QString& courseTitle,
                                const QString& username,
                                QWidget* parent = nullptr);
    ~lessonviewerwindow();

signals:
    void backRequested();
    void allLessonsComplete(int courseId,
                            const QString& courseTitle);

private slots:
    void on_pushButton_back_clicked();
    void on_pushButton_next_clicked();
    void on_pushButton_prev_clicked();

private:
    void showLesson(int index);
    void updateButtons();

    Ui::lessonviewerwindow*               ui;
    QList<databasemanager::LessonContent> m_lessons;
    int     m_currentIndex = 0;
    int     m_courseId     = 0;
    QString m_courseTitle;
    QString m_username;
};

#endif // LESSONVIEWERWINDOW_H
