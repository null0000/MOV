#include <QString>
#include <QtTest>

#include <GlobalCore.h>
#include <commcore.h>




class CommCoreUNITTest : public QObject
{
    Q_OBJECT

public:
    CommCoreUNITTest();

private Q_SLOTS:
    void testCase();
};

CommCoreUNITTest::CommCoreUNITTest()
{
}

void CommCoreUNITTest::testCase()
{
    glbGlobals::UnitBootup();
    ccPythonComm *comm = new ccPythonComm("copyTest.py");

    QString command = "This is a test of the copy system";

    comm->SendArbitraryCommand(command + "\n");
    QString reply = comm->ReadLine();
    QVERIFY(command == reply);
}

QTEST_MAIN(CommCoreUNITTest)

#include "tst_commcoreunittest.moc"
