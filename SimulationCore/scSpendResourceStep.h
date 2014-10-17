#ifndef SCSPENDRESOURCESTEP_H
#define SCSPENDRESOURCESTEP_H

#include "simulationcore_ie.h"

#include "scSimulationStep.h"
#include "scSpawner.h"
#include "scObjDesc.h"
#include "scWorld.h"

#include <qvector2d.h>



//!
//! \brief The scSpendResourceStep class
//!
//! Allocates resources for objects based on rules and stuff. I
//! have yet to determine those rules, so this class might go in the trash
//! can when I get a better idea how things are gonna work.
//!
class SIM_IE scSpendResourceStep : public scSimulationStep {
public:
    typedef scObjDesc object_type;
    typedef object_type::resource_type resource_type;
    typedef std::vector<object_type> obj_list;

    typedef scWorld::t_tag t_tag;
    typedef std::vector<t_tag> tag_list;

    static const resource_type SPAWN_COST = 50;

    void runStep(scWorld &world, scChunkManager &m, delta_t time);

    scSpendResourceStep (scSpawner_p spawner);

private:
    void nullCheck() const;
    void spawnAI(QVector2D vec);
    tag_list sortedUsingList(const scWorld &world) const;

    tag_list lastUsingList;
    scSpawner_p spawner;
};

#endif // SCSPENDRESOURCESTEP_H
