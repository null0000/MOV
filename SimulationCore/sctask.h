#ifndef SCTASK_H
#define SCTASK_H


#include <string>
#include <QPair>
#include <QVector>
#include <QVector2D>
#include "simulationcore_ie.h"
class scWorldDesc;
class scObjDesc;
class scMovementDesc;



class SIM_IE scTask {

    inline float maxMagnitude(const QVector2D &curLoc) const;
public:
    scTask(const scObjDesc &objDesc);
    scTask(const QVector2D &targetLoc);
    scTask(const QVector2D &targetLoc, bool useTask);
    scTask();

    scMovementDesc getMovement(const scObjDesc &curLoc) const;
    bool isUsing() const;

    bool needsUpdate(const scObjDesc &curLoc) const;

    bool isNullTask() const;

    std::string dump() const;

private:
    bool shouldUse;
    bool isNull;
    QVector2D targetLoc;
};

class SIM_IE scPlan {
public:
    //should return NULL if no next Task
    virtual scTask generateNextTask(const scObjDesc &thisObj,
                                    const scWorldDesc &visibleWorldDesc) = 0;
    virtual scTask firstTask() const = 0;

    virtual scPlan *copy() const = 0;
    virtual ~scPlan(){}
};

#endif // SCTASK_H
