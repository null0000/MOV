#-------------------------------------------------
#
# Project created by QtCreator 2014-02-09T23:09:27
#
#-------------------------------------------------

QT       -= gui
QT       += opengl

TARGET = SimulationCore
TEMPLATE = lib

DEFINES += SIMULATIONCORE_LIBRARY

SOURCES += scPlayer.cpp \
    scLevel.cpp

HEADERS += simulationcore.h\
    scPlayer.h \
    scLevel.h

unix:!symbian {
    maemo5 {
        target.path = /opt/usr/lib
    } else {
        target.path = /usr/lib
    }
    INSTALLS += target
}
