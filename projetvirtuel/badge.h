#ifndef BADGE_H
#define BADGE_H

#include <QString>

struct Badge {
    QString key;          // unique identifier stored in DB
    QString name;         // display name
    QString description;  // what the user did to earn it
    QString icon;         // emoji or symbol
    bool    unlocked = false;
};

// All badges the app can award — defined once here
inline QList<Badge> allBadges() {
    return {
            {"first_quiz",   "First Step",
             "Complete your first quiz",          "★"},
            {"score_100",    "Perfectionist",
             "Score 100% on any quiz",            "◆"},
            {"quiz_5",       "Quiz Enthusiast",
             "Complete 5 quizzes",                "▲"},
            {"quiz_10",      "Quiz Master",
             "Complete 10 quizzes",               "●"},
            {"xp_100",       "Century",
             "Earn 100 XP total",                 "✦"},
            {"xp_500",       "Rising Star",
             "Earn 500 XP total",                 "✸"},
            {"level_3",      "Level 3",
             "Reach level 3",                     "▶"},
            {"level_5",      "Expert",
             "Reach level 5",                     "◉"},
            {"avg_80",       "High Achiever",
             "Maintain an average score above 80%","⬟"},
            };
}

#endif // BADGE_H
