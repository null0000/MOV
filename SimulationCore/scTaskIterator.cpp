

#include "scTaskIterator.h"
#include "scMovementDesc.h"
#include "scTask.h"

scTaskIterator::scTaskIterator(const scPlan &Other) :
    curPlan(Other.copy()), curTask(Other.firstTask()){}

scTaskIterator::scTaskIterator(const scTaskIterator &Other) :
    curPlan(Other.curPlan->copy()), curTask(Other.curTask){}
scTaskIterator::~scTaskIterator() {
    delete curPlan;
}

scTaskIterator &scTaskIterator::operator=(const scTaskIterator &Other) {
    if (&Other == this)
        return *this;
    Q_ASSERT(&Other && this);

    delete curPlan;

    curPlan = Other.curPlan->copy();
    curTask = Other.curTask;

    return *this;
}



scMovementDesc scTaskIterator::getMovement(const scObjDesc &curLocation)const {
    return curTask.getMovement(curLocation);
}

bool scTaskIterator::isUsing() const {
    return curTask.isUsing();
}


void scTaskIterator::updateStrategy(const scObjDesc &thisObj, const scWorldDesc & thisWorldDesc) {
    if (curTask.needsUpdate(thisObj))
        curTask = curPlan->generateNextTask(thisObj, thisWorldDesc);
}
