#ifndef SCTASKITERATOR_H
#define SCTASKITERATOR_H

#include "scTask.h"
#include "simulationcore_ie.h"

class scPlan;

class SIM_IE scTaskIterator {
public:
    scMovementDesc getMovement(const scObjDesc &curLoctaion)const;
    bool isUsing() const;
    void updateStrategy(const scObjDesc &, const scWorldDesc &);

    scTaskIterator(const scPlan &Other);
    scTaskIterator(const scTaskIterator &Other);
    ~scTaskIterator();
    scTaskIterator &operator=(const scTaskIterator &Other);
private:
    scPlan *curPlan;
    scTask curTask;

};


#endif // SCTASKITERATOR_H
