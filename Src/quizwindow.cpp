#include "quizwindow.h"
#include "ui_quizwindow.h"
#include "databasemanager.h"
#include <QButtonGroup>
#include <QMessageBox>

quizwindow::quizwindow(int courseId, const QString& courseTitle, const QString& username, QWidget* parent)
    : QWidget(parent)
    , ui(new Ui::quizwindow)
    , m_courseId(courseId)
    , m_username(username)
    , m_courseTitle(courseTitle)
{
    ui->setupUi(this);
    setWindowTitle("Langora — Quiz");
    setMinimumSize(860, 620);

    ui->label_course_title->setText(courseTitle + " — Quiz");

    // Group radio buttons so only one can be selected at a time
    m_optionGroup = new QButtonGroup(this);
    m_optionGroup->addButton(ui->radio_0, 0);
    m_optionGroup->addButton(ui->radio_1, 1);
    m_optionGroup->addButton(ui->radio_2, 2);
    m_optionGroup->addButton(ui->radio_3, 3);
    m_optionGroup->setExclusive(true);

    // Load questions from database
    m_questions = databasemanager::instance()
                      .getQuestionsForCourse(courseId);

    if (m_questions.isEmpty()) {
        QMessageBox::information(this, "No Questions",
                                 "No questions available for this course yet.\n"
                                 "Check back soon!");
        emit backRequested();
        return;
    }

    // Hide feedback and fill-blank input initially
    ui->feedback_box->hide();
    ui->lineEdit_answer->hide();

    showQuestion(0);
}

quizwindow::~quizwindow() {
    delete ui;
}

void quizwindow::showQuestion(int index) {
    if (index >= m_questions.size()) { finishQuiz(); return; }

    const Question& q = m_questions[index];
    m_waitingForNext = false;

    ui->label_question_num->setText(
        QString("QUESTION %1").arg(index + 1));
    ui->label_progress->setText(
        QString("Question %1 / %2")
            .arg(index + 1).arg(m_questions.size()));
    ui->label_question_text->setText(q.text);

    // Update progress bar
    int barWidth = (860 * (index + 1)) / m_questions.size();
    ui->progress_fill->setFixedWidth(barWidth);

    ui->feedback_box->hide();
    ui->pushButton_submit->setText("Submit Answer");

    QList<QRadioButton*> radios = {
        ui->radio_0, ui->radio_1,
        ui->radio_2, ui->radio_3
    };

    // Reset all radio buttons
    m_optionGroup->setExclusive(false);
    for (auto* r : radios) {
        r->setChecked(false);
        r->setEnabled(true);
        r->setStyleSheet(R"(
            QRadioButton {
                color: #cbd5e1; font-size: 14px;
                background: #070b14;
                border: 1px solid #0f1629;
                border-radius: 10px; padding: 0 16px;
            }
            QRadioButton:hover {
                border-color: #1d4ed8; background: #080d18;
            }
            QRadioButton:checked {
                border-color: #1d4ed8; background: #0a1428;
                color: #60a5fa; font-weight: bold;
            }
            QRadioButton::indicator { width: 16px; height: 16px; }
        )");
    }
    m_optionGroup->setExclusive(true);

    if (q.type == QuestionType::FillBlank) {
        // Show only text input
        for (auto* r : radios) r->hide();
        ui->lineEdit_answer->show();
        ui->lineEdit_answer->clear();
        ui->lineEdit_answer->setEnabled(true);

    } else if (q.type == QuestionType::TrueFalse) {
        // Show only True and False
        ui->lineEdit_answer->hide();
        radios[0]->setText("True");
        radios[0]->show();
        radios[1]->setText("False");
        radios[1]->show();
        radios[2]->hide();
        radios[3]->hide();

    } else {
        // Multiple choice — show all options that have text
        ui->lineEdit_answer->hide();
        for (int i = 0; i < 4; i++) {
            if (i < q.options.size() && !q.options[i].isEmpty()) {
                radios[i]->setText(q.options[i]);
                radios[i]->show();
            } else {
                radios[i]->hide();
            }
        }
    }
}

