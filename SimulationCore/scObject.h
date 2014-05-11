#ifndef SCOBJECT_H
#define SCOBJECT_H

#include "scUseListener.h"
#include "scKeyboardInput.h"
class scTask;

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


class scObject_d
{
public:
    virtual scObject *instantiate() const = 0;
    ~scObject_d(){}
};


class scKeyboardObject_d : public scObject_d
{
public:
    scObject *instantiate() const;

    scKeyboardObject_d(scKeyboardMap_ccp kmap, scKeyboardState_ccp kstate,
                       QVector2D startLocation = QVector2D(0, 0),
                       QVector2D speedScale = QVector2D(.25, .25),
                       scUseListener listener = scUseListener()) :
        startLocation(startLocation), speedScale(speedScale),
        kmap(kmap), kstate(kstate), listener(listener){}
private:
    QVector2D startLocation;
    QVector2D speedScale;
    scKeyboardMap_ccp kmap;
    scKeyboardState_ccp kstate;
    scUseListener listener;

    scObject *InstantiateKeyboardObj() const;
};

class scAIObject_d : public scObject_d
{
public:
    scAIObject_d(const scTask &task) :
        task(task){}

    scObject *instantiate() const;
private:
    const scTask &task;

};


#endif // SCOBJECT_H
