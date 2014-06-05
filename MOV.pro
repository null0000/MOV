TEMPLATE = subdirs

CONFIG += ordered

windows{
    LIBS +=  $$_PRO_FILE_PWD_/Box2D-build/Box2D -lBox2D
}

INCLUDEPATH += $$_PRO_FILE_PWD_/Box2D/Box2D
CONFIG += c++11


QMAKE_CXXFLAGS_DEBUG += -g3

unix: QMAKE_CXXFLAGS += -std=gnu++11
graphics.path = $$OUT_PWD/Graphics
graphics.files = $$_PRO_FILE_PWD_/Graphics/*
INSTALLS += graphics

python.path = $$OUT_PWD
python.files = $$_PRO_FILE_PWD_/PythonCore
INSTALLS += python

SUBDIRS += \
    ErrorCore \
    GlobalCore \
    SimulationCore \
    GraphicsCore \
    CompositionCore \
    CommCore \
    MOVMain \
    UnitTests

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/GlobalCore/release/ -lGlobalCore
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/GlobalCore/debug/ -lGlobalCore
else:unix: LIBS += -L$$OUT_PWD/GlobalCore/ -lGlobalCore

INCLUDEPATH += $$PWD/GlobalCore
DEPENDPATH += $$PWD/GlobalCore

