#ifndef ECIOERRORS_H
#define ECIOERRORS_H

#include "ErrorCore.h"

class ecCdError : public ecError{
private:
    QString dir;

public:
    QString message() const {return "Failed to change directories to: " + dir;}
    ecCdError(QString dir) : dir(dir){}
    ~ecCdError() throw(){}
};

class ecProcessError : public ecError {
    QString name;
public:
    ecProcessError(QString errorName) : name(errorName){}
    QString message() const {return "Process threw error with type: " + name;}
    ~ecProcessError() throw(){}
};


#endif // ECIOERRORS_H
