#include <QString>
#include <QtTest>
#include <QCoreApplication>


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

void SimulationCoreUNITTest::testCase1()
{

}

QTEST_MAIN(SimulationCoreUNITTest)

#include "tst_simulationcoreunittest.moc"
