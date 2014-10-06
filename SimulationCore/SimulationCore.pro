#-------------------------------------------------
#
# Project created by QtCreator 2014-02-09T23:09:27
#
#-------------------------------------------------

QT       += gui

TARGET = SimulationCore
TEMPLATE = lib

DEFINES += SIMULATIONCORE_LIBRARY


CONFIG += c++11

unix: QMAKE_CXXFLAGS += -std=gnu++11

SOURCES += \
    scWorld.cpp \
    sckeyboardcontrolledobj.cpp \
    scKeyboardInput.cpp \
    scTask.cpp \
    scMovementDesc.cpp \
    scObjDesc.cpp \
    scTaskIterator.cpp \
    scTaskList.cpp \
    scListPlan.cpp \
    scSingleTask.cpp \
    scLocationFunctor.cpp \
    scTagMsgCallback.cpp

HEADERS += simulationcore.h \
    scKeyboardInput.h \
    sckeyboardcontrolledobj.h \
    scObject.h \
    scTask.h \
    scWorld.h \
    scObjDesc.h \
    scMovementDesc.h \
    scWorldDesc.h \
    scTaskIterator.h \
    simulationcore_ie.h \
    scTaskList.h \
    scListPlan.h \
    scSimulationStep.h \
    scSingleTask.h \
    scLocationFunctor.h \
    scTagMsgCallback.h \
    scFullTag.h

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

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../ErrorCore/release/ -lErrorCore
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../ErrorCore/debug/ -lErrorCore
else:unix: LIBS += -L$$OUT_PWD/../ErrorCore/ -lErrorCore

INCLUDEPATH += $$PWD/../ErrorCore
DEPENDPATH += $$PWD/../ErrorCore
