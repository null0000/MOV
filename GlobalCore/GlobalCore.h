#ifndef GLOBALCORE_H
#define GLOBALCORE_H

#include <QString>
#include <QStack>

class gcGlobals
{
    gcGlobals(){}

    static const QString APP_DIR;
    static const QString PYTHON_DIR;

    static bool tryCD(QString cdTarget);
    static QStack<QString> dirStack;

public:
    static const QString PROGRAM_NAME;
    static QString ProgramDir();
    static void MoveToProgramDir() {CD(ProgramDir());}
    static void MoveToPythonDir(){CD(ProgramDir()); CD(PYTHON_DIR);}

    static void PushDir();
    static void RevertDir();
    static void CD(QString target);
};

#endif // GLOBALCORE_H
