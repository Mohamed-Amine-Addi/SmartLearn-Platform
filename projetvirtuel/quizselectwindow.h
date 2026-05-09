#ifndef QUIZSELECTWINDOW_H
#define QUIZSELECTWINDOW_H

#include <QWidget>
#include <QVBoxLayout>
#include "course.h"

namespace Ui { class quizselectwindow; }

class quizselectwindow : public QWidget
{
    Q_OBJECT
public:
    explicit quizselectwindow(const QString& username,
                              QWidget* parent = nullptr);
    ~quizselectwindow();

signals:
    void backRequested();
    void quizSelected(int courseId,
                      const QString& courseTitle);

private slots:
    void on_pushButton_back_clicked();
    void on_btn_filter_all_clicked();
    void on_btn_filter_cpp_clicked();
    void on_btn_filter_python_clicked();

private:
    void loadCards(const QString& filter = "");
    void buildCard(const course& c, QVBoxLayout* layout);
    void setFilter(const QString& active);

    Ui::quizselectwindow* ui;
    QString       m_username;
    QVBoxLayout*  m_layout = nullptr;
};

#endif // QUIZSELECTWINDOW_H
