#ifndef SCINSTR_H
#define SCINSTR_H

#include "scObject.h"

class scInstrDesc
{
public:
    QVector2D movement() const {return movement;}
    scInstrDesc registerMovement(QVector2D delta) const {return scInsrDesc(movement - delta, use);}

    float use() const {return useDelta;}
    scInstrDesc registerUse(float useLength) const {return scInstrDesc(movement, use - useLength);}

    scInstrDesc(QVector2D movement) :
        movement(movement), use(0){}
    scInstrDesc(float useLength) :
        movement(0, 0), usDelta(useLength){}
    scInstrDesc(QVector2D movement, float useLength) :
        movement(movement), useDelta(useLength){}
    scInstrDesc() :
        movement(0, 0), useDelta(0){}


    bool nullInstr() const {return movement.x() > 0 || movement.y() > 0 || useDelta > 0;}

private:
    QVector2D movement;
    float useDelta;

};

#endif // SCINSTR_H
