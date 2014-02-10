#-------------------------------------------------
#
# Project created by QtCreator 2014-02-09T23:14:08
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = MOVMain
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    gamelogic.cpp

HEADERS  += mainwindow.h \
    gamelogic.h

FORMS    += mainwindow.ui

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../GraphicsCore/release/ -lGraphicsCore
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../GraphicsCore/debug/ -lGraphicsCore
else:unix: LIBS += -L$$OUT_PWD/../GraphicsCore/ -lGraphicsCore

INCLUDEPATH += $$PWD/../GraphicsCore
DEPENDPATH += $$PWD/../GraphicsCore

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../ErrorCore/release/ -lErrorCore
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../ErrorCore/debug/ -lErrorCore
else:unix: LIBS += -L$$OUT_PWD/../ErrorCore/ -lErrorCore

INCLUDEPATH += $$PWD/../ErrorCore
DEPENDPATH += $$PWD/../ErrorCore

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../SimulationCore/release/ -lSimulationCore
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../SimulationCore/debug/ -lSimulationCore
else:unix: LIBS += -L$$OUT_PWD/../SimulationCore/ -lSimulationCore

INCLUDEPATH += $$PWD/../SimulationCore
DEPENDPATH += $$PWD/../SimulationCore
