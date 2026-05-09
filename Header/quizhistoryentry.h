#ifndef QUIZHISTORYENTRY_H
#define QUIZHISTORYENTRY_H

#include <QString>

struct QuizHistoryEntry {
    QString courseTitle;
    int     score    = 0;
    int     correct  = 0;
    int     total    = 0;
    int     xpEarned = 0;
    QString takenAt;
};

#endif
