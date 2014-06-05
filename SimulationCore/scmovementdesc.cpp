#include "scMovementDesc.h"
static int hitCount = 0;
scMovementDesc::scMovementDesc(const QVector2D &movement, float maxMag) :
    maxMagnitude(maxMag), dir(movement) {
    hitCount++;
    float length = movement.length();
    Q_ASSERT(length <= 1);
}


QVector2D scMovementDesc::maxMovement() const {
    return dir * maxMagnitude;
}


scMovementDesc scMovementDesc::addMaxDelta(float newMaxDelta) const {
    float finalDelta = std::min(newMaxDelta, maxMagnitude);
    if (finalDelta == 0)
        return scMovementDesc(QVector2D(0, 0), 0);
    return scMovementDesc(dir, finalDelta);
}
