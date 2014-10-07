#include <QVector2D>

#include <iostream>


#include "scObjDesc.h"


const scObjDesc scObjDesc::NULL_DESC;
static const scObjDesc::resource_type INIT_RESOURCES = 500;

const QVector2D &scObjDesc::location() const {return thisLocation;}

void scObjDesc::moveInDir(const QVector2D &Dir, float magnitude) {
    thisLocation += Dir *(speedScale * magnitude);
}

void scObjDesc::moveTowardPoint(const QVector2D &Point, float maxDist) {
    thisLocation += ((thisLocation - Point) * maxDist)  * speedScale;
}

void scObjDesc::moveAmount(const QVector2D &movementAmount) {
    thisLocation += movementAmount * speedScale;
}

scObjDesc::scObjDesc(const QVector2D &StartPos, const QVector2D &SpeedScale) :
    resources(INIT_RESOURCES), thisLocation(StartPos), speedScale(SpeedScale){}

scObjDesc::scObjDesc() : resources(INIT_RESOURCES), thisLocation(0, 0), speedScale(1, 1){}


const scObjDesc::resource_type &scObjDesc::curResources() const {
    return resources;
}


void scObjDesc::addResources(resource_type newResources) {
    resources += newResources;
}

void scObjDesc::removeResources(resource_type removedResources) {
    resources -= removedResources;
}

std::ostream & operator<< (std::ostream &out, const scObjDesc &t) {
    out << "(" << t.thisLocation.x() << ", " << t.thisLocation.y() << ")";
    out << " Resources: " << t.resources;
    return out;
}
