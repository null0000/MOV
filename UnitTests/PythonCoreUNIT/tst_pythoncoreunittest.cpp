#include <QString>
#include <QtTest>

class PythonCoreUNITTest : public QObject
{
    Q_OBJECT

public:
    PythonCoreUNITTest();

private Q_SLOTS:
    void testCase1();
};

PythonCoreUNITTest::PythonCoreUNITTest()
{
}

void PythonCoreUNITTest::testCase1()
{
    QVERIFY2(true, "Failure");
}

QTEST_APPLESS_MAIN(PythonCoreUNITTest)

#include "tst_pythoncoreunittest.moc"
