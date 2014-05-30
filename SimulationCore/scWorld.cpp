
#include "simulationcore.h"
#include <QMap>
#include <QKeyEvent>
#include <ErrorCore.h>
#include "scMovementDesc.h"
#include "scWorldDesc.h"


template<typename planType>
void scSubWorld<planType>::simulate(delta_t timeDelta) {
    for (typename objlist_t::iterator itr = objList.begin(); itr != objList.end(); itr++) {
        scMovementDesc moveDesc = itr->second.getMovement(itr->first);
        moveDesc.applyScale(timeDelta);
        itr->first.moveAmount(moveDesc.maxMovement());
        itr->second.updateStrategy(itr->first, scWorldDesc());
    }
}
delta_t timeDeltaFromMilli(int milliseconds) {return ((float)(milliseconds))/TIME_CONVERSION_DIVISOR;}


class badTagError : public ecError {
public:
    QString message() const {return "Bad tag used to lookup object";}
};

template <typename planType>
QVector2D scSubWorld<planType>::lookup(t_tag tag) const {
    if (objList.size() > tag)
        objList[tag].first.location();

    throw badTagError();
}


class ecBadSimulatable : public ecError {

public:
    QString message() const {return "Error resolving object position due to bad world type";}
};

//we don't want to die here in production, but... you know, something bad happened.
QVector2D scBaseWorld::lookup(t_tag) const {Q_ASSERT(false); throw ecBadSimulatable();}

QVector2D scWorld::lookupObject(t_tag tag) const {
    switch(tag.first)
    {
        case KeyboardTag: return keyboardWorld.lookup(tag.second);
        case TaskTag: return taskWorld.lookup(tag.second);
    }
    throw ecSwitchError(tag.first);
}

/*
 *These are some macros used to debug simulate.
 *
 *
 */
#ifdef QT_DEBUG
#define DEFINE_TYPETAG unsigned int typeTagCount = 0
#define SIMULATE_SUB_WORLD(x, timeDelta) x.simulate(timeDelta); typeTagCount++
#define CHECK_TYPETAG Q_ASSERT(typeTagCount == TypeTagCountS) //did you run the correct # of simulates?

#else

#define DEFINE_TYPETAG
#define SIMULATE_SUB_WORLD(x, timeDelta) x.simulate(timeDelta)
#define CHECK_TYPETAG

#endif

#ifdef QT_DEBUG
#endif

/**
 * @brief scWorld::simulate
 * @param timeDelta - amount of time that's passed
 *
 *  This will simulate all sub worlds, as well as do any
 *other meta-world work required which needs work between
 *the different object types.
 *
 *It checks to make sure that all worlds are accounted
 *for automatically during debug, while ignoring that
 *during production code (probably not needed due to optimization,
 *but it makes me feel better so shut up.)
 */
void scWorld::simulate(delta_t timeDelta) {
    DEFINE_TYPETAG;

    SIMULATE_SUB_WORLD(keyboardWorld, timeDelta);
    SIMULATE_SUB_WORLD(taskWorld, timeDelta);

    CHECK_TYPETAG;
}


template <>
scWorld::t_tag scWorld::addObject(const scKeyboardControlledObj &obj) {
    return scWorld::t_tag(KeyboardTag, keyboardWorld.addObject(obj));
}

template<>
scWorld::t_tag scWorld::addObject(const scTask &obj) {
    return t_tag(TaskTag, taskWorld.addObject(obj));
}
