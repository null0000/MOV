

#include "glbDebug.h"
#include "glbTranslate.h"
#include <iostream>
#include <QString>
#include <QVector2D>
#include <string>

void dumpVec(const QVector2D &vec) {std::cerr << vec2str(vec) << std::endl;}
void dumpStr(const QString &str){std::cerr << str.toStdString() << std::endl;}
void dumpStdStr(const std::string &str){std::cerr << str << std::endl;}
