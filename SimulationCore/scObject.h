#ifndef SCOBJECT_H
#define SCOBJECT_H

#include "scKeyboardInput.h"
#include "sckeyboardcontrolledobj.h"
class scTask;
class scKeyboardControlledObj;

typedef float delta_t;

const float TIME_CONVERSION_DIVISOR = 1000;
delta_t timeDeltaFromMilli(int milliseconds);


class scControlScheme {
public:
    QVector2D GetMovement(delta_t timeDelta) const;
    virtual ~scControlScheme(){}
};

class scObject {
public:
    virtual void Simulate(delta_t timeDelta) = 0;
    virtual bool isUsing() const = 0;
    virtual QVector2D position() const = 0;
    virtual ~scObject(){}
};

#endif // SCOBJECT_H
