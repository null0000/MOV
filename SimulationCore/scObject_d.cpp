
#include "simulationcore.h"
#include "scAIObject.h"
#include "scUseListener.h"

scObject *scKeyboardObject_d::instantiate() const {
    return new scKeyboardControlledObj(kstate, kmap, speedScale, startLocation, listener);

}

scObject *scAIObject_d::instantiate() const {
    return new scAIObject(task, QVector2D(1, 1));
}
