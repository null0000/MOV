#ifndef SCKEYBOARDCONTROLLEDOBJ_H
#define SCKEYBOARDCONTROLLEDOBJ_H

#include <QVector2D>
#include <QSharedPointer>
#include "simulationcore.h"
#include "scUseListener.h"

class scKeyboardState;
class scKeyboardMap;
class scUseListener;

class scKeyboardControlledObj : public scObject {
public:
    scKeyboardControlledObj(scKeyboardState_p keyboardObj, scKeyboardMap_ccp km);
    scKeyboardControlledObj(scKeyboardState_p keyboardObj, scKeyboardMap_ccp km, QVector2D scaleFactor);
    scKeyboardControlledObj(scKeyboardState_p keyboardObj, scKeyboardMap_ccp  km, QVector2D scaleFactor, QVector2D startPos, scUseListener listener);

    void Simulate(delta_t timeDelta);
    QVector2D position() const {return pos;}
    bool isUsing() const;
private:
    class keyboardListener;

    friend class keyboardListener;

    void registerKeyboardListener();

    QVector2D pos;
    QVector2D deltaScale;

    scKeyboardState_p ks;
    scKeyboardMap_ccp kMap;

    scUseListener listener;

    float udScale() const {return (ks->keyScale(kMap->Down()) - ks->keyScale(kMap->Up())) * deltaScale.y(); }
    float lrScale() const {return (ks->keyScale(kMap->Right()) - ks->keyScale(kMap->Left())) * deltaScale.x();}
};

#endif // SCKEYBOARDCONTROLLEDOBJ_H
