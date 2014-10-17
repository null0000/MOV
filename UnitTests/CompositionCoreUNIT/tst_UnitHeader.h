#ifndef TST_UNITHEADER_H
#define TST_UNITHEADER_H

#include <QObject>

class CompositionCoreUNITTest : public QObject
{
    Q_OBJECT

public:
    CompositionCoreUNITTest();

private Q_SLOTS:
    void chunkTest();
};

#endif // TST_UNITHEADER_H
