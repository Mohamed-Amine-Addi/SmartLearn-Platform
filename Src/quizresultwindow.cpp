#include "quizresultwindow.h"
#include "ui_quizresultwindow.h"

quizresultwindow::quizresultwindow(const QuizResult& result,
                                   QWidget* parent)
    : QWidget(parent)
    , ui(new Ui::quizresultwindow)
    , m_result(result)
{
    ui->setupUi(this);
    setWindowTitle("Langora — Results");

    int wrong = result.total - result.correct;

    // Set score with color based on performance
    ui->label_score->setText(QString::number(result.score) + "%");
    if (result.score >= 80) {
        ui->label_score->setStyleSheet(
            "QLabel { color:#22c55e; font-size:42px; "
            "font-weight:bold; background:transparent; }");
        ui->label_icon->setText("✓");
        ui->label_icon->setStyleSheet(
            "QLabel { color:#22c55e; font-size:52px; background:transparent; }");
    } else if (result.score >= 50) {
        ui->label_score->setStyleSheet(
            "QLabel { color:#f59e0b; font-size:42px; "
            "font-weight:bold; background:transparent; }");
        ui->label_icon->setText("~");
        ui->label_icon->setStyleSheet(
            "QLabel { color:#f59e0b; font-size:52px; background:transparent; }");
    } else {
        ui->label_score->setStyleSheet(
            "QLabel { color:#ef4444; font-size:42px; "
            "font-weight:bold; background:transparent; }");
        ui->label_icon->setText("✗");
        ui->label_icon->setStyleSheet("QLabel { color:#ef4444; font-size:52px; background:transparent; }");
    }

    ui->label_course->setText(result.courseTitle);
    ui->label_correct_val->setText(QString::number(result.correct));
    ui->label_wrong_val->setText(QString::number(wrong));
    ui->label_xp_val->setText("+" + QString::number(result.xpEarned) + " XP");

    QString msg = result.score >= 80 ? "Excellent work! XP added to your account." : result.score >= 50 ? "Good effort! Keep practicing to improve." : "Keep studying and try again — you can do it!";
    ui->label_message->setText(msg);
}

quizresultwindow::~quizresultwindow() {
    delete ui;
}

void quizresultwindow::on_pushButton_dashboard_clicked() {
    emit backToDashboard();
}

void quizresultwindow::on_pushButton_retry_clicked() {
    emit retryQuiz();
}
