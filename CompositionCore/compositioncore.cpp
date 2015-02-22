#include "CompositionCore.h"
#include "coAiSpawner.h"
#include "coWorld.h"
#include "coWorldFullTag.h"
#include "coDebugHandler.h"
#include "coTagLocFunctor.h"
#include "coChunkRenderer.h"


#include <gcImage.h>
#include <simulationcore.h>
#include <scSpendResourceStep.h>
#include <scChunkGenerator.h>
#include <stack>

coWorld_p coBootUp(scInputDevice_p inputDevice, QRect CameraBounds, QRect windowDim) {

    coWorld_p world (new coWorld(CameraBounds,windowDim));

    scKeyboardMap_ccp km = scKeyboardMap_ccp(new scKeyboardMovementMap(scKeyboardMovementMap::stdMovementMap()));
    scKeyboardState_p ks (new scKeyboardState(inputDevice));

    scKeyboardControlledObj kObj(ks, km);
    gcImage image ("face");

    coWorld::t_simtag st = world->trackObject(image, kObj);
    world->setTarget(st);



    measure_type r = std::max(windowDim.width(), windowDim.height()) /2;

     typedef std::function<point()> lambda_callback;

    lambda_callback co = [=](){
        measure_type xOff = -world->cameraOffset().x() + (windowDim.width() / 2);
        measure_type yOff = -world->cameraOffset().y() + (windowDim.height() / 2);
        return point(xOff, yOff);
    };

    coChunkRenderer<lambda_callback> cr(world, gcImage("grey"), co);
    world->addObject(cr);

    scSimulationStep *cgen = new scChunkGenerator<lambda_callback>(co, r);
    scSimulationStep_p sstep (cgen);

    world->registerSimulationStep(sstep);

#ifdef QT_DEBUG
    new coDebugHandler(world,coWorldFullTag(world, st), ks);
#endif
    scSpawner_p spawner (new coAiSpawner ("face", world));
    scSimulationStep_p step (new scSpendResourceStep(spawner));

    world->registerSimulationStep(step);

    return world;
}
