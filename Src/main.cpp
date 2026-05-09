#include <QStandardPaths>
#include <QDir>
#include <QApplication>
#include <QFile>
#include <QDebug>
#include "loginwindow.h"
#include "databasemanager.h"
#include "dashboard.h"
#include "coursewindow.h"
#include "coursedetailwindow.h"
#include "lessonviewerwindow.h"
#include "quizselectwindow.h"
#include "quizwindow.h"
#include "quizresultwindow.h"
#include "progresswindow.h"
#include "badgeswindow.h"

//Free functions

void openResultWindow(dashboard* dashWin, QWidget* parentWin, QWidget* courseListWin, const QuizResult& result)
{
    quizresultwindow* rWin = new quizresultwindow(result);

    // Back to dashboard
    QObject::connect(rWin,
                     &quizresultwindow::backToDashboard,
                     [dashWin, parentWin, courseListWin, rWin]()
                     {
                         rWin->close();         rWin->deleteLater();
                         parentWin->close();    parentWin->deleteLater();
                         courseListWin->close();courseListWin->deleteLater();
                         dashWin->loadUserStats();
                         dashWin->show();
                     });

    // Retry -> back to parent (detail or quiz select)
    QObject::connect(rWin,
                     &quizresultwindow::retryQuiz,
                     [parentWin, rWin]()
                     {
                         rWin->close();
                         rWin->deleteLater();
                         parentWin->show();
                     });

    rWin->show();
}

void openQuizFromDetail(dashboard* dashWin,
                        coursewindow* courseWin,
                        coursedetailwindow* detailWin,
                        int courseId,
                        const QString& courseTitle,
                        const QString& username)
{
    quizwindow* quizWin = new quizwindow(
        courseId, courseTitle, username);

    QObject::connect(quizWin,
                     &quizwindow::backRequested,
                     [detailWin, quizWin]()
                     {
                         quizWin->close();
                         quizWin->deleteLater();
                         detailWin->show();
                     });

    QObject::connect(quizWin,
                     &quizwindow::quizFinished,
                     [dashWin, courseWin, detailWin, quizWin]
                     (const QuizResult& result)
                     {
                         quizWin->close();
                         quizWin->deleteLater();
                         //detailWin is the parent, courseWin is the list
                         openResultWindow(dashWin, detailWin, courseWin, result);
                     });

    detailWin->hide();
    quizWin->show();
}

void openLessonWindow(dashboard* dashWin, coursewindow* courseWin, coursedetailwindow* detailWin, int courseId, const QString& courseTitle, const QString& username)
{
    lessonviewerwindow* lessonWin = new lessonviewerwindow(courseId, courseTitle, username);

    QObject::connect(lessonWin,
                     &lessonviewerwindow::backRequested,
                     [detailWin, lessonWin]()
                     {
                         lessonWin->close();
                         lessonWin->deleteLater();
                         detailWin->show();
                     });

    QObject::connect(lessonWin,
                     &lessonviewerwindow::allLessonsComplete,
                     [dashWin, courseWin, detailWin,
                      lessonWin, username]
                     (int qId, const QString& qTitle)
                     {
                         lessonWin->close();
                         lessonWin->deleteLater();
                         openQuizFromDetail(dashWin, courseWin, detailWin, qId, qTitle, username);
                     });

    detailWin->hide();
    lessonWin->show();
}

void openDetailWindow(dashboard* dashWin, coursewindow* courseWin, int courseId, const QString& username)
{
    QList<course> all =
        databasemanager::instance().getAllCourses();
    course selected;
    for (const course& c : all) {
        if (c.id == courseId) { selected = c; break; }
    }

    coursedetailwindow* detailWin =
        new coursedetailwindow(selected, username);

    QObject::connect(detailWin,
                     &coursedetailwindow::backRequested,
                     [courseWin, detailWin]()
                     {
                         detailWin->close();
                         detailWin->deleteLater();
                         courseWin->show();
                     });

    QObject::connect(detailWin,
                     &coursedetailwindow::startLearningRequested,
                     [dashWin, courseWin, detailWin, username]
                     (int cId, const QString& cTitle)
                     {
                         openLessonWindow(dashWin, courseWin, detailWin, cId, cTitle, username);
                     });
    courseWin->hide();
    detailWin->show();
}

