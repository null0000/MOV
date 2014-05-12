#include "scAIObject.h"
#include "scInstr.h"
#include "scTask.h"
#include "scObject.h"



void scAIObject::Simulate(delta_t timeDelta) {
    QVector2D movementDelta = getMovement(timeDelta);
    curLoc = updatePos(movementDelta);
    instrPair = updateTask(movementDelta);
}

scInstrPair scAIObject::updateTask(QVector2D totalMovement) const {
    scInstrDesc newInstr = fetchCurInstr().registerMovement(totalMovement);
    if (newInstr.isNullInstr())
        return fetchCurTask()->nextInstr();
    return scInstrPair(fetchCurTask(), newInstr);
}


QVector2D scAIObject::getMovement(delta_t time) const {
    QVector2D maxSpeed (time * speedScale.x(), time * speedScale.y());
    QVector2D desiredMovement = fetchCurInstr().movementRemaining();
    return QVector2D(qMin(maxSpeed.x(), desiredMovement.x()),
                     qMin(maxSpeed.y(), desiredMovement.y()));
}

QVector2D scAIObject::updatePos(QVector2D movement) const {
    return movement + curLoc;
}

const scInstrDesc &scAIObject::fetchCurInstr() const {
    return instrPair.second;
}

const scTask *scAIObject::fetchCurTask() const {
    return instrPair.first;
}

QVector2D scAIObject::position() const {return curLoc;}


scAIObject::scAIObject(const scTask &task, QVector2D speedScale) :
    curLoc(0, 0), speedScale(speedScale), instrPair(task.nextInstr()){}
