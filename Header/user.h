#ifndef USER_H
#define USER_H
#include <QString>
class user{
public:
    int id=0;
    QString name;
    QString password;
    int xp=0;
    int level=1;
    bool isValid() const {
        return id>0;
    }
};

#endif
