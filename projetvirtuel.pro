QT       += core gui widgets sql
    quick

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    badgeswindow.cpp \
    coursedetailwindow.cpp \
    coursewindow.cpp \
    dashboard.cpp \
    databasemanager.cpp \
    lessonviewerwindow.cpp \
    loginwindow.cpp \
    main.cpp \
    mainwindow.cpp \
    progresswindow.cpp \
    quizresultwindow.cpp \
    quizselectwindow.cpp \
    quizwindow.cpp \
    registerwindow.cpp

HEADERS += \
    badge.h \
    badgeswindow.h \
    course.h \
    coursedetailwindow.h \
    coursewindow.h \
    dashboard.h \
    databasemanager.h \
    lesson.h \
    lessonviewerwindow.h \
    loginwindow.h \
    mainwindow.h \
    progresswindow.h \
    question.h \
    quizhistoryentry.h \
    quizresult.h \
    quizresultwindow.h \
    quizselectwindow.h \
    quizwindow.h \
    registerwindow.h \
    user.h

FORMS += \
    badgeswindow.ui \
    coursedetailwindow.ui \
    coursewindow.ui \
    dashboard.ui \
    lessonviewerwindow.ui \
    loginwindow.ui \
    mainwindow.ui \
    progresswindow.ui \
    quizresultwindow.ui \
    quizselectwindow.ui \
    quizwindow.ui \
    registerwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES +=

RESOURCES +=
