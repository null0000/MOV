#ifndef SCMOVEMENTDESC_H
#define SCMOVEMENTDESC_H

#include <QVector2D>

#include "simulationcore_ie.h"

class SIM_IE scMovementDesc
{
public:
    scMovementDesc(const QVector2D &dir, float maxMag);

    /*!
     * \brief addMaxDelta Adds max delta to this class
     * \param newMaxDelta the speed limit for this class
     * \return capped version of this object
     *
     *This is used to make sure that the movement description
     *doesn't go past a certain speed limit (newMaxDelta).
     */
    scMovementDesc addMaxDelta(float newMaxDelta) const;

    QVector2D maxMovement() const;
private:
    float maxMagnitude;
    QVector2D dir;
};

#endif // SCMOVEMENTDESC_H
