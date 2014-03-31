#ifndef COMPOSITIONCORE_H
#define COMPOSITIONCORE_H


#include <simulationcore.h>
#include <GraphicsCore.h>
#include <QVector2D>
#include <QScopedPointer>
#include <gcRenderTransform.h>

class ccObject;

class ccObject_d{
   ccObject_d(scSim_d simDesc, gcImage_d imageDesc) :
    simDesc(simDesc), imageDesc(imageDesc){}

    QScopedPointer<ccObject> instantiate();


private:
    scSim_d simDesc;
    gcImage_d imageDesc;
 };


class ccObject {
private:
    class renderTarget {
    private:
        scWorld::t_tag lookupTag;
        const scWorld &world;
    public:
        QVector2D operator()() const {return world.lookup(lookupTag).position();}
        renderTarget(const scWorld &world, scWorld::t_tag tag) : lookupTag(tag), world(world){}
    };

public:
    ccObject(scObject &simObj, gcRenderable &animation, scWorld &world, gcRenderList &Renderer) :
        simObjPtr(world.addObject(simObj)),
        imageAnim(*new gcRenderOffset<renderTarget>(animation, renderTarget(world, simObjPtr)))
    {
        Renderer.pushRenderable(&imageAnim);
    }



private:
    scWorld::t_tag simObjPtr;
    gcRenderable &imageAnim;
};


void ccBootUp(scWorld &world, gcRenderList &list, scInputDevice &inputDevice) {
    scObject *keyboardObject = scCreateKeyboardObject(&inputDevice, QVector2D(0, 0), QVector2D(1, 1));
    gcRenderable *image = (new gcImage("face"))->toRenderable();
    new ccObject(*keyboardObject, *image, world, list);

}

#endif // COMPOSITIONCORE_H
