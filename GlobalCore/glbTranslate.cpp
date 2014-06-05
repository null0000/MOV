

#include <QVector2D>
#include <sstream>
#include "glbTranslate.h"

std::string vec2str(const QVector2D &vector) {

    std::stringstream vecString;
    vecString << "Target Location: " << "(" << vector.x() << "," << vector.y() << ")";

    return vecString.str();
}
