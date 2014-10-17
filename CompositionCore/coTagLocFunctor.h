#ifndef COTAGLOCFUNCTOR_H
#define COTAGLOCFUNCTOR_H

#include <glbDefinitions.h>

#include <QSharedPointer>

#include "coWorld.h"

class coTagLocFunctor {
public:
    typedef coWorld::t_simtag sim_tag;
    point operator()() const {return world->lookupLoc(tag);}
    coTagLocFunctor(coWorld_cp world, sim_tag t) :
        world(world), tag(t){}
    coTagLocFunctor(){}

private:
    coWorld_cp world;
    sim_tag tag;
};

#endif // COTAGLOCFUNCTOR_H
