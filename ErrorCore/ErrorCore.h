#ifndef ERRORCORE_H
#define ERRORCORE_H

#include <exception>
#include <QString>
#include <map>
#include <vector>

class ecError : public std::exception
{
public:

    virtual QString message() const = 0;
    ecError(){}
    virtual ~ecError() throw() {}
};


class ecErrorRegister {
public:
    void showError(ecError *e);


private:
    static const QString ErrorLogName;
};

#endif // ERRORCORE_H
