#-------------------------------------------------
#
# Project created by QtCreator 2014-02-09T23:09:27
#
#-------------------------------------------------

QT       += gui
QT       += opengl

TARGET = SimulationCore
TEMPLATE = lib

DEFINES += SIMULATIONCORE_LIBRARY

SOURCES += \
    scWorld.cpp

HEADERS += simulationcore.h \
    scKeyboardInput.h

unix:!symbian {
    maemo5 {
        target.path = /opt/usr/lib
    } else {
        target.path = /usr/lib
    }
    INSTALLS += target
}

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../GlobalCore/release/ -lGlobalCore
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../GlobalCore/debug/ -lGlobalCore
else:unix: LIBS += -L$$OUT_PWD/../GlobalCore/ -lGlobalCore

INCLUDEPATH += $$PWD/../GlobalCore
DEPENDPATH += $$PWD/../GlobalCore
