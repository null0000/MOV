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
    coCameraManager.cpp \
    coWorld.cpp \
    coDebugHandler.cpp


CONFIG += c++11

HEADERS += \
    CompositionCore.h \
    compositioncore_ie.h \
    coAiSpawner.h \
    coCameraManager.h \
    coWorld.h \
    coDebugHandler.h \
    coWorldFullTag.h \
    coChunkRenderer.h \
    coTagLocFunctor.h

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

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../GlobalCore/release/ -lGlobalCore
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../GlobalCore/debug/ -lGlobalCore
else:unix: LIBS += -L$$OUT_PWD/../GlobalCore/ -lGlobalCore

INCLUDEPATH += $$PWD/../GlobalCore
DEPENDPATH += $$PWD/../GlobalCore
