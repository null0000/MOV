#-------------------------------------------------
#
# Project created by QtCreator 2014-03-22T21:39:19
#
#-------------------------------------------------

QT       += opengl

TARGET = CompositionCore
TEMPLATE = lib

unix: QMAKE_CXXFLAGS += -std=gnu++11
DEFINES += COMPOSITIONCORE_LIBRARY

SOURCES += compositioncore.cpp \
    coAiSpawner.cpp \
    coWorld.cpp


CONFIG += c++11

HEADERS += \
    CompositionCore.h \
    compositioncore_ie.h \
    coAiSpawner.h \
    coScene.h \
    coObject.h \
    coWorld.h \
    coWorld_tplt.h \
    coCameraStrategy.h \
    coDefaultCamera.h

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

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../ErrorCore/release/ -lErrorCore
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../ErrorCore/debug/ -lErrorCore
else:unix: LIBS += -L$$OUT_PWD/../ErrorCore/ -lErrorCore

INCLUDEPATH += $$PWD/../ErrorCore
DEPENDPATH += $$PWD/../ErrorCore
