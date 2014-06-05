#ifndef ERRORCORE_H
#define ERRORCORE_H

#include <exception>
#include <QString>
#include <QDataStream>
#include <map>
#include <vector>

#include "errorcore_ie.h"

class ecErrorDialog;

class ERR_IE ecError : public std::exception
{
public:
    virtual QString message() const = 0;
    ecError(){}
    virtual ~ecError() throw() {}
};


class ERR_IE ecErrorRegister {
public:
    static ecErrorDialog *showError(ecError *e);

    static QDataStream *debugStreamRead();
    static QDataStream *debugStreamWrite();

    static int outstandingErrorCount();

private:
    static void openDebugFileRead();
    static void openDebugFileWrite();


    static QSet<ecErrorDialog *> errorSet;
    static const QString ErrorLogName;
};

class ERR_IE ecSwitchError : public ecError {
public:

    ecSwitchError(int typeNum) : typeNum(typeNum) {}
    QString message() const {return "Found invalid type in switch statement: " + typeNum;}

private:
    int typeNum;

};

#endif // ERRORCORE_H
