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

#include <glbTranslate.h>

#include <random>

#include <algorithm>


class SimulationCoreUNITTest : public QObject
{
    Q_OBJECT

public:
    SimulationCoreUNITTest();

private Q_SLOTS:
    void initTestCase();
    void cleanupTestCase();
    void testCase1();
    void testCase2();
};

SimulationCoreUNITTest::SimulationCoreUNITTest()
{
}

void SimulationCoreUNITTest::initTestCase()
{
}

void SimulationCoreUNITTest::cleanupTestCase()
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
    float x = (((int)rnum())%(maxX * 2)) - maxX;
    float y = (((int)rnum())%(maxY * 2)) - maxY;
    return QVector2D(x, y);
}

void SimulationCoreUNITTest::testCase1()
{
    static const int NUM_TASKS = 1000;

    static const int MAX_X = 5000;
    static const int MAX_Y = 5000;

    scSubWorld<scTaskIterator> world;
    taskList_t singleTaskVec(NUM_TASKS, singleTask());
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
        Q_ASSERT(ticks < 1);
    }
}

void SimulationCoreUNITTest::testCase2() {
    const int NUM_TASKS = 1000;
    const int MAX_NUM_JOBS = 25;

    const int MAX_START_X = 50000;
    const int MAX_START_Y = 50000;

    const int MAX_DELTA_X = 200;
    const int MAX_DELTA_Y = 200;

    typedef std::vector<QVector2D> vecList_t;
    typedef std::vector<vecList_t> multiVecList_t;;

    multiVecList_t mVecList;

    for (int i = 0; i < NUM_TASKS; i++) {
        vecList_t newTaskList;

        newTaskList.push_back(genRandomVec(MAX_START_X, MAX_START_Y));
        int lastIdx = 0;
        int numJobs = rnum()%MAX_NUM_JOBS;
        for (int j = 0; j < numJobs - 1; j++) {
            QVector2D deltaVec = genRandomVec(MAX_DELTA_X, MAX_DELTA_Y);
            QVector2D finalVec = deltaVec + newTaskList[lastIdx];
            newTaskList.push_back(finalVec);
        }

        mVecList.push_back(newTaskList);
    }

    typedef std::vector<scTask> taskList_t;
    typedef std::vector<taskList_t> multiTaskList_t;
    multiTaskList_t mTasklist;


    for (size_t i = 0; i < mVecList.size(); i++) {
        taskList_t tList (mVecList[i].size(), scTask());
        for (size_t j = 0; j < mVecList[j].size(); j++)
            tList[j] = scTask(mVecList[i][j]);
        mTasklist.push_back(tList);
    }

    std::vector<scTaskList> taskListList;

    for (size_t i = 0; i < mTasklist.size(); i++) {
        taskListList.push_back(scTaskList(mTasklist[i].begin(), mTasklist[i].end()));
    }

}

QTEST_MAIN(SimulationCoreUNITTest)

#include "tst_simulationcoreunittest.moc"
