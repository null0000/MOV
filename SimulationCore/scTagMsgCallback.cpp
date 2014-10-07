

#include "scTagMsgCallback.h"
#include <sstream>



std::string scTagMsgCallback::msg() const {
    std::stringstream sstream;
    if (name != "")
        sstream << name << ": ";
    sstream << objTag.objInfo();
    return sstream.str();
}
