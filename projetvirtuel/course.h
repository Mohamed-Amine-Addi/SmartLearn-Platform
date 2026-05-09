#ifndef COURSE_H
#define COURSE_H
#include <QString>
//Difficulty levels
enum class Difficulty{
    Beginner,
    Intermediate,
    Advanced
};

struct course{
    int id = 0;
    QString title;
    QString description;
    QString language;
    Difficulty difficulty = Difficulty::Beginner;
    int totallessons = 0;
    int xpreward = 0;


    QString difficultytext() const{
        switch(difficulty){
            case Difficulty::Beginner: return "Beginner";
            case Difficulty::Intermediate: return "Intermediate";
            case Difficulty::Advanced: return "Advanced";
        }
            return "Beginner";
    }
    QString difficultycolor() const{
        switch(difficulty){
        case Difficulty::Beginner: return "#22c55e";
        case Difficulty::Intermediate: return "#f59e0b";
        case Difficulty::Advanced: return "#ef4444";
        }
        return "#22c55e";
    }

};

#endif // COURSE_H
