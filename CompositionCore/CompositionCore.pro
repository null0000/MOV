#-------------------------------------------------
#
# Project created by QtCreator 2014-03-22T21:39:19
#
#-------------------------------------------------

QT       += opengl

TARGET = CompositionCore
TEMPLATE = lib

DEFINES += COMPOSITIONCORE_LIBRARY

SOURCES += compositioncore.cpp

HEADERS += \
    CompositionCore.h

unix:!symbian {
    maemo5 {
        target.path = /opt/usr/lib
    } else {
        target.path = /usr/lib
    }
    INSTALLS += target
}

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../SimulationCore/release/ -lSimulationCore
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../SimulationCore/debug/ -lSimulationCore
else:unix: LIBS += -L$$OUT_PWD/../SimulationCore/ -lSimulationCore

INCLUDEPATH += $$PWD/../SimulationCore
DEPENDPATH += $$PWD/../SimulationCore

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../GraphicsCore/release/ -lGraphicsCore
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../GraphicsCore/debug/ -lGraphicsCore
else:unix: LIBS += -L$$OUT_PWD/../GraphicsCore/ -lGraphicsCore

INCLUDEPATH += $$PWD/../GraphicsCore
DEPENDPATH += $$PWD/../GraphicsCore
