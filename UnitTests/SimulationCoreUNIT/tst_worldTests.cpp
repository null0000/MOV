#include "tst_simulationCoreUnit.h"
#include "tst_unitUtil.h"

#include <scWorld.h>
#include <scWorldDesc.h>

#include <sstream>
#include <QVector2D>



void SimulationCoreUNITTest::testAdjacency(){
    static const size_t ADDITIONAL_TAGS = 100;
    static const size_t VALID_DIST = 100;

    static const size_t INVALID_DIST_MAX = 200;

    QVector2D startVec = tst_genRandomVec(500, 500);
    std::vector<scSingleTask> validTasks;
    std::vector<scSingleTask> invalidTasks;

    QVector2D maxDist (startVec);

    for (size_t idx = 0; idx < ADDITIONAL_TAGS; idx++) {
        QVector2D modVec = tst_genRandomVec(INVALID_DIST_MAX, INVALID_DIST_MAX);
        std::vector<scSingleTask> *tagList = NULL;
        if (modVec.length() < VALID_DIST)
            tagList = &validTasks;
        else
            tagList = &invalidTasks;
        if (maxDist.length() < (modVec + startVec).length())
            maxDist = modVec + startVec;

        scSingleTask task (modVec + startVec);

        tagList->push_back(task);
    }

    typedef scWorld t_worldType;
    typedef t_worldType::t_tag t_tagType;

    t_worldType world;

    typedef std::vector<scSingleTask>::iterator task_iterator;
    typedef std::vector<t_tagType> t_tagVec;
    t_tagVec validTags;
    for (task_iterator tItr = validTasks.begin(); tItr != validTasks.end(); tItr++) {
        validTags.push_back(world.addObject(scTaskIterator(*tItr)));
    }

    t_tagVec invalidTags;
    for (task_iterator tItr = invalidTasks.begin(); tItr != invalidTasks.end(); tItr++) {
        invalidTags.push_back(world.addObject(scTaskIterator(*tItr)));
    }

    world.simulate(maxDist.length() + 1);

    std::deque<t_tagType> tagList;
    std::insert_iterator<std::deque<t_tagType> > tagIItr(tagList, tagList.begin());
    world.getAdjacentObjects(startVec, VALID_DIST, tagIItr);

    std::stringstream sstr;

    sstr << "Invalid number of adjacent objects: " << validTags.size() << " != " << tagList.size();

    QVERIFY2(validTags.size() == tagList.size(), sstr.str().c_str());

    for (std::deque<t_tagType>::iterator itr = tagList.begin(); itr != tagList.end(); itr++) {
        auto retTag = std::find(validTags.begin(), validTags.end(), *itr);
        QVERIFY2(retTag != validTags.end(), "Couldn't find a valid tag in the adjacent tags list");
    }

}
