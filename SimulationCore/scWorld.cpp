
#include "simulationcore.h"
#include <QMap>
#include <QKeyEvent>



scWorld::t_tag scWorld::addObject(scObject_d newObj) {
    simVec.push_back(newObj.instantiate());
    return simVec.size() - 1;
}

void scWorld::simulate(delta_t timeDelta) {
    for (QVector<scObject *>::iterator itr = simVec.begin(); itr != simVec.end(); itr++)
        (*itr)->Simulate(timeDelta);
}

delta_t timeDeltaFromMilli(int milliseconds) {return ((float)(milliseconds))/TIME_CONVERSION_DIVISOR;}
