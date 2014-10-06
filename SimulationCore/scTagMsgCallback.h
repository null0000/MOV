#ifndef SCTAGMSGCALLBACK_H
#define SCTAGMSGCALLBACK_H

#include <glbStringCallback.h>
#include "scFullTag.h"
#include "simulationcore_ie.h"

#include <string>

class SIM_IE scTagMsgCallback : public glbStringCallback {
public:
    virtual std::string msg() const;

    scTagMsgCallback(scFullTag tag) : objTag(tag), name(""){}
    scTagMsgCallback(std::string name, scFullTag tag) : objTag(tag), name (name){}


private:
    scFullTag objTag;
    std::string name;


};


#endif // SCTAGMSGCALLBACK_H
