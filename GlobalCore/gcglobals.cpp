#include "GlobalCore.h"
#include <QDir>
#include <ErrorCore.h>
#include <ecIOErrors.h>
#include <QCoreApplication>

#include <QDebug>

#include <QTextStream>

const QString gcGlobals::PROGRAM_NAME = "MOV";
const QString gcGlobals::APP_DIR = "C:\\Users\\null\\MOV";
const QString gcGlobals::PYTHON_DIR = "PythonCore";
QStack<QString> gcGlobals::dirStack;

QString gcGlobals::ProgramDir()
{
    return APP_DIR;
}

bool gcGlobals::tryCD(QString cdTarget){
    try {
        QDir::setCurrent(cdTarget);
    } catch (...) {
        ecErrorRegister::showError(new ecCdError(cdTarget));
        return false;
    }
    return true;
}



void gcGlobals::PushDir() {
    dirStack.push(QDir::currentPath());
}

void gcGlobals::RevertDir() {
    QString newDir = dirStack.pop();
    CD(newDir);
}


void gcGlobals::CD(QString target) {
    bool success = tryCD(target);
    Q_ASSERT(success == true);
}
