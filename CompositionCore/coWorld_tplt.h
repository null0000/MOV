#ifndef COWORLD_TPLT_H
#define COWORLD_TPLT_H


#include <coWorld.h>


template<typename gcType, typename scType>
coWorld::t_tag coWorld::addRenderedObject(gcType gcObj, scType scObj) {
    renderList->pushRenderable(gcObj);
    return world.addObject(scObj);
}

template<typename gcType>
void coWorld::addRenderable(gcType obj) {
    renderList->pushRenderable(obj);
}




#endif // COWORLD_TPLT_H
