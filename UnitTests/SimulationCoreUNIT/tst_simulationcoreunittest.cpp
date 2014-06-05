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

void SimulationCoreUNITTest::testCase1()
{
    scSubWorld<scTaskIterator> world;
    typedef std::vector<singleTask> taskList_t;
    taskList_t singleTaskVec(1000, singleTask());
    std::minstd_rand rnum (22132);
    for (int i = 0; i < 1000; i++) {
        float x = ((int)rnum())%5000;
        float y = ((int)rnum())%5000;

        singleTaskVec[i] = (singleTask(QVector2D(x, y)));
    }



    for (taskList_t::const_iterator cItr = singleTaskVec.begin();
         cItr != singleTaskVec.end(); cItr++) {
        world.addObject(scTaskIterator(*cItr));
    }

    float maxTime = 0;

    for (taskList_t::const_iterator cItr = singleTaskVec.begin();
         cItr != singleTaskVec.end(); cItr++) {
        maxTime = std::max(maxTime, cItr->numTicksToLocation(QVector2D(0, 0)));
    }

    float curTime = 0;
    while (curTime != maxTime)
    {
        float delta = std::min((float)10, maxTime - curTime);
        curTime += delta;
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
