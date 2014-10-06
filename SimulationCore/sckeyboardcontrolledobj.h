#ifndef SCKEYBOARDCONTROLLEDOBJ_H
#define SCKEYBOARDCONTROLLEDOBJ_H

#include <QVector2D>
#include <QSharedPointer>

#include "simulationcore_ie.h"

#include "scKeyboardInput.h"

class scKeyboardState;
class scObjDesc;
class scMovementDesc;
class scWorldDesc;

class SIM_IE scKeyboardControlledObj {
public:
    scKeyboardControlledObj(scKeyboardState_p keyboardObj, scKeyboardMap_ccp km);
    scKeyboardControlledObj(scKeyboardState_p keyboardObj, scKeyboardMap_ccp km, QVector2D scaleFactor);

    scMovementDesc getMovement(const scObjDesc &objDesc) const;
    bool isUsing() const;
    void updateStrategy(const scObjDesc &objDesc, const scWorldDesc &worldState) const;

private:
    class keyboardListener;

    friend class keyboardListener;

    void registerKeyboardListener();
    QVector2D deltaScale;

    scKeyboardState_p ks;
    scKeyboardMap_ccp kMap;


    float udScale() const {return (ks->keyScale(kMap->Down()) - ks->keyScale(kMap->Up())); }
    float lrScale() const {return (ks->keyScale(kMap->Right()) - ks->keyScale(kMap->Left()));}
};

#endif // SCKEYBOARDCONTROLLEDOBJ_H
