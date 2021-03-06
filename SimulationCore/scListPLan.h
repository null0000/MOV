#ifndef SCLISTPLAN_H
#define SCLISTPLAN_H

#include "scTask.h"
#include "scTaskList.h"
#include "simulationcore_ie.h"

class SIM_IE scListPlan : public scPlan {
public :
    scTask generateNextTask(const scObjDesc &thisObj,
                            const scWorldDesc &visibleWorldDesc);
    scTask firstTask() const;

    scPlan *copy() const;

    scListPlan(const scTaskList &list);
    scListPlan(scTaskList::const_iterator begin,
               scTaskList::const_iterator end);
    scListPlan();

private:
    scTaskList::const_iterator cur;
    scTaskList::const_iterator end;
};


#endif // SCLISTPLAN_H
