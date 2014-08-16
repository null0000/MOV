#include <QString>
#include <QtTest>
#include <QCoreApplication>

#include <vector>
#include <sstream>

#include <scTaskIterator.h>
#include <scTaskList.h>
#include <scWorld.h>
#include <scTask.h>
#include <scWorldDesc.h>
#include <scObjDesc.h>
#include <scListPlan.h>
#include <scSingleTask.h>

#include <glbTranslate.h>

#include <random>

#include <algorithm>


class SimulationCoreUNITTest : public QObject
{
    Q_OBJECT

public:
    SimulationCoreUNITTest();

private Q_SLOTS:
    void testCase1();
    void testCase2();
    void testCase3();
    void testAdjacency();
};

SimulationCoreUNITTest::SimulationCoreUNITTest()
{
}


typedef std::vector<scSingleTask> taskList_t;

/**
 * @brief GetLargestOrTen Returns the largest update needed, or ten if that works.
 * @param world
 * @param taskList
 * @return
 *
 *returns the largest update needed to complete all tasks in the task list, or
 *10 if that number is over 10. 10 is chosen as a magic number - probably should
 *be parameterized, but oh well.
 */
float GetLargestOrTen(const scSubWorld<scTaskIterator> &world, const taskList_t &taskList) {
    float curMax = 0;
    for (unsigned int i = 0; i < taskList.size(); i++) {
        const scSingleTask &tsk = taskList[i];
        float ticks = tsk.numTicksToLocation(world.lookup(i));
        if (ticks > 10)
            return 10;
        curMax = std::max(curMax, ticks);
    }
    return curMax;

}

static std::minstd_rand rnum (22132);
QVector2D genRandomVec(unsigned int maxX, unsigned int maxY) {
    int unX = ((rnum())%(maxX * 2)); //unnormalized x
    float x = (float)(unX - (int)maxX);

    int unY = ((rnum())%(maxY * 2)); //unnormalizedY
    float y = (float)(unY - (int)maxY);
    return QVector2D(x, y);
}

scObjDesc createObjDesc(size_t idx, const scSubWorld<scTaskIterator> &taskWorld) {
    QVector2D loc (taskWorld.lookup(idx));
    return scObjDesc(loc, QVector2D(1, 1));
}

/**
 * @brief updateList Updates itrVec to match what's shown in scSubWorld
 * @param itrVec
 * @param taskWorld
 *
 *This updates itrVec to match what's in the input subworld. This is used because
 *it's difficult to track needed updates otherwise.
 */
void updateList(std::vector<scTaskIterator> &itrVec, const scSubWorld<scTaskIterator> &taskWorld) {
    QVERIFY(itrVec.size() == taskWorld.maxTag());
    for (size_t i = 0; i < itrVec.size(); i++) {
        scObjDesc od (createObjDesc(i, taskWorld));
        itrVec[i].updateStrategy(od, scWorldDesc());
    }
}


/**
 * @brief maxUpdateOrTen
 *        Returns the maxiumum update needed, or 10 if it's over 10
 * @param itrVec
 * @param taskWorld
 * @return a float
 *
 *Returns the maxiumum update needed to complete all tasks in itrVec, according
 *to the subworld. Alternatively, it returns 10 if the number is above 10.
 *
 *10 is a magic number, but unit test, so oh well.
 */
float maxUpdateOrTen(std::vector<scTaskIterator> &itrVec, const scSubWorld<scTaskIterator> &taskWorld) {
    float curMax = 0;
    Q_ASSERT(itrVec.size() == taskWorld.maxTag());
    for (size_t i = 0; i < itrVec.size(); i++) {
        scObjDesc od (createObjDesc(i, taskWorld));
        scMovementDesc md (itrVec[i].getMovement(od));
        float length = md.maxMovement().length();
        if (length > 10)
            return 10;
        curMax = std::max(curMax, length);
    }
    return curMax;
}

template <typename insert_iterator>
insert_iterator insertRaggedTasks(insert_iterator insertLoc, int numTasks, int numJobs,
                                  const QVector2D &startDelta, const QVector2D secondaryDelta)
{
    typedef std::vector<QVector2D> vecList_t;
    for (int i = 0; i < numTasks; i++) {
        vecList_t newTaskList;

        newTaskList.push_back(genRandomVec(startDelta.x(), startDelta.y()));
        int lastIdx = 0;
        int thisJobCount = rnum() % numJobs;

        for (int j = 0; j < thisJobCount - 1; j++) {
            QVector2D deltaVec = genRandomVec(secondaryDelta.x(), secondaryDelta.y());
            QVector2D finalVec = deltaVec + newTaskList[lastIdx];
            newTaskList.push_back(finalVec);
        }

        *insertLoc = newTaskList;
        insertLoc++;
    }
    return insertLoc;
}

