#ifndef SCCHUNK_H
#define SCCHUNK_H

#include <vector>
#include <QVector2D>

#include "scResourceDeposit.h"

#include "simulationcore_ie.h"

class SIM_IE scChunk {
public:
    typedef scResourceDeposit deposit_type;
    typedef std::list<deposit_type> deposit_list;
    typedef deposit_list::iterator deposit_iterator;
    typedef deposit_list::const_iterator const_deposit_iterator;
    typedef QVector2D point;
    typedef float coord_type;

    coord_type x() const{return loc.x();}
    coord_type y() const{return loc.y();}

    point location() const{return loc;}

    template<typename deposit_iterator_type>
    scChunk(point loc, deposit_iterator_type depositsBegin, deposit_iterator_type depositsEnd) :
        loc(loc), deposits(depositsBegin, depositsEnd){}

    scChunk(){}

    const_deposit_iterator begin() const {return deposits.begin();}
    deposit_iterator begin() {return deposits.begin();}

    const_deposit_iterator end() const {return deposits.end();}
    deposit_iterator end(){return deposits.end();}

    void removeDeposit(deposit_iterator i) {deposits.erase(i);}

private:
    QVector2D loc;
    deposit_list deposits;

};


#endif // SCCHUNK_H
