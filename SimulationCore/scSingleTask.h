#ifndef SCSINGLETASK_H
#define SCSINGLETASK_H

#include "scTask.h"
#include "simulationcore_ie.h"

class SIM_IE scSingleTask : public scPlan {
public:
    scTask generateNextTask(const scObjDesc &, const scWorldDesc &);

    float numTicksToLocation(const QVector2D &startLoc) const;

    scTask firstTask() const;

    std::string dump();

    scPlan *copy() const;

    scSingleTask(const QVector2D &location);
    scSingleTask(const QVector2D &location, const scTask &task);
    scSingleTask();

private:
    scTask oneTask;
    QVector2D location;

};

#endif // SCSINGLETASK_H
