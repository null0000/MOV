#ifndef SCFULLTAG_H
#define SCFULLTAG_H

#include "scWorld.h"

class SIM_IE scFullTag {

public:
    QVector2D objectLoc() const {return world->lookupObject(tag);}
    scFullTag(scWorld_cp world, scWorld::t_tag tag) : tag(tag), world(world){}

private:
    scWorld::t_tag tag;
    const scWorld_cp world;
};

#endif // SCFULLTAG_H
