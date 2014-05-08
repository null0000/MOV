#include "scAIObject.h"
#include "scInstr.h"
#include "scTask.h"
#include "scObject.h"



void scAIObject::Simulate(delta_t timeDelta) {
    updatePos(getMovement(timeDelta));
}

scInstrPair scAIObject::updateTask(QVector2D totalMovement) const {
    scInstrDesc newInstr = fetchCurInstr.registerMovement(totalMovement);
    if (newInstr.nullInstr())
        return scInstrPair()
}


QVector2D scAIObject::getMovement(delta_t time) const {
    QVector2D maxSpeed = (time * speedScale);
    QVector2D desiredMovement = fetchCurInstr().movement();
    return QVector2D(qMax(maxSpeed.x(), desiredMovement.x()),
                     qMax(maxSpeed.y(), desiredMovement.y()));
}

QVector2D scAIObject::updatePos(QVector2D movement) const {
    return movement + curLoc;
}

const scInstrDesc &scAIObject::fetchCurInstr() const {
    return instrPair.second;
}
