
#include "scTaskList.h"
#include <sstream>

scTaskList::iterator scTaskList::begin() {return impl.begin();}
scTaskList::const_iterator scTaskList::begin() const {return impl.begin();}

scTaskList::iterator scTaskList::end() {return impl.end();}
scTaskList::const_iterator scTaskList::end() const {return impl.end();}

std::string scTaskList::dump() const {
    std::stringstream sstream;
    for (const_iterator cItr = begin(); cItr != end(); cItr++) {
        sstream << cItr->dump() << std::endl;
    }

    return sstream.str();
}
