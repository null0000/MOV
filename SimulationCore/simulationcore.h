#ifndef SIMULATIONCORE_H
#define SIMULATIONCORE_H

#include <QtGlobal>
#include <utility>
#include <QWindow>
#include <qvector2d.h>
#include <simulationcore.h>
#include "scKeyboardInput.h"

typedef float delta_t;

/**
 * @brief The scInputDevice class
 *
 * This class acts as an input device which
 *  Operates in the language of the simulation
 *  core. In other words, This is expected
 *  to be passed to anything which deals with
 *  user input.
 *
 *
 */
class scSimulatable {

public:
    virtual void Simulate(delta_t timeDelta) = 0;
    virtual ~scSimulatable(){}
};

class scSim_d
{
public:
    typedef enum {KeyControlledE} controlType;

    QSharedPointer<scSimulatable> instantiate();

    scSim_d(controlType controller) :
        startLocation(0, 0), speedScale(1, 1), controller(controller){}

private:
    QVector2D startLocation;
    QVector2D speedScale;
    controlType controller;
};

class scControlScheme {
public:
    virtual QVector2D position() const = 0;

    virtual ~scControlScheme(){}
};


const float TIME_CONVERSION_DIVISOR = 1000;
delta_t timeDeltaFromMilli(int milliseconds);


class scObject : public scControlScheme, public scSimulatable
{
public:
    virtual ~scObject(){}    
};

class scWorld {
public:
    typedef int t_tag;

    t_tag addObject(scObject &newObj);
    const scObject &lookup(t_tag tag) const {return *simVec[tag];}
    void simulate(delta_t timeDelta);

private:
    QVector<scObject *> simVec;
};


scObject *scCreateKeyboardObject(scInputDevice *input, const QVector2D startOffset, QVector2D speedScale);


#endif // SIMULATIONCORE_H
