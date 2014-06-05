#include <QString>
#include <QtTest>
#include <QCoreApplication>

#include <vector>
#include <sstream>

#include <scTaskIterator.h>
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

void SimulationCoreUNITTest::testCase1()
{
    const int NUM_TASKS = 10000;
    const int MAX_X = 50000;
    const int MAX_Y = 50000;

    scSubWorld<scTaskIterator> world;
    taskList_t singleTaskVec(NUM_TASKS, singleTask());
    std::minstd_rand rnum (22132);
    for (int i = 0; i < NUM_TASKS; i++) {
        float x = (((int)rnum())%(MAX_X * 2)) - MAX_X;
        float y = (((int)rnum())%(MAX_Y * 2)) - MAX_Y;

        singleTaskVec[i] = (singleTask(QVector2D(x, y)));
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

QTEST_MAIN(SimulationCoreUNITTest)

#include "tst_simulationcoreunittest.moc"
