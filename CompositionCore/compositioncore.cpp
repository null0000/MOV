#include "CompositionCore.h"
#include <simulationcore.h>

coObject::coObject(scObject_d simObj, gcRenderable &animation, scWorld_p world, gcRenderList &Renderer) :
    simObjPtr(world->addObject(simObj)),
    imageAnim(*new gcRenderOffset<renderTarget>(animation, renderTarget(world, simObjPtr)))
{
    Renderer.pushRenderable(&imageAnim);
}
