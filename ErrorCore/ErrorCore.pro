#-------------------------------------------------
#
# Project created by QtCreator 2014-02-09T23:07:33
#
#-------------------------------------------------

QT       += gui designer widgets

CONFIG += ordered

TARGET = ErrorCore
TEMPLATE = lib

DEFINES += ERRORCORE_LIBRARY

SOURCES += \
    ecErrorRegister.cpp \
    ecErrorDialog.cpp

HEADERS += \
    ErrorCore.h \
    ecErrorDialog.h \
    dialogKiller.h \
    ecIOErrors.h

unix:!symbian {
    maemo5 {
        target.path = /opt/usr/lib
    } else {
        target.path = /usr/lib
    }
    INSTALLS += target
}

FORMS += \
    errordialog.ui

INCLUDEPATH += $$PWD/../GlobalCore
DEPENDPATH += $$PWD/../GlobalCore
