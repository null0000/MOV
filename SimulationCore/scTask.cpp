


#include "scTask.h"
#include "scObjDesc.h"
#include "scMovementDesc.h"


scTask scTask::NullTaskS = scTask();


bool scTask::isNullTask() const {return this == &NullTaskS;}

scMovementDesc scTask::getMovement(const scObjDesc &curLoc) const {
    QVector2D remainingMovement = (curLoc.location() - targetLoc);
    return scMovementDesc(remainingMovement.normalized(), remainingMovement.length());
}


void scTask::updateStrategy(const scObjDesc &, const scWorldDesc &) {

}

scTask::scTask() : shouldUse(false), targetLoc(0, 0){}

scTask::scTask(const scObjDesc &objDesc) :
    shouldUse(false), targetLoc(objDesc.location()){}
