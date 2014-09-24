#ifndef SCLOCATIONFUNCTOR_H
#define SCLOCATIONFUNCTOR_H

#include <QVector2D>

#include "simulationcore_ie.h"
#include "scWorld.h"

class SIM_IE scLocationFunctor {
    static scWorld::t_tag INVALID_TAG;

public:
    QVector2D operator()() const;
    void setObject(scWorld::t_tag NewTarget);
    void setObject(scWorld_p World, scWorld::t_tag NewTarget);
    scLocationFunctor(scWorld::t_tag Tag, scWorld_p World);
    scLocationFunctor(scWorld_p world);
    scLocationFunctor() : target(), world(){}
private:
    scWorld::t_tag target;
    scWorld_p world;
};


#endif // SCLOCATIONFUNCTOR_H
