#include "CompositionCore.h"
#include <simulationcore.h>
#include "ccAISpawner.h"
#include <scInstrTask.h>

void coBootUp(scWorld_p world, gcRenderList_p list, scInputDevice_p inputDevice) {

    scKeyboardMap_ccp km = scKeyboardMap_ccp(new scKeyboardMap(scKeyboardMap::stdMap()));
    scKeyboardState_ccp ks (new scKeyboardState(inputDevice));
    const scObject_d &objDesc = scKeyboardObject_d(km, ks, QVector2D(0, 0),
                                                   QVector2D(.25, .25),scUseListener(world));
    gcImage image = gcImage("face");
    new coObject<gcImage>(objDesc, image, world, list);

    scInstrDesc desc (QVector2D(100, 100));
    scInstrTask *task = new scInstrTask(desc);
    scAIObject_d obj (*task);
    new ccAISpawner(world, list, obj);

}
