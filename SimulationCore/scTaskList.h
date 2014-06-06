#ifndef SCTASKLIST_H
#define SCTASKLIST_H


#include <vector>

#include "scTask.h"
#include "simulationcore_ie.h"


class SIM_IE scTaskList {
    typedef std::vector<scTask> taskListImpl_t;

public:
    typedef taskListImpl_t::iterator iterator;
    typedef taskListImpl_t::const_iterator const_iterator;

    iterator begin();
    const_iterator begin() const;

    iterator end();
    const_iterator end() const;

    template <typename IteratorType>
    scTaskList(IteratorType begin, IteratorType end) :
        impl(begin, end){}

    scTaskList();

    std::string dump() const;

private:
        taskListImpl_t impl;
};

#endif // SCTASKLIST_H
