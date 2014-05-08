#ifndef SCAIOBJECT_H
#define SCAIOBJECT_H

#include "scObject.h"
#include "scTask.h"

class scTask;
class scInstrDesc;

class scAIObject : scObject
{
public:
    void Simulate(delta_t timeDelta);

    scAIObject(const scTask &task, QVector2D speedScale) :
        curLoc(0, 0), speedScale(1, 1), task (&task), speedScale(speedScale){}



private:
    const scTask *updateTask() const;
    QVector2D getMovement(delta_t time) const;
    QVector2D updatePos(QVector2D movement) const;

    const scInstrDesc &fetchCurInstr() const;
    const scTask &fetchCurTask() const;

    QVector2D curLoc;
    QVector2D speedScale;
    scInstrPair instrPair;
};

#endif // SCAIOBJECT_H
