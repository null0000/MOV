#ifndef TST_SIMULATIONCOREUNIT_H
#define TST_SIMULATIONCOREUNIT_H

#include <QString>
#include <QtTest>
#include <QCoreApplication>

class SimulationCoreUNITTest : public QObject
{
    Q_OBJECT

public:
    SimulationCoreUNITTest();

private Q_SLOTS:
    //RESOURCES TESTS//
    void testResourceGathering();
    void testResourceCounting();
    void testResourceChunking();

    //TASK TESTS//
    void singleTaskTest();
    void multiTaskTest();
    void taskUsingTest();

    //WORLD TESTS//
    void testAdjacency();

};



#endif // TST_SIMULATIONCOREUNIT_H
