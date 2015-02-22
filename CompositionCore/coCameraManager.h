#ifndef COCAMERAMANAGER_H
#define COCAMERAMANAGER_H

#include <algorithm>

#include <gcRenderList.h>
#include <gcCamera.h>
#include <gcSharedOffset.h>

class gcDrawingImpl;

#include <scWorld.h>
#include <scLocationFunctor.h>

#include "compositioncore_ie.h"


/*!
 * \brief The coCameraManager class
 *
 *This manages the camera, conveniently covering up a few different abstractions
 *and allowing the user to swap camera strategies in and out, and allowing the
 *
 */
class CMP_IE coCameraManager {
    typedef enum {nullE, trackingE} CameraStateEnum;

    template <typename T>
    class coCameraBox
    {
    public:
        void update() {
            QVector2D start (cameraBounds.center());
            QVector2D translation(GetShiftVal(start.x(), cameraBounds.width()/2.0, location().x()), GetShiftVal(start.y(), cameraBounds.height()/2.0, location().y()));
            cameraBounds.translate(translation.x(), translation.y());
        }

        QVector2D operator()() const{
            QVector2D vwCenter (viewingWindow.center());
            QVector2D cbCenter (cameraBounds.center());
            return QVector2D(vwCenter.x() - cbCenter.x(),
                             vwCenter.y() - cbCenter.y());
        }

        T &offsetFunctor() {return location;}

        void setCameraBounds(QRect bounds) {
            cameraBounds.setWidth(bounds.width());
            cameraBounds.setHeight(bounds.height());
        }

        void viewingWindowBounds(QRect window) {
            viewingWindow = window;
        }

        coCameraBox(T input, QRect cameraBounds, QRect viewingWindow) :
            location(input), cameraBounds(cameraBounds), viewingWindow(viewingWindow){}
    private:
        float GetShiftVal(float center, float border, float Tloc) const
        {
            float tDist = std::abs(center - Tloc);
            float mag = tDist - border;

            if (mag > 0)
                return ((center - Tloc) > 0) ? -mag : mag;
            return 0;
        }

        T location;
        QRect cameraBounds;
        QRect viewingWindow;

    };

public:
    void pushRenderable(const gcRenderable *newRenderable);

    coCameraManager(scWorld_p world, scWorld::t_tag Target, QRect CameraBounds, QRect WorldBounds);
    coCameraManager(scWorld_p world, QRect CameraBounds, QRect WorldBounds);
    void setTarget(scWorld::t_tag targetTag);
    void setTarget(scWorld_p world, scWorld::t_tag targetTag);
    void bounds(QRect bounds);
    point curOffset () const;

    void update(delta_t delta);

    void draw(gcDrawingImpl &impl) const;

private:
    scLocationFunctor &getConfigurableLocation() {return camera.offsetFunctor().offsetFunctor();}

    gcCamera<coCameraBox<scLocationFunctor> > camera;
};



#endif // COCAMERAMANAGER_H
