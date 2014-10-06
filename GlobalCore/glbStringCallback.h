#ifndef GLBSTRINGCALLBACK_H
#define GLBSTRINGCALLBACK_H

#include <string>
#include <QSharedPointer>

class glbStringCallback
{
public:
    virtual ~glbStringCallback(){}
    virtual std::string msg() const = 0;
};


typedef QSharedPointer<glbStringCallback> glbStringCallback_p;

#endif // GLBSTRINGCALLBACK_H
