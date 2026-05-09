#include <QMessageBox>
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
#include "profilewindow.h"

// ═══════════════════════════════════════════════════════════════
//  COURSE FLOW: Courses → Detail → Lessons → back to dashboard
//  (NO quiz at end of lessons — courses and quizzes are separate)
// ═══════════════════════════════════════════════════════════════

// Called when user finishes all lessons in a course
void courseFinished(dashboard* dashWin,
                    coursewindow* courseWin,
                    coursedetailwindow* detailWin,
                    lessonviewerwindow* lessonWin,
                    int /*courseId*/,
                    const QString& courseTitle)
{
    lessonWin->close();
    lessonWin->deleteLater();
    detailWin->close();
    detailWin->deleteLater();
    courseWin->close();
    courseWin->deleteLater();

    // Show congratulations and return to dashboard
    QMessageBox::information(
        dashWin,
        "Course Complete! 🎉",
        QString("Congratulations!\n\n"
                "You completed \"%1\".\n\n"
                "Head to the Quiz section to test your knowledge "
                "and earn XP!").arg(courseTitle));

    dashWin->loadUserStats();
    dashWin->show();
}

void openLessonWindow(dashboard* dashWin,
                      coursewindow* courseWin,
                      coursedetailwindow* detailWin,
                      int courseId,
                      const QString& courseTitle,
                      const QString& username)
{
    lessonviewerwindow* lessonWin =
        new lessonviewerwindow(courseId, courseTitle, username);

    // Back → course detail
    QObject::connect(lessonWin,
        &lessonviewerwindow::backRequested,
        [detailWin, lessonWin]() {
            lessonWin->close();
            lessonWin->deleteLater();
            detailWin->show();
        });

    // All lessons done → congratulations + back to dashboard
    QObject::connect(lessonWin,
        &lessonviewerwindow::allLessonsComplete,
        [dashWin, courseWin, detailWin, lessonWin]
        (int cId, const QString& cTitle) {
            courseFinished(dashWin, courseWin,
                           detailWin, lessonWin,
                           cId, cTitle);
        });

    detailWin->hide();
    lessonWin->show();
}

void openDetailWindow(dashboard* dashWin,
                      coursewindow* courseWin,
                      int courseId,
                      const QString& username)
{
    QList<course> all =
        databasemanager::instance().getAllCourses();
    course selected;
    for (const course& c : all)
        if (c.id == courseId) { selected = c; break; }

    coursedetailwindow* detailWin =
        new coursedetailwindow(selected, username);

    // Back → course list
    QObject::connect(detailWin,
        &coursedetailwindow::backRequested,
        [courseWin, detailWin]() {
            detailWin->close();
            detailWin->deleteLater();
            courseWin->show();
        });

    // Start Learning → lessons (no quiz at end)
    QObject::connect(detailWin,
        &coursedetailwindow::startLearningRequested,
        [dashWin, courseWin, detailWin, username]
        (int cId, const QString& cTitle) {
            openLessonWindow(dashWin, courseWin,
                             detailWin, cId,
                             cTitle, username);
        });

    courseWin->hide();
    detailWin->show();
}

// ═══════════════════════════════════════════════════════════════
//  QUIZ FLOW: Quiz button → QuizSelect → Quiz → Results
//  (completely separate from courses)
// ═══════════════════════════════════════════════════════════════

void openQuizResultWindow(dashboard* dashWin,
                          quizselectwindow* qsWin,
                          const QuizResult& result,
                          const QString& username)
{
    quizresultwindow* rWin = new quizresultwindow(result);

    // Back to dashboard
    QObject::connect(rWin,
        &quizresultwindow::backToDashboard,
        [dashWin, qsWin, rWin]() {
            rWin->close();  rWin->deleteLater();
            qsWin->close(); qsWin->deleteLater();
            dashWin->loadUserStats();
            dashWin->show();
        });

    // Retry → back to quiz select
    QObject::connect(rWin,
        &quizresultwindow::retryQuiz,
        [qsWin, rWin]() {
            rWin->close();
            rWin->deleteLater();
            qsWin->show();
        });

    rWin->show();
}

void openQuizWindow(dashboard* dashWin,
                    quizselectwindow* qsWin,
                    int courseId,
                    const QString& courseTitle,
                    const QString& username)
{
    quizwindow* quizWin =
        new quizwindow(courseId, courseTitle, username);

    // Exit → back to quiz select
    QObject::connect(quizWin,
        &quizwindow::backRequested,
        [qsWin, quizWin]() {
            quizWin->close();
            quizWin->deleteLater();
            qsWin->show();
        });

    // Finished → results screen
    QObject::connect(quizWin,
        &quizwindow::quizFinished,
        [dashWin, qsWin, quizWin, username]
        (const QuizResult& result) {
            quizWin->close();
            quizWin->deleteLater();
            openQuizResultWindow(dashWin, qsWin,
                                 result, username);
        });

    qsWin->hide();
    quizWin->show();
}

