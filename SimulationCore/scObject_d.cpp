
#include "simulationcore.h"

scObject *scKeyboardObject_d::instantiate() const {return new scKeyboardControlledObj(kstate, kmap, speedScale, startLocation);}

scObject *scAIObject_d::instantiate() const {

}
