#ifndef SCAIOBJECT_H
#define SCAIOBJECT_H

#include "scObject.h"
#include "scTask.h"

class scTask;
class scInstrDesc;

class scAIObject : public scObject
{
public:
    void Simulate(delta_t timeDelta);

    scAIObject(const scTask &task, QVector2D speedScale);
    QVector2D position() const;

    bool isUsing() const {return false;}

private:
    scInstrPair updateTask(QVector2D moementDelta) const;
    QVector2D getMovement(delta_t time) const;
    QVector2D updatePos(QVector2D movement) const;

    const scInstrDesc &fetchCurInstr() const;
    const scTask *fetchCurTask() const;

    QVector2D curLoc;
    QVector2D speedScale;
    scInstrPair instrPair;
};

#endif // SCAIOBJECT_H
