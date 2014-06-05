#ifndef COMMCORE_H
#define COMMCORE_H

#include <QProcess>
#include <ErrorCore.h>
#include <QTextStream>
#include "commcore_ie.h"

class COM_IE ccPythonComm : public QObject

{
    Q_OBJECT

    QProcess server;
    QTextStream ioStream;
    bool successfullyStarted;

    static const QString SCRIPT_NAME;
    static const QString PYTHON_NAME;

    void startupServer(const QString ScriptName);



public:
    ccPythonComm();
    ccPythonComm(const QString name);
    void Kill() {server.kill();}
    void Terminate() {server.closeWriteChannel(); server.terminate();}
    void SendArbitraryCommand(QString input);
    QString ReadLine();

private slots:
    void ProcessError(QProcess::ProcessError ErrorType);
    void Started() {successfullyStarted = true;}

};

#endif
