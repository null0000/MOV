#include "CompositionCore.h"
#include "coAiSpawner.h"
#include <simulationcore.h>

void coBootUp(scWorld_p world, gcRenderList_p list, scInputDevice_p inputDevice) {

    scKeyboardMap_ccp km = scKeyboardMap_ccp(new scKeyboardMap(scKeyboardMap::stdMap()));
    scKeyboardState_p ks (new scKeyboardState(inputDevice));

    gcImage image ("face");
    new coObject<gcImage>(scKeyboardControlledObj(ks, km), image, world, list);

    scSimulationStep_p step (new coAiSpawner(list, "face", world));
    world->registerSimulationStep(step);
}
