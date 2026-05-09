#ifndef QUIZRESULT_H
#define QUIZRESULT_H

#include <QString>
#include <QList>

struct AnswerRecord {
    int     questionId  = 0;
    int     givenIndex  = -1;
    QString givenText;
    bool    correct     = false;
};

struct QuizResult {
    int              courseId   = 0;
    QString          courseTitle;
    int              score      = 0;    // 0 to 100
    int              xpEarned   = 0;
    int              correct    = 0;
    int              total      = 0;
    QList<AnswerRecord> answers;
};

#endif
