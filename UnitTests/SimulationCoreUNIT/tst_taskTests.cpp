
#include <scTaskList.h>
#include <scListPlan.h>
#include <algorithm>

#include "tst_unitUtil.h"
#include "tst_simulationCoreUnit.h"

void SimulationCoreUNITTest::singleTaskTest()
{
    static const int NUM_TASKS = 1000;

    static const int MAX_X = 5000;
    static const int MAX_Y = 5000;

    scSubWorld<scTaskIterator> world;
    task_list singleTaskVec(NUM_TASKS);

    for (int i = 0; i < NUM_TASKS; i++) {
        singleTaskVec[i] = (scSingleTask(tst_genRandomVec(MAX_X, MAX_Y)));
    }

    for (task_list::const_iterator cItr = singleTaskVec.begin();
         cItr != singleTaskVec.end(); cItr++) {
        world.addObject(scTaskIterator(*cItr));
    }
    float delta = 10;
    while (delta != 0)
    {
        delta = tst_maxUpdateOrTen(world, singleTaskVec);
        world.simulate(delta);
    }

    for (size_t i = 0; i < singleTaskVec.size(); i++) {
        QVector2D loc = world.lookup(i);
        const scSingleTask &curTask = singleTaskVec[i];
        float ticks = curTask.numTicksToLocation(loc);
        QVERIFY(ticks == 0);
    }
}

void SimulationCoreUNITTest::multiTaskTest() {
    const int NUM_TASKS = 1000;
    const int MAX_NUM_JOBS = 25;

    const int MAX_START_X = 5000;
    const int MAX_START_Y = 5000;

    const int MAX_DELTA_X = 200;
    const int MAX_DELTA_Y = 200;

    typedef std::vector<QVector2D> vecList_t;
    typedef std::vector<vecList_t> multiVecList_t;

    multiVecList_t mVecList (NUM_TASKS);

    tst_insertRaggedTasks(mVecList.begin(), NUM_TASKS, MAX_NUM_JOBS,
                      QVector2D(MAX_START_X, MAX_START_Y), QVector2D(MAX_DELTA_X, MAX_DELTA_Y));

    typedef std::vector<scTask> taskList_t;
    typedef std::vector<taskList_t> multiTaskList_t;
    multiTaskList_t mTasklist;

    for (size_t i = 0; i < mVecList.size(); i++) {
        taskList_t tList (mVecList[i].size(), scTask());
        for (size_t j = 0; j < mVecList[i].size(); j++)
            tList[j] = scTask(mVecList[i][j]);
        mTasklist.push_back(tList);
    }

    std::vector<scTaskList> taskListList;

    for (size_t i = 0; i < mTasklist.size(); i++) {
        taskListList.push_back(scTaskList(mTasklist[i].begin(), mTasklist[i].end()));
    }

    std::vector<scListPlan> listPlanVec (taskListList.size());

    std::transform(taskListList.begin(), taskListList.end(), listPlanVec.begin(),
                   [](const scTaskList &list) {return scListPlan(list.begin(), list.end());});

    std::vector<scTaskIterator> itrVec(listPlanVec.size());
    std::transform(listPlanVec.begin(), listPlanVec.end(), itrVec.begin(),
                   [](const scListPlan &plan){return scTaskIterator(plan);});

    scSubWorld <scTaskIterator> world;
    std::for_each(itrVec.begin(), itrVec.end(), [&](const scTaskIterator &itr){world.addObject(itr);});


    float curUpdate = tst_maxUpdateOrTen(world, itrVec);
    while (curUpdate > 0) {
        world.simulate(curUpdate);

        //this is a hack to make sure that itrVec stays updated to match world.
        tst_updateList(itrVec, world);
        curUpdate = tst_maxUpdateOrTen(world, itrVec);
    }

    QVERIFY(curUpdate == 0);
    QVERIFY(tst_maxUpdateOrTen(world, itrVec) == 0);
}

void SimulationCoreUNITTest::taskUsingTest() {

    typedef std::vector<scTask> taskList_t;
    typedef scSubWorld<scTaskIterator> world_type;
    typedef std::deque<world_type::t_tag> tag_list;

    static const int TASK_COUNT = 50000;
    static const QVector2D TARGET_LOC(5000, 5000);

    static const float usePercent = .75;

    taskList_t list (TASK_COUNT);

    for (taskList_t::iterator iItr = list.begin(); iItr != list.end(); iItr++)
        *iItr = scTask(TARGET_LOC, ((rnum()%100)/100.0) < usePercent);


    std::vector<scSingleTask> taskVector (TASK_COUNT);
    std::for_each(list.begin(), list.end(),
                  [&](const scTask &Task){taskVector.push_back(scSingleTask(TARGET_LOC, Task));});


    world_type world;
    std::for_each(taskVector.begin(),
                  taskVector.end(),[&](const scSingleTask &taskPlan){world.addObject(scTaskIterator(taskPlan));});

    world.simulate(TARGET_LOC.length() - 1);

    tag_list objDeque;
    std::insert_iterator<tag_list> ii (objDeque, objDeque.begin());

    world.gatherUsingList(ii);

    size_t count = 0;
    std::for_each(list.begin(), list.end(), [&](const scTask &task){if (task.isUsing()) count++;});

    QCOMPARE(objDeque.size(), count);

    world.simulate(1);
    QCOMPARE(tst_maxUpdateOrTen(world, taskVector), (float)0);

}
