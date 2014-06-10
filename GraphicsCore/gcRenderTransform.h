#ifndef GCRENDERTRANSFORM_H
#define GCRENDERTRANSFORM_H

#include "graphicscore_ie.h"

#include <QVector2D>
#include "gcRenderable.h"
#include "gcDrawingImpl.h"
#include <QTransform>
template <typename offsetFunctor, typename renderObjType>
class gcRenderOffset : public gcRenderable{
    const renderObjType renderObj;
    const offsetFunctor offsetFunc;
public:
    gcRenderOffset(renderObjType renderable, offsetFunctor functor) :
        renderObj(renderable), offsetFunc(functor){}

    void draw(gcDrawingImpl &impl) const
    {
        QTransform transform;
        QVector2D translation = offsetFunc();
        transform.translate(translation.x(), translation.y());
        impl.PushTransform(transform);
        renderObj.draw(impl);
        impl.PopTransform();
    }

};

#endif // GCRENDERTRANSFORM_H
