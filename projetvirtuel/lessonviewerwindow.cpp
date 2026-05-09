#include "lessonviewerwindow.h"
#include "ui_lessonviewerwindow.h"
#include "databasemanager.h"
#include <QScrollArea>
#include <QScrollBar>

lessonviewerwindow::lessonviewerwindow(int courseId,
                                       const QString& courseTitle,
                                       const QString& username,
                                       QWidget* parent)
    : QWidget(parent)
    , ui(new Ui::lessonviewerwindow)
    , m_courseId(courseId)
    , m_courseTitle(courseTitle)
    , m_username(username)
{
    ui->setupUi(this);
    setWindowTitle("Langora — " + courseTitle);
    setMinimumSize(900, 680);
    ui->label_course_name->setText(courseTitle);

    databasemanager::instance()
        .markCourseStarted(username, courseId);

    m_lessons = databasemanager::instance()
                    .getLessonsForCourse(courseId);

    if (m_lessons.isEmpty()) {
        ui->label_lesson_title->setText("No lessons available yet");
        ui->label_content->setText(
            "Lesson content is being prepared.\n"
            "Please check back soon!");
        ui->pushButton_next->setEnabled(false);
        ui->pushButton_prev->setEnabled(false);
        return;
    }
    showLesson(0);
}

lessonviewerwindow::~lessonviewerwindow() { delete ui; }

void lessonviewerwindow::showLesson(int index) {
    if (index < 0 || index >= m_lessons.size()) return;
    m_currentIndex = index;
    const auto& lesson = m_lessons[index];
    ui->label_lesson_title->setText(lesson.title);
    ui->label_content->setText(lesson.content);
    ui->label_progress->setText(
        QString("Lesson %1 / %2")
            .arg(index + 1).arg(m_lessons.size()));
    ui->prog_fill->setFixedWidth(
        (900 * (index + 1)) / m_lessons.size());
    // Scroll to top safely
    if (ui->scrollArea && ui->scrollArea->verticalScrollBar())
        ui->scrollArea->verticalScrollBar()->setValue(0);
    updateButtons();
}

void lessonviewerwindow::updateButtons() {
    ui->pushButton_prev->setEnabled(m_currentIndex > 0);
    bool isLast = (m_currentIndex == m_lessons.size() - 1);
    if (isLast) {
        ui->pushButton_next->setText("Finish Course →");
        ui->pushButton_next->setStyleSheet(R"(
            QPushButton{background:#22c55e;color:white;
            border:none;border-radius:10px;
            font-size:14px;font-weight:bold;}
            QPushButton:hover{background:#16a34a;})");
    } else {
        ui->pushButton_next->setText("Next →");
        ui->pushButton_next->setStyleSheet(R"(
            QPushButton{background:#1d4ed8;color:#eff6ff;
            border:none;border-radius:10px;
            font-size:14px;font-weight:bold;}
            QPushButton:hover{background:#2563eb;})");
    }
}

void lessonviewerwindow::on_pushButton_next_clicked() {
    if (m_currentIndex == m_lessons.size() - 1) {
        // Mark completed and go back to dashboard
        databasemanager::instance()
            .markCourseCompleted(m_username, m_courseId);
        emit allLessonsComplete(m_courseId, m_courseTitle);
    } else {
        showLesson(m_currentIndex + 1);
    }
}

void lessonviewerwindow::on_pushButton_prev_clicked() {
    showLesson(m_currentIndex - 1);
}

void lessonviewerwindow::on_pushButton_back_clicked() {
    emit backRequested();
}
