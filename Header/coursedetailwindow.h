#ifndef COURSEDETAILWINDOW_H
#define COURSEDETAILWINDOW_H

#include <QWidget>
#include "course.h"

namespace Ui {
class coursedetailwindow;
}

class coursedetailwindow : public QWidget
{
    Q_OBJECT
public:
    explicit coursedetailwindow(const course& c, const QString& username, QWidget* parent = nullptr);
    ~coursedetailwindow();

signals:
    void backRequested();
    void startQuizRequested(int courseId, const QString& courseTitle);
    void startLearningRequested(int courseId, const QString& courseTitle);

private slots:
    void on_pushButton_back_clicked();
    void on_pushButton_startQuiz_clicked();

private:
    Ui::coursedetailwindow* ui;
    course m_course;
    QString m_username;
};

#endif // COURSEDETAILWINDOW_H
