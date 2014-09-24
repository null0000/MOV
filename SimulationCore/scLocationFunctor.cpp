
#include "scLocationFunctor.h"

scWorld::t_tag scLocationFunctor::INVALID_TAG((scWorld::TypeTag)-1, -1);

QVector2D scLocationFunctor::operator()() const {
    if (!world || target == INVALID_TAG)
        return QVector2D();
    return world->lookupObject(target);
}

scLocationFunctor::scLocationFunctor(scWorld::t_tag Tag, scWorld_p World) :
    target(Tag), world(World) {
    Q_ASSERT(World);
}


void scLocationFunctor::setObject(scWorld::t_tag NewTarget) {
    target = NewTarget;
}

void scLocationFunctor::setObject(scWorld_p World, scWorld::t_tag NewTarget) {
    target = NewTarget;
    world = World;
}


scLocationFunctor::scLocationFunctor(scWorld_p world) :
    target(INVALID_TAG), world(world){}
