
#include "scListPlan.h"
#include "scObjDesc.h"
#include "scWorldDesc.h"

scTask scListPlan::generateNextTask(const scObjDesc &/*thisObj*/,
                        const scWorldDesc &/*visibleWorldDesc*/) {
    cur++;
    return *cur;
}

scTask scListPlan::firstTask() const {return *cur;}

scPlan *scListPlan::copy() const {return new scListPlan(cur, end);}



scListPlan::scListPlan(const scTaskList &list) :
    cur(list.begin()), end(list.end()){}

scListPlan::scListPlan(scTaskList::const_iterator begin,
           scTaskList::const_iterator end) :
    cur(begin), end(end){}
