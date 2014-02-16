#-------------------------------------------------
#
# Project created by QtCreator 2014-02-15T18:07:57
#
#-------------------------------------------------

QT       += testlib

QT       -= gui

TARGET = tst_commcoreunittest
CONFIG   += console
CONFIG   += ordered
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += tst_commcoreunittest.cpp
DEFINES += SRCDIR=\\\"$$PWD/\\\"

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../../CommCore/release/ -lCommCore
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../../CommCore/debug/ -lCommCore
else:unix: LIBS += -L$$OUT_PWD/../../CommCore/ -lCommCore

INCLUDEPATH += $$PWD/../../CommCore
DEPENDPATH += $$PWD/../../CommCore

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../../GlobalCore/release/ -lGlobalCore
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../../GlobalCore/debug/ -lGlobalCore
else:unix: LIBS += -L$$OUT_PWD/../../GlobalCore/ -lGlobalCore

INCLUDEPATH += $$PWD/../../GlobalCore
DEPENDPATH += $$PWD/../../GlobalCore

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../../ErrorCore/release/ -lErrorCore
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../../ErrorCore/debug/ -lErrorCore
else:unix: LIBS += -L$$OUT_PWD/../../ErrorCore/ -lErrorCore

INCLUDEPATH += $$PWD/../../ErrorCore
DEPENDPATH += $$PWD/../../ErrorCore
