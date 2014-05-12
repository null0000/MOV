#include "GlobalCore.h"
#include <QDir>
#include <ErrorCore.h>
#include <ecIOErrors.h>
#include <QCoreApplication>

#include <QDebug>

#include <QTextStream>


QObject *glbGlobals::topObjectVar = NULL;
const QString glbGlobals::PROGRAM_NAME = "MOV";
QString glbGlobals::APP_DIR = "";
const QString glbGlobals::PYTHON_DIR = "PythonCore";
const QString glbGlobals::GRAPHICS_DIR = "Graphics";
QStack<QString> glbGlobals::dirStack;



bool glbGlobals::tryCD(QString cdTarget){

    bool success = false;
    try {
        success = QDir::setCurrent(cdTarget);
    } catch (...) {
        success = false;
    }

    if (!success) {
        ecErrorRegister::showError(new ecCdError(cdTarget));
        return false;
    }

    return success;
}



void glbGlobals::PushDir() {
    dirStack.push(QDir::currentPath());
}

void glbGlobals::RevertDir() {
    QString newDir = dirStack.pop();
    CD(newDir);
}


void glbGlobals::CD(QString target) {
    tryCD(target);
}



void glbGlobals::LogAppDir() {
    Q_ASSERT(APP_DIR == ""); //don't want to log it multiple times
    APP_DIR = QDir::currentPath() + "/..";
    CD(APP_DIR);
}

QString glbGlobals::GraphicsDir() {return GRAPHICS_DIR;}
QString glbGlobals::PythonDir() {return PYTHON_DIR;}
QString glbGlobals::AppDir() {return APP_DIR;}
QString glbGlobals::ProgramDir(){return APP_DIR;}


void glbGlobals::Bootup() {
    LogAppDir();
}

void glbGlobals::UnitBootup() {
    QDir::setCurrent("..");
    Bootup();
}
