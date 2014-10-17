#ifndef SCTASKITERATOR_H
#define SCTASKITERATOR_H

#include "scTask.h"
#include "simulationcore_ie.h"

#include <glbDefinitions.h>

class scPlan;

class SIM_IE scTaskIterator {
public:
    scMovementDesc getMovement(const scObjDesc &curLoctaion)const;
    bool isUsing() const;
    void updateStrategy(const scObjDesc &, const scWorldDesc &);

    float remainingDist(const QVector2D &location) const;

    scTaskIterator(const scPlan &Other);
    scTaskIterator(const scTaskIterator &Other);
    scTaskIterator(point task);
    scTaskIterator();
    ~scTaskIterator();
    scTaskIterator &operator=(const scTaskIterator &Other);
private:
    scPlan *curPlan;
    scTask curTask;

};

#endif // SCTASKITERATOR_H
