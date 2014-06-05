
#include "commcore.h"
#include <GlobalCore.h>
#include <ecIOErrors.h>
#include <string>
#include <QDir>
#include <iostream>

const QString ccPythonComm::SCRIPT_NAME = "pcServerMain.py";
const QString ccPythonComm::PYTHON_NAME = "python";


ccPythonComm::ccPythonComm() :
    server(), ioStream(&server), successfullyStarted(false) {
    startupServer(SCRIPT_NAME);
}

ccPythonComm::ccPythonComm(const QString name) :
    server(), ioStream(&server), successfullyStarted(false) {
    startupServer(name);
}


void ccPythonComm::ProcessError(QProcess::ProcessError) {
    ecErrorRegister::showError(new ecProcessError(server.errorString()));
}


void ccPythonComm::startupServer(const QString ScriptName) {
    glbGlobals::PushDir();
    glbGlobals::MoveToPythonDir();

    QStringList dirs = QDir::current().entryList();

    Q_ASSERT(dirs.contains(SCRIPT_NAME));

    bool errorConnection = QObject::connect(&server, SIGNAL(error(QProcess::ProcessError)), this, SLOT(ProcessError(QProcess::ProcessError)));
    Q_ASSERT(errorConnection);

    bool startupConnection = QObject::connect(&server, SIGNAL(started()), this, SLOT(Started()));
    Q_ASSERT(startupConnection);

    QStringList argList;
    argList << "-i"; //make sure python is interactive
    if (ScriptName.length() > 0)
        argList << ScriptName;
    server.start(PYTHON_NAME, argList);
    server.waitForStarted();
    glbGlobals::RevertDir();
}


void ccPythonComm::SendArbitraryCommand(QString input) {
    Q_ASSERT(server.isWritable());
    ioStream << input;
    ioStream.flush();
}

QString ccPythonComm::ReadLine() {
    Q_ASSERT(server.isReadable());
    bool canRead = server.waitForReadyRead(1000);
    Q_ASSERT(canRead);
    QString output = ioStream.readLine();
    return output;
}
