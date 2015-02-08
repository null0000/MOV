#-------------------------------------------------
#
# Project created by QtCreator 2014-10-16T21:01:29
#
#-------------------------------------------------

QT       += gui testlib

TARGET = TestLibrary
TEMPLATE = lib

DEFINES += TESTLIBRARY_LIBRARY

CONFIG += c++11

SOURCES += \
    tst_unitUtil.cpp \
    tstDrawRegistry.cpp

HEADERS +=\
    tst_unitUtil.h \
    tstDrawRegistry.h \
    tstNullRenderable.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}

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

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../../GraphicsCore/release/ -lGraphicsCore
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../../GraphicsCore/debug/ -lGraphicsCore
else:unix: LIBS += -L$$OUT_PWD/../../GraphicsCore/ -lGraphicsCore

INCLUDEPATH += $$PWD/../../GraphicsCore
DEPENDPATH += $$PWD/../../GraphicsCore

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../../ErrorCore/release/ -lErrorCore
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../../ErrorCore/debug/ -lErrorCore
else:unix: LIBS += -L$$OUT_PWD/../../ErrorCore/ -lErrorCore

INCLUDEPATH += $$PWD/../../ErrorCore
DEPENDPATH += $$PWD/../../ErrorCore
