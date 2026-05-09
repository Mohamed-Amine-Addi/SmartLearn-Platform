#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H

#include <QSqlError>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QDebug>
#include <QString>
#include <QList>
#include "course.h"
#include "question.h"
#include "quizresult.h"
#include "quizhistoryentry.h"
#include "badge.h"

class databasemanager {
public:
    static databasemanager& instance();
    bool init(const QString& dbPath);

    // Auth
    bool registeruser(const QString& firstname,
                      const QString& lastname,
                      const QString& username,
                      const QString& email,
                      const QString& password);
    bool loginuser(const QString& name, const QString& password);
    bool usernameexists(const QString& username);
    bool emailexists(const QString& email);

    // User data
    int     getUserXp(const QString& username);
    int     getUserLevel(const QString& username);
    QString getUserFirstname(const QString& username);
    int     getUserStreak(const QString& username);

    // Full profile data — all fields at once
    struct UserProfile {
        QString firstname;
        QString lastname;
        QString username;
        QString email;
        int     xp        = 0;
        int     level     = 1;
        int     streak    = 0;
        QString createdAt;
    };
    UserProfile getUserProfile(const QString& username);

    // Update profile fields
    bool updateProfile(const QString& currentUsername,
                       const QString& newFirstname,
                       const QString& newLastname,
                       const QString& newUsername,
                       const QString& newEmail,
                       const QString& currentPassword);

    // Change password
    bool changePassword(const QString& username,
                        const QString& currentPassword,
                        const QString& newPassword);

    // Streak — call on every login
    void updateStreak(const QString& username);

    // Course progress
    void markCourseStarted(const QString& username, int courseId);
    void markCourseCompleted(const QString& username, int courseId);
    int  getCoursesStarted(const QString& username);

    // Courses
    QList<course> getAllCourses();
    bool          courseExists(const QString& title);

    // Lessons
    struct LessonContent {
        int     id       = 0;
        int     courseId = 0;
        int     orderNum = 0;
        QString title;
        QString content;
    };
    QList<LessonContent> getLessonsForCourse(int courseId);

    // Quiz
    QList<Question> getQuestionsForCourse(int courseId);
    bool            saveQuizResult(const QString& username,
                                   const QuizResult& result);
    void            addXpToUser(const QString& username, int xp);

    // Progress
    QList<QuizHistoryEntry> getQuizHistory(const QString& username);
    int getTotalQuizesDone(const QString& username);
    int getAverageScore(const QString& username);

    // Badges
    void         checkAndAwardBadges(const QString& username);
    QList<Badge> getUserBadges(const QString& username);
    bool         hasBadge(const QString& username, const QString& key);
    bool         awardBadge(const QString& username, const QString& key);

private:
    databasemanager() = default;
    databasemanager(const databasemanager&) = delete;
    bool createTables();
    void seedCourses();
    void seedQuestions();
    void seedLessons();
    QSqlDatabase m_db;
};

#endif // DATABASEMANAGER_H
