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
    scKeyboardControlledObj(scKeyboardState_ccp keyboardObj, scKeyboardMap_ccp km) : pos(0, 0), deltaScale(1, 1), useLatch(false), ks(keyboardObj), kMap(km){}
    scKeyboardControlledObj(scKeyboardState_ccp keyboardObj, scKeyboardMap_ccp km, QVector2D scaleFactor) :
        pos(0, 0), deltaScale(scaleFactor), useLatch(false), ks(keyboardObj), kMap(km){}
    scKeyboardControlledObj(scKeyboardState_ccp keyboardObj, scKeyboardMap_ccp  km, QVector2D scaleFactor, QVector2D startPos, scUseListener listener) :
        pos(startPos), deltaScale(scaleFactor), useLatch(false), ks(keyboardObj), kMap(km), listener(listener){}



    void Simulate(delta_t timeDelta);
    QVector2D position() const {return pos;}
    bool isUsing() const;
private:
    QVector2D pos;
    QVector2D deltaScale;

    bool useLatch;

    const QSharedPointer<const scKeyboardState> ks;
    const QSharedPointer<const scKeyboardMap> kMap;

    scUseListener listener;

    float udScale() const {return (ks->keyScale(kMap->Down()) - ks->keyScale(kMap->Up())) * deltaScale.y(); }
    float lrScale() const {return (ks->keyScale(kMap->Right()) - ks->keyScale(kMap->Left())) * deltaScale.x();}
};

#endif // SCKEYBOARDCONTROLLEDOBJ_H
