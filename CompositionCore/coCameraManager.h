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
            QVector2D start (viewingWindow.center());
            QVector2D translation(GetShiftVal(start.x(), viewingWindow.width()/2.0, location().x()), GetShiftVal(start.y(), viewingWindow.height()/2.0, location().y()));
            viewingWindow.translate(translation.x(), translation.y());
        }

        QVector2D operator()() const{
            return QVector2D(-viewingWindow.center().x(), -viewingWindow.center().y());
        }

        T &offsetFunctor() {return location;}

        void bounds(QRect bounds) {
            viewingWindow.setWidth(bounds.width());
            viewingWindow.setHeight(bounds.height());
        }

        coCameraBox(T input) : location(input){}
    private:
        float GetShiftVal(float center, float border, float Tloc) const
        {
            float tDist = std::abs(center - Tloc);
            float mag = tDist - border;

            if (mag > 0)
            {
                return ((center - Tloc) > 0) ? mag : -mag;
            }
            return 0;
        }

        QRect viewingWindow;
        T location;

    };

public:
    coCameraManager(scWorld_p world, scWorld::t_tag Target);

    void pushRenderable(const gcRenderable *newRenderable);

    coCameraManager(scWorld_p world);
    void setTarget(scWorld::t_tag targetTag);
    void setTarget(scWorld_p world, scWorld::t_tag targetTag);
    void bounds(QRect bounds);

    void update(delta_t delta);

    void draw(gcDrawingImpl &impl) const;

private:
    scLocationFunctor &getConfigurableLocation() {return camera.offsetFunctor().offsetFunctor();}

    gcCamera<coCameraBox<scLocationFunctor> > camera;
};



#endif // COCAMERAMANAGER_H
