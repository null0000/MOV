#include "GlobalCore.h"
#include <QDir>
#include <ErrorCore.h>
#include <ecIOErrors.h>
#include <QCoreApplication>

#include <QDebug>

#include <QTextStream>


QObject *glbGlobals::topObjectVar = NULL;
const QString glbGlobals::PROGRAM_NAME = "MOV";
const QString glbGlobals::APP_DIR = "C:\\Users\\null\\MOV";
const QString glbGlobals::PYTHON_DIR = "PythonCore";
QStack<QString> glbGlobals::dirStack;

QString glbGlobals::ProgramDir()
{
    return APP_DIR;
}

bool glbGlobals::tryCD(QString cdTarget){
    try {
        QDir::setCurrent(cdTarget);
    } catch (...) {
        ecErrorRegister::showError(new ecCdError(cdTarget));
        return false;
    }
    return true;
}



void glbGlobals::PushDir() {
    dirStack.push(QDir::currentPath());
}

void glbGlobals::RevertDir() {
    QString newDir = dirStack.pop();
    CD(newDir);
}


void glbGlobals::CD(QString target) {
    bool success = tryCD(target);
    Q_ASSERT(success == true);
}

