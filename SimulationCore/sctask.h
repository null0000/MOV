#ifndef SCTASK_H
#define SCTASK_H

#include <QPair>
#include <QVector>
#include <QVector2D>
class scWorldDesc;
class scObjDesc;
class scMovementDesc;



class scTask {

    static scTask NullTaskS;

    inline float maxMagnitude(const QVector2D &curLoc) const;
public:
    scTask(const scObjDesc &objDesc);
    scTask();

    void updateStrategy(const scObjDesc &loc, const scWorldDesc &desc);
    scMovementDesc getMovement(const scObjDesc &curLoc) const;
    bool isUsing() const;

    bool isNullTask() const;

private:
    bool shouldUse;
    QVector2D targetLoc;
};

class scPlan {
public:
    //should return NULL if no next Task
    virtual scTask generateNextTask(const scObjDesc &thisObj,
                                    const scWorldDesc &visibleWorldDesc) = 0;
};

class scTaskIterator {

public:
    scMovementDesc calcMovement(const QVector2D curLoctaion)const;
    bool isUsing() const;

};

typedef const QVector<const scTask *> scTaskList;

#endif // SCTASK_H
