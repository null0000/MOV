#ifndef SCMOVEMENTDESC_H
#define SCMOVEMENTDESC_H

#include <QVector2D>

#include "simulationcore_ie.h"

class SIM_IE scMovementDesc
{
public:
    scMovementDesc(const QVector2D &dir, float maxMag);

    scMovementDesc addMaxDelta(float newMaxDelta) const;

    QVector2D maxMovement() const;
private:
    float maxMagnitude;
    QVector2D dir;
};

#endif // SCMOVEMENTDESC_H
