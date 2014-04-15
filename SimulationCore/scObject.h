#ifndef SCOBJECT_H
#define SCOBJECT_H

#include "scKeyboardInput.h"

typedef float delta_t;
const float TIME_CONVERSION_DIVISOR = 1000;
delta_t timeDeltaFromMilli(int milliseconds);

class scSimulatable {

public:
    virtual void Simulate(delta_t timeDelta) = 0;
    virtual ~scSimulatable(){}
};

class scControlScheme {
public:
    virtual QVector2D position() const = 0;

    virtual ~scControlScheme(){}
};




class scObject : public scControlScheme, public scSimulatable {
public:
    virtual ~scObject(){}
};

class scObject_d
{
public:
    typedef enum {KeyControlledE} controlType;

    scObject *instantiate() const;

    scObject_d(scKeyboardMap_ccp kmap, scKeyboardState_ccp kstate, QVector2D startLocation = QVector2D(0, 0),  QVector2D speedScale = QVector2D(.25, .25)) :
        startLocation(startLocation), speedScale(speedScale), controller(KeyControlledE), kmap(kmap), kstate(kstate){}

private:
    QVector2D startLocation;
    QVector2D speedScale;
    controlType controller;
    scKeyboardMap_ccp kmap;
    scKeyboardState_ccp kstate;

    scObject *InstantiateKeyboardObj() const;
};

#endif // SCOBJECT_H
