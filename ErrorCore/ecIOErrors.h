#ifndef ECIOERRORS_H
#define ECIOERRORS_H

#include "ErrorCore.h"
#include "errorcore_ie.h"

#include <QString>

class ERR_IE ecCdError : public ecError{
private:
    QString dir;

public:
    QString message() const {return "Failed to change directories to: " + dir;}
    ecCdError(QString dir);
    ~ecCdError() throw(){}
};

class ERR_IE ecProcessError : public ecError {
    QString name;
public:
    ecProcessError(QString errorName) : name(errorName){}
    QString message() const {return "Process threw error with type: " + name;}
    ~ecProcessError() throw(){}
};


#endif // ECIOERRORS_H
