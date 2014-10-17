#ifndef TSTNULLRENDERABLE_H
#define TSTNULLRENDERABLE_H

#include <gcRenderable.h>

class tstNullRenderable : public gcRenderable {
public:
    void draw(gcDrawingImpl &) const{}
    tstNullRenderable() : gcRenderable(){}
};

#endif // TSTNULLRENDERABLE_H
