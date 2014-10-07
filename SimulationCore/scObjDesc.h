#ifndef SCOBJDESC_H
#define SCOBJDESC_H

#include <QVector2D>
#include "simulationcore_ie.h"

class scObjDesc;

std::ostream & operator<< (std::ostream &out, const scObjDesc &t);

/**
 * @brief The scObjDesc class
 *
 * This represents a description of an object
 *in the scWorld vector. It's used to track
 *location, speed, and so on.
 */
class SIM_IE scObjDesc {
public:
    static const scObjDesc NULL_DESC;

    typedef int resource_type;
    const QVector2D &location() const;
    const resource_type &curResources() const;

    void moveInDir(const QVector2D &Dir, float magnitude);
    void moveTowardPoint(const QVector2D &Point, float maxDist);
    void moveAmount(const QVector2D &movementAmount);

    void addResources(resource_type resources);
    void removeResources(resource_type resources);

    scObjDesc(const QVector2D &StartPos, const QVector2D &SpeedScale);
    scObjDesc();
private:
    friend
    std::ostream & operator<< (std::ostream &out, const scObjDesc &t);

    resource_type resources;
    QVector2D thisLocation;
    QVector2D speedScale;
};


#endif // SCOBJDESC_H
