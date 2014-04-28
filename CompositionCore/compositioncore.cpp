#include "CompositionCore.h"
#include <simulationcore.h>

template <typename renderableType>
coObject<renderableType>::coObject(scObject_d simObj, renderableType animation, scWorld_p world, gcRenderList_p Renderer) :
    simObjPtr(world->addObject(simObj)),
    imageAnim(gcRenderOffset<renderTarget, renderableType> (animation, renderTarget(world, simObjPtr)))
{
    Renderer->pushRenderable(&imageAnim);
}
