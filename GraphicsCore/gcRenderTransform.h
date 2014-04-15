#ifndef GCRENDERTRANSFORM_H
#define GCRENDERTRANSFORM_H

#include <QVector2D>
#include "gcRenderable.h"
#include "gcDrawingImpl.h"
#include <QTransform>
template <typename offsetFunctor>
class gcRenderOffset : public gcRenderable{
    const gcRenderable &renderObj;
    const offsetFunctor offsetFunc;
public:
    gcRenderOffset(gcRenderable &renderable, offsetFunctor functor) :
        renderObj(renderable), offsetFunc(functor){}

    void draw(gcDrawingImpl &impl) const
    {
        QTransform transform;
        QVector2D translation = offsetFunc();
        transform.translate(translation.x(), translation.y());
        impl.PushTransform(transform);
        renderObj.draw(impl);
    }

};

#endif // GCRENDERTRANSFORM_H
