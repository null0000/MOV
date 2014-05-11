#ifndef SCINSTR_H
#define SCINSTR_H

#include "scObject.h"
#include "QVector2D"
#include <QString>

class scInstrDesc
{
public:
    QVector2D movementRemaining() const;
    scInstrDesc registerMovement(QVector2D delta) const;

    float useRemaining() const;
    scInstrDesc registerUse(float useLength) const;

    scInstrDesc(QVector2D movement);
    scInstrDesc(float useLength);
    scInstrDesc(QVector2D movement, float useLength);
    scInstrDesc();
    bool isNullInstr() const;

    void Dump() const;

private:
    QVector2D movement;
    float useDelta;

};

#endif // SCINSTR_H
