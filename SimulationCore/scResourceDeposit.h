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
    typedef std::pair<resource_type, resource_type> gathered_remaining_pair;

    scResourceDeposit(){}
    scResourceDeposit(point loc, measure_type radius, delta_t mineTime, resource_type startResources) :
        p(loc), rad(radius), value(startResources), timeToMine(mineTime){}


    resource_type remainingValue() const;
    gathered_remaining_pair mine(delta_t time);
    point location() const {return p;}
    measure_type radius() const {return rad;}
private:
    point p;
    measure_type rad;
    resource_type value;
    delta_t timeToMine;

};


#endif // SCRESOURCEDEPOSIT_H
