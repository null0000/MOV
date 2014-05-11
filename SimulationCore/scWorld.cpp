
#include "simulationcore.h"
#include <QMap>
#include <QKeyEvent>
#include <scUseRegister.h>

//TODO: These are in WAY the wrong place. Remove when haxorzing is done.
#include "scInstr.h"
#include "scInstrTask.h"


scWorld::t_tag scWorld::addObject(const scObject_d &newObj) {
    simVec.push_back(newObj.instantiate());
    return simVec.size() - 1;
}

void scWorld::simulate(delta_t timeDelta) {
    for (object_list::iterator itr = simVec.begin(); itr != simVec.end(); itr++) {
        (*itr)->Simulate(timeDelta);
    }
}

void scWorld::registerUse(const scObject &source) {
    for (useRegister_list::iterator itr = regObjVec.begin(); itr != regObjVec.end(); itr++) {
        (*itr)->registerUse(source);
    }
}

delta_t timeDeltaFromMilli(int milliseconds) {return ((float)(milliseconds))/TIME_CONVERSION_DIVISOR;}

const scObject *scWorld::lookup(t_tag tag) const {return simVec.size() ? simVec[tag] : NULL;}


void scWorld::addUseRegister(scUseRegister &reg) {
    regObjVec.push_back(&reg);
}
