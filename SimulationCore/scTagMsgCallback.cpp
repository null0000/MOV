

#include "scTagMsgCallback.h"
#include <sstream>



std::string scTagMsgCallback::msg() const {
    std::stringstream sstream;
    if (name != "")
        sstream << name << ": ";
    sstream << "(" << objTag.objectLoc().x() << ", " << objTag.objectLoc().y() << ")";
    return sstream.str();
}
