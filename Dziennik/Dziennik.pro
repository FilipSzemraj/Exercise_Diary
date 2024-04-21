QT       += core gui
QT       += sql
QT       += charts


greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    adding_exercise.cpp \
    adding_new_exercise.cpp \
    adding_new_group.cpp \
    calendar.cpp \
    chart.cpp \
    chartsoption.cpp \
    login.cpp \
    main.cpp \
    mainwindow.cpp \
    ranking.cpp \
    registeruser.cpp

HEADERS += \
    adding_exercise.h \
    adding_new_exercise.h \
    adding_new_group.h \
    calendar.h \
    chart.h \
    chartsoption.h \
    login.h \
    mainwindow.h \
    ranking.h \
    registeruser.h

FORMS += \
    adding_exercise.ui \
    adding_new_exercise.ui \
    adding_new_group.ui \
    calendar.ui \
    chart.ui \
    chartsoption.ui \
    login.ui \
    mainwindow.ui \
    ranking.ui \
    registeruser.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resources.qrc
