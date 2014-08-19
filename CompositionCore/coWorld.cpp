


#include <coWorld.h>
#include <scWorld.h>


class NullOffset : public coCameraStrategy {
    QVector2D offset() const {return QVector2D(0,0);}
    virtual coCameraStrategy *duplicate() const {
        return new NullOffset();
    }
};

coWorld::CameraImpl::CameraImpl() :
    strategy(new NullOffset()){}


coWorld::coWorld(gcRenderList_p list) :
    cameraImpl(new CameraImpl()),
    camera(gcSharedOffset<CameraImpl>(cameraImpl)), renderList(list) {
    Q_ASSERT(renderList);
}

void coWorld::simulate(delta_t timeDelta) {
    world.simulate(timeDelta);
}


coWorld::CameraImpl &coWorld::CameraImpl::operator =(const CameraImpl &Other) {
    Q_ASSERT(strategy);
    if ((*this == Other))
        return *this;
    delete strategy;
    strategy = Other.strategy->duplicate();
    return *this;
}

coWorld::CameraImpl::~CameraImpl() {
    delete strategy;
}

coWorld::CameraImpl::CameraImpl(const CameraImpl &Other) :
    strategy(Other.strategy->duplicate()) {
    Q_ASSERT(strategy);
}


bool coWorld::CameraImpl::operator ==(const CameraImpl &Other) const {
    if (this == &Other)
        return true;
    Q_ASSERT(this && &Other);

    return strategy == Other.strategy;
}

