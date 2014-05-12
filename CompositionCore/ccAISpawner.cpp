

#include "ccAISpawner.h"
#include "CompositionCore.h"

#include <simulationcore.h>
#include <scUseRegister.h>
#include <scObject.h>
#include <scInstr.h>
#include <scInstrTask.h>

#include <iostream>

ccAISpawner::ccAISpawner(scWorld_p world, gcRenderList_p list, scAIObject_d objectDesc) :
    obj(objectDesc), world(world), list(list)
{
    world->addUseRegister(*this);
}


void ccAISpawner::registerUse(const scObject &) {
    gcImage image ("face");
    new coObject<gcImage>(obj, image, world, list);
}
