#ifndef GCRENDERABLE_H
#define GCRENDERABLE_H

#include "graphicscore_ie.h"

class gcDrawingImpl;

class GFX_IE gcRenderable{
public:
    virtual void draw(gcDrawingImpl &impl) const = 0;
    virtual ~gcRenderable(){}
};

#endif // GCRENDERABLE_H
