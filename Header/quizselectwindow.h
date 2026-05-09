#ifndef QUIZSELECTWINDOW_H
#define QUIZSELECTWINDOW_H

#include <QWidget>
#include <QVBoxLayout>
#include "course.h"

namespace Ui {
class quizselectwindow;
}

class quizselectwindow : public QWidget
{
    Q_OBJECT
public:
    explicit quizselectwindow(const QString& username, QWidget* parent = nullptr);
    ~quizselectwindow();

signals:
    void backRequested();
    void quizSelected(int courseId,
                      const QString& courseTitle);

private slots:
    void on_pushButton_back_clicked();

private:
    void buildCourseCard(const course& c, QVBoxLayout* layout);
    Ui::quizselectwindow* ui;
    QString m_username;
    QVBoxLayout* m_cardsLayout = nullptr;
};

#endif
