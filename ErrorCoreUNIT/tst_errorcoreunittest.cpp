#include <QString>
#include <QtTest>

class ErrorCoreUNITTest : public QObject
{
    Q_OBJECT

public:
    ErrorCoreUNITTest();

private Q_SLOTS:
    void Register();
};

ErrorCoreUNITTest::ErrorCoreUNITTest()
{
}

void ErrorCoreUNITTest::Register()
{
    QVERIFY2(true, "Failure");
}

QTEST_APPLESS_MAIN(ErrorCoreUNITTest)

#include "tst_errorcoreunittest.moc"
