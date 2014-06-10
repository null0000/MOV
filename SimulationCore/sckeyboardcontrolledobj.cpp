#include "simulationcore.h"
#include "scWorldDesc.h"
#include "scMovementDesc.h"

class scKeyboardControlledObj::keyboardListener : public scKeyListener {
public:
    void registerEvent();
    keyboardListener(scKeyboardControlledObj &listener) :
        owner(listener){}
private:
    scKeyboardControlledObj &owner;
};

bool scKeyboardControlledObj::isUsing() const {
    return ks->isDown(kMap->Use());
}

scKeyboardControlledObj::scKeyboardControlledObj(scKeyboardState_p keyboardObj, scKeyboardMap_ccp km) :
    deltaScale(1, 1), ks(keyboardObj), kMap(km){registerKeyboardListener();}
scKeyboardControlledObj::scKeyboardControlledObj(scKeyboardState_p keyboardObj, scKeyboardMap_ccp km, QVector2D scaleFactor) :
    deltaScale(scaleFactor), ks(keyboardObj), kMap(km){registerKeyboardListener();}


void scKeyboardControlledObj::registerKeyboardListener() {
    ks->registerListener(kMap->Use().toInt(), new keyboardListener(*this));
}

void scKeyboardControlledObj::keyboardListener::registerEvent(){}



scMovementDesc scKeyboardControlledObj::getMovement(const scObjDesc &) const {
        QVector2D inputScale (lrScale(), udScale());
        return scMovementDesc ((inputScale * deltaScale).normalized(), deltaScale.length()); //cache delta scale values?
}
void scKeyboardControlledObj::updateStrategy(const scObjDesc &, const scWorldDesc &) const{}
