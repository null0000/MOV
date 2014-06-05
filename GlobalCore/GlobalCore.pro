#-------------------------------------------------
#
# Project created by QtCreator 2014-02-15T18:14:33
#
#-------------------------------------------------

QT       -= gui

QT       += widgets

CONFIG += ordered

TARGET = GlobalCore
TEMPLATE = lib

DEFINES += GLOBALCORE_LIBRARY

SOURCES += gcglobals.cpp \
    glbTranslate.cpp \
    glbDebug.cpp

HEADERS += GlobalCore.h \
    glbTranslate.h \
    glbDebug.h \
    globalcore_ie.h

unix:!symbian {
    maemo5 {
        target.path = /opt/usr/lib
    } else {
        target.path = /usr/lib
    }
    INSTALLS += target
}

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../ErrorCore/release/ -lErrorCore
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../ErrorCore/debug/ -lErrorCore
else:unix: LIBS += -L$$OUT_PWD/../ErrorCore/ -lErrorCore

INCLUDEPATH += $$PWD/../ErrorCore
DEPENDPATH += $$PWD/../ErrorCore
