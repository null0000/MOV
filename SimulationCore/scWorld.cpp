
#include "simulationcore.h"
#include <QMap>
#include <QKeyEvent>


class scKeyboardControlledObj : public scObject {

    QVector2D pos;
    QVector2D deltaScale;
    const scKeyboardState &ks;
    KeyMapping kMap;

    float udScale() const {return (ks.keyScale(kMap.Down()) - ks.keyScale(kMap.Up())) * deltaScale.y(); }
    float lrScale() const {return (ks.keyScale(kMap.Right()) - ks.keyScale(kMap.Left())) * deltaScale.x();}



public:

    scKeyboardControlledObj(const scKeyboardState &keyboardObj, KeyMapping km) : pos(0, 0), deltaScale(1, 1), ks(keyboardObj), kMap(km){}
    scKeyboardControlledObj(const scKeyboardState &keyboardObj, KeyMapping km, QVector2D scaleFactor) :
        pos(0, 0), deltaScale(scaleFactor), ks(keyboardObj), kMap(km){}
    scKeyboardControlledObj(const scKeyboardState &keyboardObj, KeyMapping km, QVector2D scaleFactor, QVector2D startPos) :
        pos(startPos), deltaScale(scaleFactor), ks(keyboardObj), kMap(km){}


    void Simulate(delta_t timeDelta)
    {
        QVector2D inputScale (lrScale(), udScale());
        QVector2D timeScaledPosDelta = inputScale * timeDelta;
        pos += timeScaledPosDelta;
    }

    QVector2D position() const {return pos;}
};


scWorld::t_tag scWorld::addObject(scObject &newObj) {
    simVec.push_back(&newObj);
    return simVec.size() - 1;
}

void scWorld::simulate(delta_t timeDelta) {
    for (QVector<scObject *>::iterator itr = simVec.begin(); itr != simVec.end(); itr++)
        (*itr)->Simulate(timeDelta);
}


delta_t timeDeltaFromMilli(int milliseconds) {return ((float)(milliseconds))/TIME_CONVERSION_DIVISOR;}


scObject *scCreateKeyboardObject(scInputDevice *inputDevice, QVector2D startOffset, QVector2D speedScale)
{
    scKeyboardControlledObj *newObj = new scKeyboardControlledObj(*new scKeyboardState(inputDevice), KeyMapping::stdMap(),
                                                                  speedScale, startOffset);
    return newObj;
}
