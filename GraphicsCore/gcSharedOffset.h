#ifndef GCSHAREDOFFSET_H
#define GCSHAREDOFFSET_H

#include <QSharedPointer>

template <typename OffsetType>
class gcSharedOffset {
public:
    gcSharedOffset(QSharedPointer<OffsetType> offest);
    QVector2D operator()();

private:
    QSharedPointer<OffsetType> offset;
};


#include "gcSharedOffset_tplt.h"

#endif // GCSHAREDOFFSET_H
