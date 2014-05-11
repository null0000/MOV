#ifndef COMPOSITIONCORE_H
#define COMPOSITIONCORE_H


#include <simulationcore.h>
#include <GraphicsCore.h>
#include <QVector2D>
#include <QScopedPointer>
#include <gcRenderTransform.h>

template<typename renderableType> class coObject;

template<typename renderableType>
class coObject {
private:
    class renderTarget {
    private:
        scWorld::t_tag lookupTag;
        const scWorld_p world;
    public:
        QVector2D operator()() const {const scObject *obj = world->lookup(lookupTag); if (obj) return obj->position(); return QVector2D(0, 0);}
        renderTarget(scWorld_p world, scWorld::t_tag tag) : lookupTag(tag), world(world){}
    };

public:
    coObject(const scObject_d &simObj, renderableType animation,
             scWorld_p world, gcRenderList_p Renderer) :
        simObjPtr(world->addObject(simObj)),
        imageAnim(gcRenderOffset<renderTarget, renderableType> (animation, renderTarget(world, simObjPtr)))
    {
        Renderer->pushRenderable(&imageAnim);
    }

private:
    scWorld::t_tag simObjPtr;
    gcRenderOffset<renderTarget, renderableType> imageAnim;
};


void coBootUp(scWorld_p world, gcRenderList_p list, scInputDevice_p inputDevice);

#endif // COMPOSITIONCORE_H
