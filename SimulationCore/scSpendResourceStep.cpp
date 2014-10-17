#include "scSpendResourceStep.h"


void scSpendResourceStep::runStep(scWorld &world, scChunkManager &, delta_t) {
    nullCheck();

    tag_list users (sortedUsingList(world));
    for (auto user : users) {
        if (std::lower_bound(lastUsingList.begin(), lastUsingList.end(), user) != lastUsingList.end())
            continue;
        const scObjDesc &d (world.objInfo(user));
        Q_ASSERT(&d != &scObjDesc::NULL_DESC);
        if (d.curResources() < SPAWN_COST)
            continue;
        world.removeResources(user, SPAWN_COST);
        spawnAI(d.location());
    }
    lastUsingList.clear();
    lastUsingList.insert(lastUsingList.begin(), users.begin(), users.end());
}

scSpendResourceStep::tag_list scSpendResourceStep::sortedUsingList(const scWorld &world) const {
    nullCheck();

    tag_list list;
    std::insert_iterator<tag_list> iitr (list, list.begin());
    world.gatherUsingList(iitr);
    std::sort(list.begin(), list.end());
    return list;
}


scSpendResourceStep::scSpendResourceStep(scSpawner_p spawner) :
    spawner(spawner){nullCheck();}

void scSpendResourceStep::nullCheck() const {
    Q_ASSERT(!spawner.isNull());
}

void scSpendResourceStep::spawnAI(QVector2D vec) {
    nullCheck();
    if (spawner.isNull())
        return;
    spawner->spawnAI(vec);
}
