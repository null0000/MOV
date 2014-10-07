#include "CompositionCore.h"
#include "coAiSpawner.h"
#include "coWorld.h"
#include "coWorldFullTag.h"
#include "coDebugHandler.h"

#include <gcImage.h>
#include <simulationcore.h>
#include <stack>

coWorld_p coBootUp(scInputDevice_p inputDevice, QRect CameraBounds, QRect windowDim) {

    coWorld_p world (new coWorld(CameraBounds,windowDim));


    scKeyboardMap_ccp km = scKeyboardMap_ccp(new scKeyboardMovementMap(scKeyboardMovementMap::stdMovementMap()));
    scKeyboardState_p ks (new scKeyboardState(inputDevice));

    scKeyboardControlledObj kObj(ks, km);
    gcImage image ("face");

    coWorld::t_simtag st = world->trackObject(image, kObj);
    world->setTarget(st);

#ifdef QT_DEBUG
    new coDebugHandler(world,coWorldFullTag(world, st), ks);
#endif
    coAiSpawner ai("face", world);
    scSimulationStep_p step (new coAiSpawner(ai));

    world->registerSimulationStep(step);

    return world;
}
