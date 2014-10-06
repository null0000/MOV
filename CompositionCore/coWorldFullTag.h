#ifndef COWORLDFULLTAG_H
#define COWORLDFULLTAG_H

#include "coWorld.h"
#include "scFullTag.h"

#include "compositioncore_ie.h"

class CMP_IE coWorldFullTag {
public:
    QVector2D loc() {return world->lookupLoc(tag);}
    operator scFullTag() const {return scFullTag(world->getWorld(), tag);}

    bool operator ==(const coWorld::t_simtag &Other) const {return tag == Other;}
    bool operator !=(const coWorld::t_simtag &Other) const {return !(tag == Other);}

    coWorldFullTag(coWorld_cp world, coWorld::t_simtag tag) : world(world), tag(tag){}
    coWorldFullTag() : world(NULL), tag(coWorld::NULL_SIM_TAG){}

private:
    coWorld_cp world;
    coWorld::t_simtag tag;
};


#endif // COWORLDFULLTAG_H
