#ifndef COCHUNKRENDERER_H
#define COCHUNKRENDERER_H

#include <gcRenderable.h>
#include <gcDrawingImpl.h>
#include <gcImage.h>

#include <scWorld.h>
#include <scChunkDescription.h>
#include <scResourceDeposit.h>

#include <coWorld.h>

template <typename offset_f>
class coChunkRenderer : public gcRenderable{
public:
    void draw(gcDrawingImpl &impl) const;

    coChunkRenderer(coWorld_cp world, gcImage resourcePic, offset_f off);

    void setOffsetFunctor(offset_f off);

private:
    struct drawChunk_f;
    coWorld_cp world;
    gcImage resourceImage;
    offset_f getOffset;
};

template <typename offset_f>
void coChunkRenderer<offset_f>::draw(gcDrawingImpl &impl) const {
    auto drawChunk = [&](coWorld::const_chunk_description cd) {
        std::for_each(cd.beginDeposits(), cd.endDeposits(), [&](scResourceDeposit rd) {
            QTransform t;
            t.translate(rd.location().x(), rd.location().y());
            impl.PushTransform(t);
            impl.Draw(resourceImage);
        });
    };
    QRect geometry (impl.screenGeometry());
    measure_type radius = std::max(geometry.width(), geometry.height())/2.0;
    world->chunkCallback(getOffset(), radius, drawChunk);
}

template <typename offset_f>
coChunkRenderer<offset_f>::coChunkRenderer(coWorld_cp world, gcImage resourcePic, offset_f off) :
    world(world), resourceImage(resourcePic), getOffset(off) {}

template <typename offset_f>
void coChunkRenderer<offset_f>::setOffsetFunctor(offset_f off) {
    getOffset = off;
}

#endif // COCHUNKRENDERER_H
