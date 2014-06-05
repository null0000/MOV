#include "CompositionCore.h"
#include <simulationcore.h>

void coBootUp(scWorld_p /*world*/, gcRenderList_p /*list*/, scInputDevice_p inputDevice) {

    scKeyboardMap_ccp km = scKeyboardMap_ccp(new scKeyboardMap(scKeyboardMap::stdMap()));
    scKeyboardState_p ks (new scKeyboardState(inputDevice));

    gcImage image = gcImage("face");
//    new coObject<gcImage>(/*objDesc*/, image, world, list);

//    scInstrDesc desc (QVector2D(100, 100));
//    scInstrTask *task = new scInstrTask(desc);
//    scAIObject_d obj (*task);
}