void SimulationCoreUNITTest::testCase1()
{
    static const int NUM_TASKS = 1000;

    static const int MAX_X = 5000;
    static const int MAX_Y = 5000;

    scSubWorld<scTaskIterator> world;
    taskList_t singleTaskVec(NUM_TASKS);

    for (int i = 0; i < NUM_TASKS; i++) {
        singleTaskVec[i] = (scSingleTask(genRandomVec(MAX_X, MAX_Y)));
    }

    for (taskList_t::const_iterator cItr = singleTaskVec.begin();
         cItr != singleTaskVec.end(); cItr++) {
        world.addObject(scTaskIterator(*cItr));
    }
    float delta = 10;
    while (delta != 0)
    {
        delta = GetLargestOrTen(world, singleTaskVec);
        world.simulate(delta);
    }

    for (size_t i = 0; i < singleTaskVec.size(); i++) {
        QVector2D loc = world.lookup(i);
        const scSingleTask &curTask = singleTaskVec[i];
        float ticks = curTask.numTicksToLocation(loc);
        QVERIFY(ticks == 0);
    }
}

void SimulationCoreUNITTest::testCase2() {
    const int NUM_TASKS = 1000;
    const int MAX_NUM_JOBS = 25;

    const int MAX_START_X = 5000;
    const int MAX_START_Y = 5000;

    const int MAX_DELTA_X = 200;
    const int MAX_DELTA_Y = 200;

    typedef std::vector<QVector2D> vecList_t;
    typedef std::vector<vecList_t> multiVecList_t;

    multiVecList_t mVecList (NUM_TASKS);

    insertRaggedTasks(mVecList.begin(), NUM_TASKS, MAX_NUM_JOBS,
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


    float curUpdate = maxUpdateOrTen(itrVec, world);
    while (curUpdate > 0) {
        world.simulate(curUpdate);

        //this is a hack to make sure that itrVec stays updated to match world.
        updateList(itrVec, world);
        curUpdate = maxUpdateOrTen(itrVec, world);
    }

    QVERIFY(curUpdate == 0);
    QVERIFY(maxUpdateOrTen(itrVec, world) == 0);
}

void SimulationCoreUNITTest::testCase3() {

    typedef std::vector<scTask> taskList_t;

    static const int TASK_COUNT = 50000;
    static const QVector2D TARGET_LOC(5000, 5000);

    static const float usePercent = .75;

    taskList_t list (TASK_COUNT);

    for (taskList_t::iterator iItr = list.begin(); iItr != list.end(); iItr++)
        *iItr = scTask(TARGET_LOC, ((rnum()%100)/100.0) < usePercent);


    std::vector<scSingleTask> taskVector (TASK_COUNT);
    std::for_each(list.begin(), list.end(),
                  [&](const scTask &Task){taskVector.push_back(scSingleTask(TARGET_LOC, Task));});

    scSubWorld<scTaskIterator> world;
    std::for_each(taskVector.begin(),
                  taskVector.end(),[&](const scSingleTask &taskPlan){world.addObject(scTaskIterator(taskPlan));});

    world.simulate(TARGET_LOC.length() - 1);

    std::deque<QVector2D> objDeque;
    std::insert_iterator<std::deque<QVector2D> > ii (objDeque, objDeque.begin());

    world.gatherUsingList(ii);

    size_t count = 0;
    std::for_each(list.begin(), list.end(), [&](const scTask &task){if (task.isUsing()) count++;});

    QCOMPARE(objDeque.size(), count);

    world.simulate(1);
    QCOMPARE(GetLargestOrTen(world, taskVector), (float)0);

}


void SimulationCoreUNITTest::testAdjacency(){
    static const size_t ADDITIONAL_TAGS = 100;
    static const size_t VALID_DIST = 100;

    static const size_t INVALID_DIST_MAX = 200;

    QVector2D startVec = genRandomVec(500, 500);
    std::vector<scSingleTask> validTasks;
    std::vector<scSingleTask> invalidTasks;

    QVector2D maxDist (startVec);

    for (size_t idx = 0; idx < ADDITIONAL_TAGS; idx++) {
        QVector2D modVec = genRandomVec(INVALID_DIST_MAX, INVALID_DIST_MAX);
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



QTEST_MAIN(SimulationCoreUNITTest)

#include "tst_simulationcoreunittest.moc"
