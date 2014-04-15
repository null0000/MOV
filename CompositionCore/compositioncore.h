#ifndef COMPOSITIONCORE_H
#define COMPOSITIONCORE_H


#include <simulationcore.h>
#include <GraphicsCore.h>
#include <QVector2D>
#include <QScopedPointer>
#include <gcRenderTransform.h>

class coObject;

class coObject_d{
   coObject_d(scObject_d simDesc, gcImage_d imageDesc) :
    simDesc(simDesc), imageDesc(imageDesc){}

    coObject *instantiate();


private:
    scObject_d simDesc;
    gcImage_d imageDesc;
 };


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
    coObject(scObject_d simObj, gcRenderable &animation, scWorld_p world, gcRenderList &Renderer);



private:
    scWorld::t_tag simObjPtr;
    gcRenderable &imageAnim;
};


void coBootUp(scWorld_p world, gcRenderList &list, scInputDevice_p inputDevice) {

    scKeyboardMap_ccp km = scKeyboardMap_ccp(new scKeyboardMap(scKeyboardMap::stdMap()));
    scKeyboardState_ccp ks (new scKeyboardState(inputDevice));
    scObject_d objDesc = scObject_d(km, ks);
    gcImageRenderable *image = new gcImageRenderable(gcImage("face").toRenderable());
    new coObject(objDesc, *image, world, list);

}

#endif // COMPOSITIONCORE_H