// ═══════════════════════════════════════════════════════════════
//  MAIN
// ═══════════════════════════════════════════════════════════════
int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QFile styleFile(":/app.qss");
    if (styleFile.open(QFile::ReadOnly))
        app.setStyleSheet(styleFile.readAll());

    app.setApplicationName("Langora");

    QString dataPath = QStandardPaths::writableLocation(
        QStandardPaths::AppDataLocation);
    QDir().mkpath(dataPath);

    // ── Uncomment ONCE to reset database, then re-comment ────
    // QFile::remove(dataPath + "/app.db");
    // ─────────────────────────────────────────────────────────

    databasemanager::instance().init(dataPath + "/app.db");

    loginwindow* loginWin = new loginwindow();
    loginWin->show();

    QObject::connect(loginWin, &loginwindow::loginSuccess,
        [loginWin](const QString& username)
        {
            dashboard* dashWin = new dashboard(username);

            // ── Logout ───────────────────────────────────────
            QObject::connect(dashWin,
                &dashboard::logoutRequested,
                [loginWin, dashWin]() {
                    dashWin->close();
                    dashWin->deleteLater();
                    loginWin->show();
                });

            // ── COURSES button ────────────────────────────────
            // Flow: course list → detail → lessons → dashboard
            QObject::connect(dashWin,
                &dashboard::openCoursesRequested,
                [dashWin, username]() {
                    coursewindow* cw =
                        new coursewindow(username);

                    // Back → dashboard
                    QObject::connect(cw,
                        &coursewindow::backRequested,
                        [dashWin, cw]() {
                            cw->close();
                            cw->deleteLater();
                            dashWin->show();
                        });

                    // Course card clicked → detail
                    QObject::connect(cw,
                        &coursewindow::courseStarted,
                        [dashWin, cw, username]
                        (int courseId, const QString&) {
                            openDetailWindow(dashWin, cw,
                                             courseId,
                                             username);
                        });

                    dashWin->hide();
                    cw->show();
                });

            // ── QUIZ button ───────────────────────────────────
            // Flow: quiz select → quiz → results → dashboard
            QObject::connect(dashWin,
                &dashboard::openQuizRequested,
                [dashWin, username]() {
                    quizselectwindow* qsWin =
                        new quizselectwindow(username);

                    // Back → dashboard
                    QObject::connect(qsWin,
                        &quizselectwindow::backRequested,
                        [dashWin, qsWin]() {
                            qsWin->close();
                            qsWin->deleteLater();
                            dashWin->show();
                        });

                    // Quiz chosen → start quiz directly
                    QObject::connect(qsWin,
                        &quizselectwindow::quizSelected,
                        [dashWin, qsWin, username]
                        (int courseId,
                         const QString& courseTitle) {
                            openQuizWindow(dashWin, qsWin,
                                           courseId,
                                           courseTitle,
                                           username);
                        });

                    dashWin->hide();
                    qsWin->show();
                });

            // ── PROGRESS button ───────────────────────────────
            QObject::connect(dashWin,
                &dashboard::openProgressRequested,
                [dashWin, username]() {
                    progresswindow* pw =
                        new progresswindow(username);
                    QObject::connect(pw,
                        &progresswindow::backRequested,
                        [dashWin, pw]() {
                            pw->close();
                            pw->deleteLater();
                            dashWin->loadUserStats();
                            dashWin->show();
                        });
                    dashWin->hide();
                    pw->show();
                });

            // ── BADGES button ─────────────────────────────────
            QObject::connect(dashWin,
                &dashboard::openBadgesRequested,
                [dashWin, username]() {
                    badgeswindow* bw =
                        new badgeswindow(username);
                    QObject::connect(bw,
                        &badgeswindow::backRequested,
                        [dashWin, bw]() {
                            bw->close();
                            bw->deleteLater();
                            dashWin->loadUserStats();
                            dashWin->show();
                        });
                    dashWin->hide();
                    bw->show();
                });

            // ── PROFILE button ────────────────────────────────
            QObject::connect(dashWin,
                &dashboard::openProfileRequested,
                [dashWin, username]() {
                    profilewindow* pw =
                        new profilewindow(username);
                    QObject::connect(pw,
                        &profilewindow::backRequested,
                        [dashWin, pw]() {
                            pw->close();
                            pw->deleteLater();
                            dashWin->loadUserStats();
                            dashWin->show();
                        });
                    QObject::connect(pw,
                        &profilewindow::profileUpdated,
                        [dashWin](const QString&) {
                            dashWin->loadUserStats();
                        });
                    dashWin->hide();
                    pw->show();
                });

            loginWin->hide();
            dashWin->show();
        });

    return app.exec();
}
