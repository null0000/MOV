#include "simulationcore.h"
#include "scUseListener.h"

class scKeyboardControlledObj::keyboardListener : public scKeyListener {
public:
    void registerEvent();
    keyboardListener(scKeyboardControlledObj &listener) :
        owner(listener){}
private:
    scKeyboardControlledObj &owner;
};

void scKeyboardControlledObj::Simulate(delta_t timeDelta) {
    QVector2D inputScale (lrScale(), udScale());
    QVector2D timeScaledPosDelta = inputScale * timeDelta;
    pos += timeScaledPosDelta;
}

bool scKeyboardControlledObj::isUsing() const {
    return ks->isDown(kMap->Use());
}

void scKeyboardControlledObj::keyboardListener::registerEvent() {owner.listener.registerUse(owner);}

scKeyboardControlledObj::scKeyboardControlledObj(scKeyboardState_p keyboardObj, scKeyboardMap_ccp km) : pos(0, 0), deltaScale(1, 1), ks(keyboardObj), kMap(km){registerKeyboardListener();}
scKeyboardControlledObj::scKeyboardControlledObj(scKeyboardState_p keyboardObj, scKeyboardMap_ccp km, QVector2D scaleFactor) :
    pos(0, 0), deltaScale(scaleFactor), ks(keyboardObj), kMap(km){registerKeyboardListener();}
scKeyboardControlledObj::scKeyboardControlledObj(scKeyboardState_p keyboardObj, scKeyboardMap_ccp  km, QVector2D scaleFactor, QVector2D startPos, scUseListener listener) :
    pos(startPos), deltaScale(scaleFactor), ks(keyboardObj), kMap(km), listener(listener){registerKeyboardListener();}


void scKeyboardControlledObj::registerKeyboardListener() {
    ks->registerListener(kMap->Use().toInt(), new keyboardListener(*this));
}
