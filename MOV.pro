TEMPLATE = subdirs

CONFIG += ordered

windows{
    LIBS +=  $$_PRO_FILE_PWD_/Box2D-build/Box2D -lBox2D
}

INCLUDEPATH += $$_PRO_FILE_PWD_/Box2D/Box2D


SUBDIRS += \
    ErrorCore \
    SimulationCore \
    GraphicsCore \
    MOVMain \
    UnitTests \
    CommCore \
    GlobalCore \
    IOCore

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/GlobalCore/release/ -lGlobalCore
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/GlobalCore/debug/ -lGlobalCore
else:unix: LIBS += -L$$OUT_PWD/GlobalCore/ -lGlobalCore

INCLUDEPATH += $$PWD/GlobalCore
DEPENDPATH += $$PWD/GlobalCore
