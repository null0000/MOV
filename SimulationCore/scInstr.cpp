

#include "scInstr.h"


QVector2D scInstrDesc::movementRemaining() const {return movement;}

scInstrDesc scInstrDesc::registerMovement(QVector2D delta) const {

    return scInstrDesc(movement - delta, useDelta);
}

float scInstrDesc::useRemaining() const {return useDelta;}

scInstrDesc scInstrDesc::registerUse(float useLength) const {
    return scInstrDesc(movement, useDelta - useLength);
}

scInstrDesc::scInstrDesc(QVector2D movement) :
    movement(movement), useDelta(0){}

scInstrDesc::scInstrDesc(float useLength) :
    movement(0, 0), useDelta(useLength){}

scInstrDesc::scInstrDesc(QVector2D movement, float useLength) :
    movement(movement), useDelta(useLength){}

scInstrDesc::scInstrDesc() :
    movement(0, 0), useDelta(0){}

bool scInstrDesc::isNullInstr() const {return qAbs(movement.x()) == 0 && qAbs(movement.y()) == 0 && useDelta == 0;}

void scInstrDesc::Dump() const {
    std::cerr << "Instr Desc: X: " << movement.x() << " Y: " << movement.y() <<
                 " Use delta: " << useDelta << "\n";
}
