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

unix: QMAKE_CXXFLAGS += -std=gnu++11

SOURCES += \
    gcImage.cpp \
    gcDrawingImpl.cpp

HEADERS += \
    GraphicsCore.h \
    gcImage.h \
    gcRenderTransform.h \
    gcRenderable.h \
    gcDrawingImpl.h \
    graphicscore_ie.h \
    gcRenderList.h

unix:!symbian {
    maemo5 {
        target.path = /opt/usr/lib
    } else {
        target.path = /usr/lib
    }
    INSTALLS += target
}

CONFIG += c++11

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../GlobalCore/release/ -lGlobalCore
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../GlobalCore/debug/ -lGlobalCore
else:unix: LIBS += -L$$OUT_PWD/../GlobalCore/ -lGlobalCore

INCLUDEPATH += $$PWD/../GlobalCore
DEPENDPATH += $$PWD/../GlobalCore

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../ErrorCore/release/ -lErrorCore
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../ErrorCore/debug/ -lErrorCore
else:unix: LIBS += -L$$OUT_PWD/../ErrorCore/ -lErrorCore

INCLUDEPATH += $$PWD/../ErrorCore
DEPENDPATH += $$PWD/../ErrorCore
