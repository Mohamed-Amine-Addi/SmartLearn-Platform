#ifndef QUIZWINDOW_H
#define QUIZWINDOW_H

#include <QWidget>
#include <QList>
#include <QButtonGroup>
#include "question.h"
#include "quizresult.h"

namespace Ui {
class quizwindow;
}

class quizwindow : public QWidget
{
    Q_OBJECT
public:
    explicit quizwindow(int courseId,
                        const QString& courseTitle,
                        const QString& username,
                        QWidget* parent = nullptr);
    ~quizwindow();

signals:
    void quizFinished(const QuizResult& result);
    void backRequested();

private slots:
    void on_pushButton_submit_clicked();
    void on_pushButton_back_clicked();

private:
    void showQuestion(int index);
    void showFeedback(bool correct, const QString& explanation);
    void proceedToNext();
    void finishQuiz();

    Ui::quizwindow* ui;
    QList<Question> m_questions;
    QList<AnswerRecord> m_answers;
    QButtonGroup*   m_optionGroup = nullptr;
    int             m_currentIndex = 0;
    QString         m_username;
    QString         m_courseTitle;
    bool            m_waitingForNext = false;
    int             m_courseId = 0;
};

#endif // QUIZWINDOW_H
