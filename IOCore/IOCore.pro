#-------------------------------------------------
#
# Project created by QtCreator 2014-02-16T00:04:51
#
#-------------------------------------------------

QT       -= gui

TARGET = IOCore
TEMPLATE = lib

DEFINES += IOCORE_LIBRARY

SOURCES +=

HEADERS += \
    IOCore.h

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
