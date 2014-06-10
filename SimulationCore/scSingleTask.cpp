
#include "scSingleTask.h"
#include "scWorldDesc.h"
#include "scObjDesc.h"
#include "scTask.h"

#include <QVector2D>
#include <string>
#include <glbTranslate.h>

scTask scSingleTask::generateNextTask(const scObjDesc &,
                        const scWorldDesc &) {
    return scTask();
}

float scSingleTask::numTicksToLocation(const QVector2D &startLoc) const {
    return (startLoc - location).length();
}

scTask scSingleTask::firstTask() const {return oneTask;}

std::string scSingleTask::dump() {
    std::string taskStr = oneTask.dump();
    return std::string("Task: ") + taskStr +
           std::string(" with a target location of: ") +
           vec2str(location);
}

scSingleTask::scSingleTask(const QVector2D &location) :
    oneTask(location), location(location){}
scSingleTask::scSingleTask(const QVector2D &location, const scTask &task) :
    oneTask(task), location(location){}

scSingleTask::scSingleTask() :
    oneTask(), location(0, 0){}

scPlan *scSingleTask::copy() const {
    return new scSingleTask(location);
}
