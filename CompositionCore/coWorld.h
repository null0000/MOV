#ifndef COWORLD_H
#define COWORLD_H

#include <QVector2D>

#include <compositioncore_ie.h>

#include <scSimulationStep.h>
#include <scWorld.h>


#include <gcRenderList.h>
#include <gcCamera.h>
#include <gcSharedOffset.h>
#include <coCameraStrategy.h>





class CMP_IE coWorld {
    class CMP_IE CameraImpl {
    public:

        template <typename NewStrategyType>
        void swapStrategy(const NewStrategyType &newStrategy);
        QVector2D operator()() const;


        ~CameraImpl();

        CameraImpl();
        bool operator ==(const CameraImpl &Other) const;
        CameraImpl &operator =(const CameraImpl &Other);
        CameraImpl(const CameraImpl &Other);
    private:
        coCameraStrategy *strategy;
    };

public:
    typedef scWorld::t_tag t_tag;

    coWorld(gcRenderList_p renderTarget);

    template <typename GcType, typename scType>
    t_tag addRenderedObject(GcType renderable, scType simulation);

    template <typename GcType>
    void addRenderable(GcType obj);

    void setCameraObj(t_tag targetObject);
    void simulate(delta_t timeDelta);

private:
    scWorld world;
    typedef QSharedPointer<CameraImpl> CameraImpl_p;
    CameraImpl_p cameraImpl;
    gcCamera<gcSharedOffset<CameraImpl> > camera;
    gcRenderList_p renderList;
};

#include "coWorld_tplt.h"

#endif // COWORLD_H
