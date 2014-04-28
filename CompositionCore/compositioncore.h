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
        QVector2D operator()() const {return world->lookup(lookupTag).position();}
        renderTarget(scWorld_p world, scWorld::t_tag tag) : lookupTag(tag), world(world){}
    };

public:
    coObject(scObject_d simObj, renderableType animation, scWorld_p world, gcRenderList_p Renderer);

private:
    scWorld::t_tag simObjPtr;
    gcRenderOffset<renderTarget, renderableType> imageAnim;
};


void coBootUp(scWorld_p world, gcRenderList_p list, scInputDevice_p inputDevice) {

    scKeyboardMap_ccp km = scKeyboardMap_ccp(new scKeyboardMap(scKeyboardMap::stdMap()));
    scKeyboardState_ccp ks (new scKeyboardState(inputDevice));
    scObject_d objDesc = scObject_d(km, ks);
    gcImage image = gcImage("face");
    new coObject<gcImage>(objDesc, image, world, list);

}

#endif // COMPOSITIONCORE_H
