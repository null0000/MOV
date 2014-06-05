#include <QString>
#include <QtTest>
#include <ErrorCore.h>
#include <QPushButton>
#include "ecErrorDialog.h"
#include <stdlib.h>


class testErrorRegister : public QObject
{
    Q_OBJECT

public:
    testErrorRegister();

private Q_SLOTS:
    void RegisterTests();
};

testErrorRegister::testErrorRegister()
{
}

class testError : public ecError
{
public:
    QString testMessage;
    static int errorCount;
    testError(QString testMessage) : testMessage(testMessage){}
    testError() {testMessage = "Error Number" + QString::number(errorCount++);}
    virtual QString message() const {return testMessage;}
    ~testError() throw(){}
};

int testError::errorCount = 0;

template <typename T>
void remove_at(std::vector<T>& v, typename std::vector<T>::size_type n)
{
    std::swap(v[n], v.back());
    v.pop_back();
}

void testErrorRegister::RegisterTests()
{

    std::vector<testError *> testErrorVec;
    for (int i = 0; i < 50; i++)
        testErrorVec.push_back(new testError());


    testErrorVec.push_back(new testError("Fuck"));
    testErrorVec.push_back(new testError("Shits fucked up"));
    testErrorVec.push_back(new testError("Errorstuff"));

    std::vector<testError *>::iterator itr = testErrorVec.begin();
    std::vector<ecErrorDialog *> dialog;
    int count = 0;
    for(; itr != testErrorVec.end(); itr++) {
        dialog.push_back(ecErrorRegister::showError(*itr));
        count += 1;
        QCOMPARE(count, ecErrorRegister::outstandingErrorCount());
    }

    while (dialog.size() > 0) {
        int index = rand()%count;
        ecErrorDialog *cur = dialog[index];
        remove_at<ecErrorDialog *>(dialog, index);
        QTest::mouseClick(cur->__getPushButton(), Qt::LeftButton);
        count--;
        QCOMPARE(count, ecErrorRegister::outstandingErrorCount());
    }

}

QTEST_MAIN(testErrorRegister)

#include "tst_errorcoreunit.moc"