void quizwindow::on_pushButton_submit_clicked() {
    // If waiting for next — advance to next question
    if (m_waitingForNext) {
        m_currentIndex++;
        showQuestion(m_currentIndex);
        return;
    }

    const Question& q = m_questions[m_currentIndex];
    AnswerRecord rec;
    rec.questionId = q.id;

    bool correct = false;

    if (q.type == QuestionType::FillBlank) {
        rec.givenText = ui->lineEdit_answer->text().trimmed();
        correct = rec.givenText.toLower() ==
                  q.correctAnswer.toLower();
        rec.correct = correct;
        ui->lineEdit_answer->setEnabled(false);
    } else {
        int chosen = m_optionGroup->checkedId();
        if (chosen == -1) {
            QMessageBox::warning(this, "No Answer", "Please select an answer before submitting.");
            return;
        }
        rec.givenIndex = chosen;
        correct        = (chosen == q.correctIndex);
        rec.correct    = correct;

        // Color the options green/red
        QList<QRadioButton*> radios = {
            ui->radio_0, ui->radio_1,
            ui->radio_2, ui->radio_3
        };
        for (int i = 0; i < radios.size(); i++) {
            if (!radios[i]->isVisible()) continue;
            radios[i]->setEnabled(false);
            if (i == q.correctIndex) {
                // Correct answer : green
                radios[i]->setStyleSheet(R"(
                    QRadioButton {
                        color: #22c55e; font-size: 14px; font-weight: bold;
                        background: #052010;
                        border: 2px solid #22c55e;
                        border-radius: 10px; padding: 0 16px;
                    }
                    QRadioButton::indicator { width: 16px; height: 16px; }
                )");
            } else if (i == chosen && !correct) {
                // Wrong choice — red
                radios[i]->setStyleSheet(R"(
                    QRadioButton {
                        color: #ef4444; font-size: 14px;
                        background: #1a0505;
                        border: 2px solid #ef4444;
                        border-radius: 10px; padding: 0 16px;
                    }
                    QRadioButton::indicator { width: 16px; height: 16px; }
                )");
            }
        }
    }

    m_answers.append(rec);
    showFeedback(correct, q.explanation);
}

void quizwindow::showFeedback(bool correct, const QString& explanation) {
    QString prefix = correct ? "✓  Correct!  " : "✗  Wrong!  ";
    ui->label_feedback->setText(prefix + explanation);
    ui->feedback_box->setStyleSheet(correct ? "QFrame { background:#052010; border:2px solid #22c55e; border-radius:10px; }" : "QFrame { background:#1a0505; border:2px solid #ef4444; border-radius:10px; }");
    ui->label_feedback->setStyleSheet(correct ? "QLabel { color:#22c55e; font-size:13px; background:transparent; }" : "QLabel { color:#ef4444; font-size:13px; background:transparent; }");
    ui->feedback_box->show();

    bool isLast = (m_currentIndex == m_questions.size() - 1);
    ui->pushButton_submit->setText(isLast ? "See Results" : "Next Question →");
    m_waitingForNext = true;
}

void quizwindow::finishQuiz() {
    int correct = 0;
    int totalXp = 0;
    for (const AnswerRecord& a : m_answers) {
        if (a.correct) {
            correct++;
            totalXp += 10;
        }
    }

    int total = m_questions.size();
    int score = total > 0 ? (correct * 100 / total) : 0;

    QuizResult result;
    result.courseId    = m_courseId;
    result.courseTitle = m_courseTitle;
    result.score       = score;
    result.xpEarned    = totalXp;
    result.correct     = correct;
    result.total       = total;
    result.answers     = m_answers;

    qDebug() << "Quiz finished: score=" << score << "xp=" << totalXp << "user=" << m_username;

    //Save result to DB
    databasemanager::instance().saveQuizResult(m_username, result);

    // Award XP : this updates the users table
    databasemanager::instance().addXpToUser(
        m_username, totalXp);

    // Check badges
    databasemanager::instance().checkAndAwardBadges(
        m_username);

    emit quizFinished(result);
}

void quizwindow::on_pushButton_back_clicked() {
    if (!m_answers.isEmpty()) {
        auto btn = QMessageBox::question(this, "Exit Quiz", "Are you sure you want to exit?\n" "Your progress will be lost.", QMessageBox::Yes | QMessageBox::No);
        if (btn != QMessageBox::Yes) return;
    }
    emit backRequested();
}
