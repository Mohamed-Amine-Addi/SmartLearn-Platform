#ifndef QUESTION_H
#define QUESTION_H

#include <QString>
#include <QStringList>

enum class QuestionType {
    MultipleChoice,
    TrueFalse,
    FillBlank
};

struct Question {
    int          id             = 0;
    int          courseId       = 0;
    QuestionType type           = QuestionType::MultipleChoice;
    QString      text;
    QStringList  options;        // choices for MCQ / TrueFalse
    int          correctIndex   = 0;   // index of correct option
    QString      correctAnswer;        // for FillBlank
    QString      explanation;          // shown after answering
    int          xpReward       = 10;
};

#endif // QUESTION_H
