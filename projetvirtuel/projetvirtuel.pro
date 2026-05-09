QT += core gui widgets sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

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
    profilewindow.cpp \
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
    profilewindow.h \
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
    profilewindow.ui \
    progresswindow.ui \
    quizresultwindow.ui \
    quizselectwindow.ui \
    quizwindow.ui \
    registerwindow.ui

RESOURCES += \
    resources.qrc

qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
