#ifndef QUIZRESULTWINDOW_H
#define QUIZRESULTWINDOW_H

#include <QWidget>
#include "quizresult.h"

namespace Ui {
class quizresultwindow;
}

class quizresultwindow : public QWidget
{
    Q_OBJECT
public:
    explicit quizresultwindow(const QuizResult& result, QWidget* parent = nullptr);
    ~quizresultwindow();

signals:
    void backToDashboard();
    void retryQuiz();

private slots:
    void on_pushButton_dashboard_clicked();
    void on_pushButton_retry_clicked();

private:
    Ui::quizresultwindow* ui;
    QuizResult m_result;
};

#endif
