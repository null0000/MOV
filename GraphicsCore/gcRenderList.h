#ifndef GCRENDERLIST_H
#define GCRENDERLIST_H

#include <QSharedPointer>

class gcRenderable;

class gcRenderList {
public:
    virtual void pushRenderable(gcRenderable *) = 0;
    virtual ~gcRenderList(){}
};

typedef QSharedPointer<gcRenderList> gcRenderList_p;

#endif // GCRENDERLIST_H
