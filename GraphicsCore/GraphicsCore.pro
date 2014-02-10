#-------------------------------------------------
#
# Project created by QtCreator 2014-02-09T23:12:08
#
#-------------------------------------------------

QT       -= gui
QT       += opengl
TARGET = GraphicsCore
TEMPLATE = lib

DEFINES += GRAPHICSCORE_LIBRARY

SOURCES += \
    gcImage.cpp \
    gcDrawingImpl.cpp

HEADERS += \
    GraphicsCore.h

unix:!symbian {
    maemo5 {
        target.path = /opt/usr/lib
    } else {
        target.path = /usr/lib
    }
    INSTALLS += target
}
