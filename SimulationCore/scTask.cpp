
#include <sstream>

#include <glbDebug.h>
#include <glbTranslate.h>
#include "scTask.h"
#include "scObjDesc.h"
#include "scMovementDesc.h"

bool scTask::isNullTask() const {return isNull;}


/**
 * @brief scTask::getMovement
 * @param curLoc
 * @return scMovementDesc
 *
 *returns the movement based on the remaining movement.
 */
scMovementDesc scTask::getMovement(const scObjDesc &curLoc) const {
    if (isNull)
        return scMovementDesc(QVector2D(0, 0), 0);
    QVector2D remainingMovement = (targetLoc - curLoc.location());
    return scMovementDesc(remainingMovement.normalized(), remainingMovement.length());
}




scTask::scTask() : shouldUse(false), isNull(true), targetLoc(0, 0){}

scTask::scTask(const scObjDesc &objDesc) :
    shouldUse(false), isNull(false), targetLoc(objDesc.location()) {}

std::string scTask::dump() const {
    if (isNull)
        return "--Null Task--";
    std::stringstream vecString;

    vecString << vec2str(targetLoc);
    if (shouldUse) {
        vecString << std::endl << "Should use";
    }

    return vecString.str();

}


scTask::scTask(const QVector2D &targetLoc) :
    shouldUse(false), isNull(false), targetLoc(targetLoc){}

bool scTask::isUsing() const{return shouldUse;}


bool scTask::needsUpdate(const scObjDesc &curLoc) const {
    return (curLoc.location() == targetLoc) || isNull;
}

scTask::scTask(const QVector2D &targetLoc, bool useTask) : shouldUse(useTask), isNull(false),
    targetLoc(targetLoc){}
