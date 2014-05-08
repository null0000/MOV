#ifndef SCPLANTASK_H
#define SCPLANTASK_H

#include <QVector>
#include "scTask.h"

class scPlanTask : public scTask
{
public:
    scPlanTask(const scTaskList &tasks) :
        cur(tasks.begin()), end(tasks.end()){}
    scPlanTask(scTaskList::const_iterator begin, scTaskList::const_iterator end) :
        cur(begin), end(end){}

    scInstrPair nextInstr() const {
        scInstrPair nextPair = cur->nextInstr();
        if (nextPair.first.isNullTask())
            nextPair.first = nextTask();
    }

private:

    scTask nextTask() const {
        scTaskList::const_iterator newItr = cur + 1;
        if (newItr == end)
            return scNullTask::NullTaskS;
        return scPlanTask(cur + 1, end);
    }

    scTaskList::const_iterator cur;
    scTaskList::const_iterator end;
};




#endif // SCPLANTASK_H
