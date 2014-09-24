#ifndef GCCAMERA_H
#define GCCAMERA_H

#include "graphicscore_ie.h"

#include "gcRenderable.h"
#include "gcRenderTransform.h"

template <typename OffsetFunctor>
class gcCamera : public gcRenderable {


public:
    gcCamera (OffsetFunctor offset) :
        offset(offset){}

    void pushRenderable(const gcRenderable *renderable) {
        renderableList.push_back(renderable);
    }


    void draw(gcDrawingImpl &impl) const {
        QVector2D translation (offset());
        QTransform transform;
        transform.translate(-translation.x(), -translation.y());
        impl.PushTransform(transform);

        for (auto itr = renderableList.begin(); itr != renderableList.end(); itr++)
            (*itr)->draw(impl);

        impl.PopTransform();
    }



    ~gcCamera() {
        for (auto itr = renderableList.begin(); itr != renderableList.end(); itr++)
            delete *itr;
    }

    OffsetFunctor &offsetFunctor() {return offset;}

private:
    OffsetFunctor offset;
    std::vector<const gcRenderable *> renderableList;

};

#endif // GCCAMERA_H
