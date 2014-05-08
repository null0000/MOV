#ifndef SCKEYBOARDCONTROLLEDOBJ_H
#define SCKEYBOARDCONTROLLEDOBJ_H

#include <QVector2D>
#include <QSharedPointer>
#include "simulationcore.h"

class scKeyboardState;
class scKeyboardMap;

class scKeyboardControlledObj : public scObject {

    QVector2D pos;
    QVector2D deltaScale;
    const QSharedPointer<const scKeyboardState> ks;
    const QSharedPointer<const scKeyboardMap> kMap;

    float udScale() const {return (ks->keyScale(kMap->Down()) - ks->keyScale(kMap->Up())) * deltaScale.y(); }
    float lrScale() const {return (ks->keyScale(kMap->Right()) - ks->keyScale(kMap->Left())) * deltaScale.x();}

public:
    scKeyboardControlledObj(scKeyboardState_ccp keyboardObj, scKeyboardMap_ccp km) : pos(0, 0), deltaScale(1, 1), ks(keyboardObj), kMap(km){}
    scKeyboardControlledObj(scKeyboardState_ccp keyboardObj, scKeyboardMap_ccp km, QVector2D scaleFactor) :
        pos(0, 0), deltaScale(scaleFactor), ks(keyboardObj), kMap(km){}
    scKeyboardControlledObj(scKeyboardState_ccp keyboardObj, scKeyboardMap_ccp  km, QVector2D scaleFactor, QVector2D startPos) :
        pos(startPos), deltaScale(scaleFactor), ks(keyboardObj), kMap(km){}


    void Simulate(delta_t timeDelta);

    QVector2D position() const {return pos;}
};
#endif // SCKEYBOARDCONTROLLEDOBJ_H