//main
int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QFile styleFile(":/app.qss");
    if (styleFile.open(QFile::ReadOnly)) {
        app.setStyleSheet(styleFile.readAll());
        qDebug() << "QSS loaded OK";
    }
    app.setApplicationName("Langora");

    QString dataPath = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);
    QDir().mkpath(dataPath);
    databasemanager::instance().init(dataPath + "/app.db");

    loginwindow* loginWin = new loginwindow();
    loginWin->show();

    QObject::connect(loginWin, &loginwindow::loginSuccess,
                     [loginWin](const QString& username)
                     {
                         dashboard* dashWin = new dashboard(username);

                         // Logout
                         QObject::connect(dashWin,
                                          &dashboard::logoutRequested,
                                          [loginWin, dashWin]()
                                          {
                                              dashWin->close();
                                              dashWin->deleteLater();
                                              loginWin->show();
                                          });

                         //COURSES button → course list → detail → lessons → quiz
                         QObject::connect(dashWin,
                                          &dashboard::openCoursesRequested,
                                          [dashWin, username]()
                                          {
                                              coursewindow* cw =
                                                  new coursewindow(username);

                                              // Back → dashboard
                                              QObject::connect(cw,
                                                               &coursewindow::backRequested,
                                                               [dashWin, cw]()
                                                               {
                                                                   cw->close();
                                                                   cw->deleteLater();
                                                                   dashWin->show();
                                                               });

                                              //Card clicked → course detail
                                              QObject::connect(cw,
                                                               &coursewindow::courseStarted,
                                                               [dashWin, cw, username]
                                                               (int courseId, const QString&)
                                                               {
                                                                   openDetailWindow(dashWin, cw, courseId, username);
                                                               });

                                              dashWin->hide();
                                              cw->show();
                                          });

                         //QUIZ button → quiz select → direct quiz (no lessons)
                         QObject::connect(dashWin, &dashboard::openQuizRequested, [dashWin, username]()
                                          {
                                              quizselectwindow* qsw = new quizselectwindow(username);

                                              // Back → dashboard
                                              QObject::connect(qsw,
                                                               &quizselectwindow::backRequested,
                                                               [dashWin, qsw]()
                                                               {
                                                                   qsw->close();
                                                                   qsw->deleteLater();
                                                                   dashWin->show();
                                                               });

                                              // Quiz selected → open quiz directly
                                              QObject::connect(qsw, &quizselectwindow::quizSelected, [dashWin, qsw, username] (int courseId, QString& courseTitle)
                                                               {
                                                                   quizwindow* quizWin =
                                                                       new quizwindow(courseId, courseTitle, username);

                                                                   // Exit → back to quiz select
                                                                   QObject::connect(quizWin,
                                                                                    &quizwindow::backRequested,
                                                                                    [qsw, quizWin]()
                                                                                    {
                                                                                        quizWin->close();
                                                                                        quizWin->deleteLater();
                                                                                        qsw->show();
                                                                                    });

                                                                   // Done → results
                                                                   QObject::connect(quizWin,
                                                                                    &quizwindow::quizFinished,
                                                                                    [dashWin, qsw, quizWin]
                                                                                    (const QuizResult& result)
                                                                                    {
                                                                                        quizWin->close();
                                                                                        quizWin->deleteLater();

                                                                                        quizresultwindow* rWin =
                                                                                            new quizresultwindow(result);

                                                                                        // Back to dashboard
                                                                                        QObject::connect(rWin,
                                                                                                         &quizresultwindow
                                                                                                         ::backToDashboard,
                                                                                                         [dashWin, qsw, rWin]()
                                                                                                         {
                                                                                                             rWin->close();
                                                                                                             rWin->deleteLater();
                                                                                                             qsw->close();
                                                                                                             qsw->deleteLater();
                                                                                                             dashWin->loadUserStats();
                                                                                                             dashWin->show();
                                                                                                         });

                                                                                        // Retry → quiz select
                                                                                        QObject::connect(rWin, &quizresultwindow::retryQuiz,[qsw, rWin]()
                                                                                                         {
                                                                                                             rWin->close();
                                                                                                             rWin->deleteLater();
                                                                                                             qsw->show();
                                                                                                         });

                                                                                        rWin->show();
                                                                                    });

                                                                   qsw->hide();
                                                                   quizWin->show();
                                                               });

                                              dashWin->hide();
                                              qsw->show();
                                          });
                      //PROGRESS button
                         QObject::connect(dashWin, &dashboard::openProgressRequested,[dashWin, username]()
                                          {
                                              progresswindow* pw =
                                                  new progresswindow(username);
                                              QObject::connect(pw,
                                                               &progresswindow::backRequested,
                                                               [dashWin, pw]()
                                                               {
                                                                   pw->close();
                                                                   pw->deleteLater();
                                                                   dashWin->loadUserStats();
                                                                   dashWin->show();
                                                               });
                                              dashWin->hide();
                                              pw->show();
                                          });

                         // ── BADGES button
                         QObject::connect(dashWin, &dashboard::openBadgesRequested, [dashWin, username]()
                                          {
                                              badgeswindow* bw =
                                                  new badgeswindow(username);
                                              QObject::connect(bw, &badgeswindow::backRequested, [dashWin, bw]()
                                                               {
                                                                   bw->close();
                                                                   bw->deleteLater();
                                                                   dashWin->loadUserStats();
                                                                   dashWin->show();
                                                               });
                                              dashWin->hide();
                                              bw->show();
                                          });

                         loginWin->hide();
                         dashWin->show();
                     });

    return app.exec();
}
