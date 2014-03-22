
#include "simulationcore.h"
#include <QMap>
#include <QKeyEvent>



class Key {

    int mappedKey;

public:
    Key(int mappedKey) : mappedKey(mappedKey){}
    Key() : mappedKey(-1){}


    bool operator < (const Key &Other) const {return mappedKey < Other.mappedKey;}
    bool operator > (const Key &Other) const {return mappedKey > Other.mappedKey;}
    bool operator == (const Key &Other) const {return mappedKey == Other.mappedKey;}
};

class KeyboardState : public QObject {

    Q_OBJECT

    QMap<Key, bool> downKeyMap;

public:
    bool isDown(Key k) const {return downKeyMap[k];}
    int keyScale(Key k) const {return downKeyMap[k] ? 1 : 0;} /*redundant, but I don't want to abuse implicit values for bools*/

    KeyboardState(const scInputDevice &Parent) : QObject()
    {
        connect(&Parent, SIGNAL(scInputDevice::KeyPressEvent), this, SLOT(KeyPressed));
        connect(&Parent, SIGNAL(scInputDevice::KeyReleaseEvent), this, SLOT(KeyReleased));
    }

public slots:
    void KeyPressed(QKeyEvent qke) {downKeyMap[qke.key()] = true;}
    void KeyReleased(QKeyEvent qke) {downKeyMap[qke.key()] = true;}
};


class KeyMapping
{
public:
    typedef enum {upE, downE, leftE, rightE, useE} keyEnum;




    Key Up() const {return keyMap[upE];}
    Key Down() const {return keyMap[downE];}
    Key Left() const {return keyMap[leftE];}
    Key Right() const {return keyMap[rightE];}
    Key Use() const {return keyMap[useE];}


    KeyMapping(QMap<keyEnum, Key> map) :keyMap(map){}

    void remap(keyEnum key, Key newKey) {keyMap[key] = newKey;}

private:
    QMap<keyEnum, Key> keyMap;
    static QMap<keyEnum, Key> obtainDefaultMap();

};


class scKeyboardControlledObj : public scControlScheme, public scSimulationObject {

    pos_t pos;
    vec2D_t deltaScale;
    const KeyboardState &ks;
    const KeyMapping &kMap;

    float udScale() const {return (ks.keyScale(kMap.Up()) - ks.keyScale(kMap.Down())) * deltaScale.Y();}
    float lrScale() const {return (ks.keyScale(kMap.Right())) - ks.keyScale(kMap.Left()) * deltaScale.X();}



public:

    scKeyboardControlledObj(const KeyboardState &keyboardObj, const KeyMapping &km) : pos(0, 0), deltaScale(1, 1), ks(keyboardObj), kMap(km){}
    scKeyboardControlledObj(const KeyboardState &keyboardObj, const KeyMapping &km, vec2D_t scaleFactor) :
        pos(0, 0), deltaScale(scaleFactor), ks(keyboardObj), kMap(km){}
    scKeyboardControlledObj(const KeyboardState &keyboardObj, const KeyMapping &km, vec2D_t scaleFactor, pos_t startPos) :
        pos(startPos), deltaScale(scaleFactor), ks(keyboardObj), kMap(km){}


    void Simulate(delta_t timeDelta)
    {
        vec2D_t inputScale (lrScale(), udScale());
        vec2D_t timeScaledPosDelta = inputScale.scale(timeDelta);
        pos += timeScaledPosDelta;
    }

    pos_t position() const;


public slots:


};
