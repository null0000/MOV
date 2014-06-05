#ifndef SCOBJDESC_H
#define SCOBJDESC_H

#include <QVector2D>
#include "simulationcore_ie.h"

class SIM_IE scObjDesc {

public:
    const QVector2D &location() const;

    void moveInDir(const QVector2D &Dir, float magnitude);
    void moveTowardPoint(const QVector2D &Point, float maxDist);
    void moveAmount(const QVector2D &movementAmount);

    scObjDesc(const QVector2D &StartPos, const QVector2D &SpeedScale);
    scObjDesc();
private:
    QVector2D thisLocation;
    QVector2D speedScale;
};

#endif // SCOBJDESC_H
