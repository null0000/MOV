#ifndef COOBJECT_H
#define COOBJECT_H

#include <scWorld.h>
#include <QVector2D>
#include <gcRenderList.h>
#include <gcRenderTransform.h>

template<typename renderableType>
class coObject {
private:
    class renderTarget {
    private:
        scWorld::t_tag lookupTag;
        const scWorld_p world;
    public:
        QVector2D operator()() const {return world->lookupObject(lookupTag);}
        renderTarget(scWorld_p world, scWorld::t_tag tag) : lookupTag(tag), world(world){}
    };

public:
    template <typename planType>
    coObject(const planType &simObj, renderableType animation,
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



#endif // COOBJECT_H
