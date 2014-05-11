#ifndef SCTASK_H
#define SCTASK_H

#include <QPair>
#include <QVector>
#include "scInstr.h"

typedef QPair<const scTask *, scInstrDesc> scInstrPair;

class scTask
{
public:
    virtual ~scTask(){}
    virtual scInstrPair nextInstr() const = 0;
    virtual bool isNullTask() const {return false;}
};

class scNullTask : public scTask
{
public:
    static const scNullTask NullTaskS;

    scInstrPair nextInstr() const;
    bool isNullTask() const {return true;}
};


typedef const QVector<const scTask *> scTaskList;

#endif // SCTASK_H
