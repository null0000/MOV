#-------------------------------------------------
#
# Project created by QtCreator 2014-02-09T23:58:27
#
#-------------------------------------------------

QT       += testlib widgets gui


TARGET = tst_errorcoreunit
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += tst_errorcoreunit.cpp
DEFINES += SRCDIR=\\\"$$PWD/\\\"

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../../ErrorCore/release/ -lErrorCore
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../../ErrorCore/debug/ -lErrorCore
else:unix: LIBS += -L$$OUT_PWD/../../ErrorCore/ -lErrorCore

INCLUDEPATH += $$PWD/../../ErrorCore
DEPENDPATH += $$PWD/../../ErrorCore
