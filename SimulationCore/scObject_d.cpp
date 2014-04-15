
#include "simulationcore.h"

scObject *scObject_d::instantiate() const
{
    switch(controller)
    {
    case KeyControlledE:
        return InstantiateKeyboardObj();
    default:
        Q_ASSERT(false);
        return NULL;
    }
}


scObject *scObject_d::InstantiateKeyboardObj() const {return new scKeyboardControlledObj(kstate, kmap, speedScale, startLocation);}
