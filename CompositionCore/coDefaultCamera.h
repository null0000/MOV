#ifndef CODEFAULTCAMERA_H
#define CODEFAULTCAMERA_H

#include <QVector2D>
#include <QRect>

#include "coCameraStrategy.h"


/*!
 * \brief The coDefaultCamera class
 *
 *This class represents the "default" camera
 *implementation
 */
template <typename TrackingFunc>
class coDefaultCamera : public coCameraStrategy {
    static const QRect DEFAULT_BOUNDS;

public:
    coDefaultCamera();
    coDefaultCamera(QRect Bounds);

    QVector2D offset() const; //!Returns an offset for all onscreen objects
    void updateOffset(); //!Used to move the camera
    coCameraStrategy *duplicate() const; //!Return a duplicate instance

private:
    QRect cameraBounds;
    const TrackingFunc tracking;
};

#include "coDefaultCamera_tplt.h"

#endif // CODEFAULTCAMERA_H
