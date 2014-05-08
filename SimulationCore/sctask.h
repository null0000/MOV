#ifndef SCTASK_H
#define SCTASK_H

#include <QPair>
#include <QVector>
#include "scInstr.h"

typedef QPair<const scTask &, scInstrDesc> scInstrPair;

class scTask
{
public:
    virtual ~scTask(){}
    scInstrPair nextInstr() const = 0;
    virtual bool isNullTask() const {return false;}
};

class scNullTask
{
public:
    static const scNulltask NullTaskS = scNullTask();

    scInstrPair nextInstr() const {return scInstrPair(*this, scInstr(1, 1));}
    bool isNullTask() const {return true;}
};


typedef const QVector<const scTask *> scTaskList;

#endif // SCTASK_H
