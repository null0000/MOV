#ifndef SCRESOURCEDEPOSIT_H
#define SCRESOURCEDEPOSIT_H

#include <QVector2D>
#include "scWorld.h"

#include "simulationcore_ie.h"

class SIM_IE scResourceDeposit {
public:
    typedef long long resource_type;
    typedef QVector2D point;
    typedef float coord_type;
    typedef float measure_type;

    scResourceDeposit(){}
    scResourceDeposit(point loc, measure_type radius, delta_t mineTime, resource_type startResources) :
        p(loc), rad(radius), value(startResources), timeToMine(mineTime){}

    resource_type Mine(delta_t /*time*/){return value;}
    point location() const{return p;}
    measure_type radius() const{return rad;}
private:
    point p;
    measure_type rad;
    resource_type value;
    delta_t timeToMine;

};


#endif // SCRESOURCEDEPOSIT_H
