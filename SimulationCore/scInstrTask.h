#ifndef SCINSTRTASK_H
#define SCINSTRTASK_H

#include "scTask.h"

class scInstrTask : public scTask {

public:
    scInstrTask (scInstrDesc desc) :
        desc(desc){}

    scInstrPair nextInstr() const {return scInstrPair(&scNullTask::NullTaskS, desc);}

private:
    scInstrDesc desc;
};

#endif // SCINSTRTASK_H
