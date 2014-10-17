#-------------------------------------------------
#
# Project created by QtCreator 2014-10-16T20:49:13
#
#-------------------------------------------------

QT       += testlib gui widgets


TARGET = tst_compositioncoreunittest
CONFIG += c++11
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += tst_compositioncoreunittest.cpp
DEFINES += SRCDIR=\\\"$$PWD/\\\"

HEADERS += \
    tst_CmpUtil.h \
    tst_UnitHeader.h

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../../GraphicsCore/release/ -lGraphicsCore
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../../GraphicsCore/debug/ -lGraphicsCore
else:unix: LIBS += -L$$OUT_PWD/../../GraphicsCore/ -lGraphicsCore

INCLUDEPATH += $$PWD/../../GraphicsCore
DEPENDPATH += $$PWD/../../GraphicsCore

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

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../../CompositionCore/release/ -lCompositionCore
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../../CompositionCore/debug/ -lCompositionCore
else:unix: LIBS += -L$$OUT_PWD/../../CompositionCore/ -lCompositionCore

INCLUDEPATH += $$PWD/../../CompositionCore
DEPENDPATH += $$PWD/../../CompositionCore

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../../ErrorCore/release/ -lErrorCore
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../../ErrorCore/debug/ -lErrorCore
else:unix: LIBS += -L$$OUT_PWD/../../ErrorCore/ -lErrorCore

INCLUDEPATH += $$PWD/../../ErrorCore
DEPENDPATH += $$PWD/../../ErrorCore

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../TestLibrary/release/ -lTestLibrary
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../TestLibrary/debug/ -lTestLibrary
else:unix: LIBS += -L$$OUT_PWD/../TestLibrary/ -lTestLibrary

INCLUDEPATH += $$PWD/../TestLibrary
DEPENDPATH += $$PWD/../TestLibrary
