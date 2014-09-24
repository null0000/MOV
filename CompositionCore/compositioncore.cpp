#include "CompositionCore.h"
#include "coAiSpawner.h"
#include "coWorld.h"

#include <gcImage.h>
#include <simulationcore.h>
#include <stack>

coWorld_p coBootUp(QRect CameraBounds, scInputDevice_p inputDevice) {

    coWorld_p world (new coWorld(CameraBounds));


    scKeyboardMap_ccp km = scKeyboardMap_ccp(new scKeyboardMap(scKeyboardMap::stdMap()));
    scKeyboardState_p ks (new scKeyboardState(inputDevice));

    scKeyboardControlledObj kObj(ks, km);
    gcImage image ("face");

    coWorld::t_simtag st = world->addObject(image, kObj);
    world->setTarget(st);

    return world;
}
