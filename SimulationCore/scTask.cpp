


#include "scTask.h"

const scNullTask scNullTask::NullTaskS = scNullTask();
scInstrPair scNullTask::nextInstr() const
{
    return scInstrPair(this, scInstrDesc());
}
