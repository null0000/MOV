#ifndef SCUSELISTENER_H
#define SCUSELISTENER_H

#include "scWorld.h"

class scObject;

class scUseListener
{
public:
    scUseListener(scWorld_p world) :
        world(world){}
    scUseListener() :  world(0) {}

    void registerUse(scObject &source) {
        if (!world.isNull()) world->registerUse(source);
    }

public:
    scWorld_p world;
};

#endif // SCUSELISTENER_H
