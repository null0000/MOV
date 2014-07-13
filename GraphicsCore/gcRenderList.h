#ifndef GCRENDERLIST_H
#define GCRENDERLIST_H

#include "graphicscore_ie.h"

class gcRenderable;

class gcRenderList {
public:
    virtual void pushRenderable(gcRenderable *) = 0;
    virtual ~gcRenderList(){}
};

typedef gcRenderList * gcRenderList_p;

#endif // GCRENDERLIST_H
