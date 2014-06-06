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
};

SimulationCoreUNITTest::SimulationCoreUNITTest()
{
}

class singleTask : public scPlan {
public:
    scTask generateNextTask(const scObjDesc &,
                            const scWorldDesc &) {
        return scTask();
    }

    float numTicksToLocation(const QVector2D &startLoc) const {
        return (startLoc - location).length();
    }

    scTask firstTask() const {return oneTask;}

    std::string dump() {
        std::string taskStr = oneTask.dump();
        return std::string("Task: ") + taskStr +
               std::string(" with a target location of: ") +
               vec2str(location);
    }

    singleTask(const QVector2D &location) :
        oneTask(location), location(location){}

    singleTask() :
        oneTask(), location(0, 0){}

    scPlan *copy() const {
        return new singleTask(location);
    }

private:
    scTask oneTask;
    QVector2D location;

};

typedef std::vector<singleTask> taskList_t;
float GetLargestOrTen(const scSubWorld<scTaskIterator> &world, const taskList_t &taskList) {
    float curMax = 0;
    for (unsigned int i = 0; i < taskList.size(); i++) {
        const singleTask &tsk = taskList[i];
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

void SimulationCoreUNITTest::testCase1()
{
    static const int NUM_TASKS = 1000;

    static const int MAX_X = 5000;
    static const int MAX_Y = 5000;

    scSubWorld<scTaskIterator> world;
    taskList_t singleTaskVec(NUM_TASKS);

    for (int i = 0; i < NUM_TASKS; i++) {
        singleTaskVec[i] = (singleTask(genRandomVec(MAX_X, MAX_Y)));
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
        const singleTask &curTask = singleTaskVec[i];
        float ticks = curTask.numTicksToLocation(loc);
        QVERIFY(ticks == 0);
    }
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

scObjDesc createObjDesc(size_t idx, const scSubWorld<scTaskIterator> &taskWorld) {
    QVector2D loc (taskWorld.lookup(idx));
    return scObjDesc(loc, QVector2D(1, 1));
}

void updateList(std::vector<scTaskIterator> &itrVec, const scSubWorld<scTaskIterator> &taskWorld) {
    QVERIFY(itrVec.size() == taskWorld.maxTag());
    for (size_t i = 0; i < itrVec.size(); i++) {
        scObjDesc od (createObjDesc(i, taskWorld));
        itrVec[i].updateStrategy(od, scWorldDesc());
    }
}

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
        updateList(itrVec, world);
        curUpdate = maxUpdateOrTen(itrVec, world);
    }

    QVERIFY(curUpdate == 0);
    QVERIFY(maxUpdateOrTen(itrVec, world) == 0);
}

QTEST_MAIN(SimulationCoreUNITTest)

#include "tst_simulationcoreunittest.moc"
