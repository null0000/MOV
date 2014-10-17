

#include <glbDefinitions.h>

#include "scTaskIterator.h"
#include "scMovementDesc.h"
#include "scTask.h"
#include "scSingleTask.h"


scTaskIterator::scTaskIterator(const scPlan &Other) :
    curPlan(Other.copy()), curTask(Other.firstTask()){}

scTaskIterator::scTaskIterator(const scTaskIterator &Other) :
    curPlan(Other.curPlan->copy()), curTask(Other.curTask){}
scTaskIterator::~scTaskIterator() {
    if (curPlan)
        delete curPlan;
}

scTaskIterator &scTaskIterator::operator=(const scTaskIterator &Other) {
    if (&Other == this)
        return *this;
    Q_ASSERT(&Other && this);

    if (curPlan) //could be null
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


scTaskIterator::scTaskIterator() : curPlan(NULL){}


scTaskIterator::scTaskIterator(point singletask) {
    curPlan = new scSingleTask(singletask);
    curTask = scTask();
}
