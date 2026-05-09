#ifndef COURSEWINDOW_H
#define COURSEWINDOW_H


#include <QList>
#include <QWidget>
#include <QVBoxLayout>
#include <QScrollArea>
#include "course.h"

class QPushButton;
class QLabel;

namespace Ui {
class coursewindow;
}

class coursewindow : public QWidget
{
    Q_OBJECT

public:
    explicit coursewindow(const QString& username, QWidget* parent = nullptr);
    ~coursewindow();

signals:
    void backRequested();
    void courseStarted(int course_id, const QString& course_tilte);

private slots:
    void on_pushButton_back_clicked();
    void on_btn_filter_all_clicked();
    void on_btn_filter_cpp_clicked();
    void on_btn_filter_python_clicked();

private:
    void loadCourses(const QString& languageFilter = "");
    void buildCourseCard(const course& course, QVBoxLayout* layout);
    void setActiveFilter(const QString& filter);

    Ui::coursewindow *ui;
    QString m_username;
    QVBoxLayout* m_cardsLayout = nullptr;
};

#endif // COURSEWINDOW_H
