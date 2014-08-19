#ifndef GCSHAREDOFFSET_TPLT_H
#define GCSHAREDOFFSET_TPLT_H

#include "gcSharedOffset.h"

template<typename OffsetType>
gcSharedOffset<OffsetType>::gcSharedOffset(QSharedPointer<OffsetType> inputOffset) :
    offset(inputOffset) {
    Q_ASSERT(inputOffset);
}

template<typename OffsetType>
QVector2D gcSharedOffset<OffsetType>::operator()(){
    return offset();
}

#endif // GCSHAREDOFFSET_TPLT_H
