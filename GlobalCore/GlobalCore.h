#ifndef GLOBALCORE_H
#define GLOBALCORE_H

#include <QString>
#include <QStack>
#include <QWidget>

#include "globalcore_ie.h"

#include "glbDebug.h" //make sure that everything can access deubg shit

class GLB_IE glbGlobals
{

    static QObject *topObjectVar;

    glbGlobals(){}

    static QString APP_DIR;
    static const QString PYTHON_DIR;
    static const QString GRAPHICS_DIR;
    static const QString PROGRAM_NAME;

    static bool tryCD(QString cdTarget);
    static QStack<QString> dirStack;
public:
    static void LogAppDir();
    static void LogAppDirForUnit();

    static QString ProgramDir();
    static QString GraphicsDir();
    static QString PythonDir();
    static QString AppDir();
    static void MoveToProgramDir() {CD(ProgramDir());}
    static void MoveToPythonDir(){CD(PythonDir());}
    static void MoveToGraphicsDir(){CD(GraphicsDir());}
    static void PushDir();
    static void RevertDir();
    static void CD(QString target);

    static void Bootup();
    static void UnitBootup();

};

#include <iostream>

class GLB_IE glbDebug {

public:
    static void DumpQString(const QString &dumpee) {std::cerr << dumpee.toStdString();}
};

#endif // GLOBALCORE_H
