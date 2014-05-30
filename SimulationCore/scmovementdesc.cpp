#include "scMovementDesc.h"

scMovementDesc::scMovementDesc(const QVector2D &movement, float maxMag) :
    maxMagnitude(maxMag), dir(movement) {Q_ASSERT(movement.length() == 1);}

void scMovementDesc::applyScale(float scaleDelta) {
    float finalDelta = std::min(scaleDelta, maxMagnitude);
    dir *= finalDelta;
    maxMagnitude /= finalDelta;
}

QVector2D scMovementDesc::maxMovement() const {
    return dir * maxMagnitude;
}
