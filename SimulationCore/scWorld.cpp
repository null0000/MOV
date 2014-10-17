
#include "simulationcore.h"
#include <QMap>
#include <QKeyEvent>
#include <ErrorCore.h>
#include "scMovementDesc.h"
#include "scWorldDesc.h"

const scWorld::t_tag scWorld::NULL_TAG = t_tag((TypeTag) -1, -1);

delta_t timeDeltaFromMilli(int milliseconds) {return ((float)(milliseconds))/TIME_CONVERSION_DIVISOR;}



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

    std::for_each(simulationSteps.begin(), simulationSteps.end(),
                  [&](scSimulationStep_p Step) {Step->runStep(*this, chunkManager, timeDelta);});
}


void scWorld::registerSimulationStep(scSimulationStep_p newStep) {
    simulationSteps.push_back(newStep);
}

scWorld::t_tag scWorld::addObject(const scKeyboardControlledObj &obj) {
    return t_tag(KeyboardTag, keyboardWorld.addObject(obj));
}

scWorld::t_tag scWorld::addObject(const scTaskIterator &obj) {
    return t_tag(TaskTag, taskWorld.addObject(obj));
}

const scObjDesc &scWorld::objInfo(t_tag tag) const {
    switch (tag.first) {
        case KeyboardTag:
            return keyboardWorld.objInfo(tag.second);
        case TaskTag:
            return taskWorld.objInfo(tag.second);
    }
    Q_ASSERT(false);
    return scObjDesc::NULL_DESC;
}

void scWorld::removeResources(t_tag obj, resource_type amount) {
    switch(obj.first) {
    case KeyboardTag:
        keyboardWorld.removeResources(obj.second, amount);
        break;
    case TaskTag:
        taskWorld.removeResources(obj.second, amount);
        break;
    }
}



void scWorld::genChunks(point Location, measure_type radius) {
    chunkManager.genChunks(Location, radius);
}
