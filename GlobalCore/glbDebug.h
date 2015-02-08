#ifndef GLBDEBUG_H
#define GLBDEBUG_H

#ifndef QT_NO_DEBUG
class QVector2D;
class QString;


#include "globalcore_ie.h"
#include <string>

GLB_IE void dumpCurPath();
GLB_IE void dumpVec(const QVector2D &vec);
GLB_IE void dumpStr(const QString &str);
GLB_IE void dumpStdStr(const std::string &str);

#endif

#endif // GLBDEBUG_H
