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


    template <typename RenderableType>
    void pushRenderable(RenderableType renderable) {
        renderableList.push_back(new gcRenderOffset<OffsetFunctor, RenderableType>(offset, renderable));
    }


    void draw(gcDrawingImpl &impl) const {
        for (auto itr = renderableList.begin(); itr != renderableList.end(); itr++)
            (*itr)->draw(impl);
    }

    ~gcCamera() {
        for (auto itr = renderableList.begin(); itr != renderableList.end(); itr++)
            delete *itr;
    }

private:
    OffsetFunctor offset;
    std::vector<gcRenderable *> renderableList;

};

#endif // GCCAMERA_H
