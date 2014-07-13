#ifndef COSCENE_H
#define COSCENE_H


#include <gcRenderable.h>
#include <gcRenderList.h>
#include <gcDrawingImpl.h>

#include <scWorld.h>


template <typename offsetFunctor>
class coScene : public gcRenderable, gcRenderList {

    void draw(gcDrawingImpl &impl) const;

    void pushObj(gcRenderable *Target, scWorld::t_tag lookupTag);



    gcScene(const offsetFunctor &offset, const scWorld_p world);
private:
    const scWorld_p world;

    typedef std::pair<gcRenderable *, scWorld::t_tag> renderPair_t;
    typedef std::vector<renderPair_t> renderList_t;
    renderList_t list;

    const offsetFunctor &cameraOffset;
};


template <typename offsetFunctor>
void coScene<offsetFunctor>::draw(gcDrawingImpl &impl) const {
    QVector2D offset = cameraOffset();
    QTransform tf;
    tf.translate(offset.x(), offset.y());
    impl.PushTransform(tf);
    for (renderList_t::const_iterator cItr = list.begin(); cItr != list.end(); cItr++) {

    }
}

template <typename offsetFunctor>
void coScene<offsetFunctor>::pushObj(gcRenderable *Renderable, scWorld::t_tag lookupTag) {
    list.push_back(renderPair_t(Renderable, lookupTag));
}

template <typename offsetFunctor>
coScene<offsetFunctor>::coScene(const offsetFunctor &offset, const scWorld_p world) :
    cameraOffset(offset){}

#endif // COSCENE_H
