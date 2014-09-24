#ifndef COWORLD_H
#define COWORLD_H

#include <QRect>

#include <scLocationFunctor.h>
#include <scSimulationStep.h>
#include <scWorld.h>

#include "coCameraManager.h"
#include "compositioncore_ie.h"

class gcDrawingImpl;
class scKeyboardControlledObj;
class scTaskIterator;



class CMP_IE coWorld
{
public:
    typedef scWorld::t_tag t_simtag;

    void registerSimulationStep(scSimulationStep_p newStep);

    template <typename gcRenderableType, typename scSimulatableType>
    t_simtag addObject(gcRenderableType g, const scSimulatableType &s);

    void setTarget(t_simtag target);

    void simulate(delta_t time);
    void draw (gcDrawingImpl &impl);

    void cameraBounds(QRect bounds);

    coWorld(QRect cameraBounds) : world(new scWorld()), camera(world){camera.bounds(cameraBounds);}

private:
    scWorld_p world;
    coCameraManager camera;
};


template <typename gcRenderableType, typename scSimulatableType>
coWorld::t_simtag coWorld::addObject(gcRenderableType g, const scSimulatableType &s) {
    t_simtag tag (world->addObject(s));

    typedef gcRenderOffset<gcRenderableType, scLocationFunctor> rOff;
    typedef rOff *rOff_p;
    rOff_p ro = new rOff (g, scLocationFunctor(tag, world));

    camera.pushRenderable(ro);
    return tag;
}

typedef  QSharedPointer<coWorld> coWorld_p;
typedef  QSharedPointer<const coWorld> coWorld_cp;

#endif // COWORLD_H
