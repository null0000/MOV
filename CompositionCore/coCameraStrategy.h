#ifndef COCAMERASTRATEGY_H
#define COCAMERASTRATEGY_H


/*!
 * \brief The coCameraStrategy class
 *
 *Cameras in this codebase refer to how the offset
 *is determined. It may later decide how objects are displayed
 *onscreen, but not now (this would requisite a change from QVector2D
 *return type to QTransform).
 *
 *This is used in conjunction with coWorld to decide
 *how the camera is controlled. It's used
 *as a strategy class, allowing camera types
 *to be hotswapped.
 */
class coCameraStrategy {
public:
    virtual QVector2D offset() const = 0; //!Returns an offset for all onscreen objects
    virtual coCameraStrategy *duplicate() const = 0; //!Return a duplicate instance
    virtual ~coCameraStrategy(){}
};



#endif // COCAMERASTRATEGY_H
