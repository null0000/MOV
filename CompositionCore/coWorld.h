#ifndef COWORLD_H
#define COWORLD_H

#include <QRect>

#include <scLocationFunctor.h>
#include <scSimulationStep.h>
#include <scWorld.h>

#include "coCameraManager.h"
#include "compositioncore_ie.h"
#include <gcTextList.h>

class gcDrawingImpl;
class scKeyboardControlledObj;
class scTaskIterator;



class CMP_IE coWorld
{
public:
    typedef scWorld::t_tag t_simtag;
    typedef gcTextList::t_tag t_dbgStrTag;
    typedef std::vector<gcRenderable *> renderable_list;
    typedef scWorld::chunk_description chunk_description;
    typedef scWorld::const_chunk_description const_chunk_description;

    static const t_simtag &NULL_SIM_TAG;
    static const t_dbgStrTag &NULL_DBGSTR_TAG;

    void registerSimulationStep(scSimulationStep_p newStep);

    template <typename gcRenderableType, typename scSimulatableType>
    t_simtag addObject(gcRenderableType g, const scSimulatableType &s);

    template <typename gcRenderableType, typename scSimulatableType>
    t_simtag trackObject(gcRenderableType g, const scSimulatableType &s);

    void setTarget(t_simtag target);

    template <typename gcRenderableType>
    void addObject(gcRenderableType g);


    void simulate(delta_t time);
    void draw (gcDrawingImpl &impl);

    void cameraBounds(QRect bounds);
    QVector2D cameraOffset() const;

    t_dbgStrTag addDebugText(glbStringCallback_p Callback);
    void removeDebugText(t_dbgStrTag rmTag);
    void clearDebugText();

    template<typename callback>
    void chunkCallback(point p, measure_type r, callback &cb) const;

    coWorld(QRect cameraBounds, QRect viewingWindow) :
        world(new scWorld()), camera(world, cameraBounds, viewingWindow) {}

    //forwarded from scWorld
    QVector2D lookupLoc(t_simtag tag) const;

    scWorld_cp getWorld() const;
private:
    void drawUntracked (gcDrawingImpl &impl) const;

    scWorld_p world;
    coCameraManager camera;
    renderable_list untrackedList;

#ifdef QT_DEBUG
    gcTextList debugText;
#endif
};




template <typename gcRenderableType, typename scSimulatableType>
coWorld::t_simtag coWorld::trackObject(gcRenderableType g, const scSimulatableType &s) {
    t_simtag tag (world->addObject(s));

    typedef gcRenderOffset<gcRenderableType, scLocationFunctor> rOff;
    typedef rOff *rOff_p;
    rOff_p ro = new rOff (g, scLocationFunctor(tag, world));

    camera.pushRenderable(ro);
    return tag;
}

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

template <typename gcRenderableType>
void coWorld::addObject(gcRenderableType g) {
    camera.pushRenderable(new gcRenderableType(g));
}


template<typename callback>
void coWorld::chunkCallback(point p, measure_type r, callback &cb) const {
    world->chunkCallback(p, r, cb);
}

#endif // COWORLD_H
