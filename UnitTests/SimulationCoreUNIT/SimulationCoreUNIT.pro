#-------------------------------------------------
#
# Project created by QtCreator 2014-06-02T23:05:07
#
#-------------------------------------------------

QT       += widgets opengl testlib

TARGET = tst_simulationcoreunittest
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app

SOURCES += tst_simulationcoreunittest.cpp
DEFINES += SRCDIR=\\\"$$PWD/\\\"

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../../SimulationCore/release/ -lSimulationCore
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../../SimulationCore/debug/ -lSimulationCore
else:unix: LIBS += -L$$OUT_PWD/../../SimulationCore/ -lSimulationCore

INCLUDEPATH += $$PWD/../../SimulationCore
DEPENDPATH += $$PWD/../../SimulationCore

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../../GlobalCore/release/ -lGlobalCore
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../../GlobalCore/debug/ -lGlobalCore
else:unix: LIBS += -L$$OUT_PWD/../../GlobalCore/ -lGlobalCore

INCLUDEPATH += $$PWD/../../GlobalCore
DEPENDPATH += $$PWD/../../GlobalCore


win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../../ErrorCore/release/ -lErrorCore
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../../ErrorCore/debug/ -lErrorCore
else:unix: LIBS += -L$$OUT_PWD/../ErrorCore/ -lErrorCore

INCLUDEPATH += $$PWD/../../ErrorCore
DEPENDPATH += $$PWD/../../ErrorCore

CONFIG += c++11

unix: QMAKE_CXXFLAGS += -std=gnu++11
