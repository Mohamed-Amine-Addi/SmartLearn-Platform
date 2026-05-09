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



class databasemanager{
public:

    // Singleton : call databasemanager::instance() everywhere
    static databasemanager& instance();
    bool init(const QString& dbPath);


    //authentification functions
    bool registeruser(const QString& firstname, const QString& lastname, const QString& username, const QString& email, const QString& password );
    bool loginuser(const QString& name, const QString& password);

    //Check if username or email already exists
    bool usernameexists(const QString &username);
    bool emailexists(const QString& email);

    //user data
    int getUserXp(const QString& username);
    int getUserLevel(const QString& username);
    QString getUserFirstname(const QString& username);
    QList<course> getAllCourses();
    bool courseExists(const QString& title);
    QList<Question> getQuestionsForCourse(int courseId);
    bool saveQuizResult(const QString& username, const QuizResult& result);
    void addXpToUser(const QString& username, int xp);


    //progress screen methods
    QList<QuizHistoryEntry> getQuizHistory(const QString& username);
    int getTotalQuizesDone(const QString& username);
    int getAverageScore(const QString& username);

    void checkAndAwardBadges(const QString& username);
    QList<Badge>     getUserBadges(const QString& username);
    bool hasBadge(const QString& username, const QString& key);
    bool awardBadge(const QString& username, const QString& key);
    //Lessons
    struct LessonContent {
        int     id = 0;
        int     courseId = 0;
        int     orderNum = 0;
        QString title;
        QString content;   //rich text content
    };

    QList<LessonContent> getLessonsForCourse(int courseId);


private:
    databasemanager()=default;
    databasemanager(const databasemanager&) = delete;
    bool createTables();
    void seedCourses(); //insert default courses if table is empty
    void seedQuestions();
    void seedLessons();
    QSqlDatabase m_db;

};

#endif // DATABASEMANAGER_H
