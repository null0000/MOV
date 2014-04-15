#ifndef COMPOSITIONCORE_H
#define COMPOSITIONCORE_H


#include <simulationcore.h>
#include <GraphicsCore.h>
#include <QVector2D>
#include <QScopedPointer>
#include <gcRenderTransform.h>

class coObject;

class coObject_d{
   coObject_d(scSim_d simDesc, gcImage_d imageDesc) :
    simDesc(simDesc), imageDesc(imageDesc){}

    QScopedPointer<coObject> instantiate();


private:
    scSim_d simDesc;
    gcImage_d imageDesc;
 };


class coObject {
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
    coObject(scObject &simObj, gcRenderable &animation, scWorld &world, gcRenderList &Renderer) :
        simObjPtr(world.addObject(simObj)),
        imageAnim(*new gcRenderOffset<renderTarget>(animation, renderTarget(world, simObjPtr)))
    {
        Renderer.pushRenderable(&imageAnim);
    }



private:
    scWorld::t_tag simObjPtr;
    gcRenderable &imageAnim;
};


void coBootUp(scWorld &world, gcRenderList &list, scInputDevice &inputDevice) {
    scObject *keyboardObject = scCreateKeyboardObject(&inputDevice, QVector2D(0, 0), QVector2D(.25, .25));
    gcImageRenderable *image = new gcImageRenderable(gcImage("face").toRenderable());
    new coObject(*keyboardObject, *image, world, list);

}

#endif // COMPOSITIONCORE_H
