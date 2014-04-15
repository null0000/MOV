#ifndef SCKEYBOARDINPUT_H
#define SCKEYBOARDINPUT_H

#include <QMap>
#include <QKeyEvent>
#include <QWindow>

class scKeyboardState;
#include <iostream>


/**
 * @brief The scInputDevice class
 *
 *This acts as a bridge between the outside world
 *and the simulation core for input signals. To use
 *this class, Implement it and connect your signals to it,
 *then pass that instantiation to SC.
 */
class scInputDevice : public QObject
{
    Q_OBJECT

signals:
    void keyPressSignal(QKeyEvent *KeyPress);
    void keyReleaseSignal(QKeyEvent *KeyRelease);

};


/**
 * @brief The Key class
 *  This is a key. It allows for a more firm
 *  representation of qt keys than just ints.
 */
class Key {

    int mappedKey;

public:
    Key(int mappedKey) : mappedKey(mappedKey){}
    Key() : mappedKey(-1){}


    bool operator < (const Key &Other) const {return mappedKey < Other.mappedKey;}
    bool operator > (const Key &Other) const {return mappedKey > Other.mappedKey;}
    bool operator == (const Key &Other) const {return mappedKey == Other.mappedKey;}
};


/**
 * @brief The KeyMapping class
 *
 *  This maps between input key signals and move actions
 *  using the keyEnum
 *
 */
class KeyMapping
{
public:
    typedef enum {upE, downE, leftE, rightE, useE} keyEnum;
    typedef std::map<keyEnum, Key> keyMapping_t;

    Key Up() const {return returnFind(upE);}
    Key Down() const {return returnFind(downE);}
    Key Left() const {return returnFind(leftE);}
    Key Right() const {return returnFind(rightE);}
    Key Use() const {return returnFind(useE);}


    KeyMapping(keyMapping_t map) :keyMap(map){}

    void remap(keyEnum key, Key newKey) {keyMap[key] = newKey;}

    static KeyMapping stdMap() {
        keyMapping_t map;
        map[upE] = Key(Qt::Key_W);
        map[downE] = Key(Qt::Key_S);
        map[leftE] = Key(Qt::Key_A);
        map[rightE] = Key(Qt::Key_D);
        map[useE] = Key(Qt::Key_E);
        return map;
    }

private:
    Key returnFind(keyEnum k) const
    {
        keyMapping_t::const_iterator fr = keyMap.find(k);
        if (fr != keyMap.end())
            return keyMap.find(k)->second;
        return Key(0);
    }
    keyMapping_t keyMap;

};


/**
 * @brief The KeyboardState class
 *  Represents the current state of the player's
 *  keyboard. Query it to see what's going on using
 *  isDown. keyScale can be used for multiplication
 *  purposes when dealing with velocities (i.e.
 *  write mySpeed * ks.keyScale(keyDir);
 */
class scKeyboardState : public QObject {

    Q_OBJECT

    QMap<Key, bool> downKeyMap;

public:
    bool isDown(Key k) const {return downKeyMap[k];}
    int keyScale(Key k) const {return downKeyMap[k] ? 1 : 0;} /*redundant, but I don't want to abuse implicit values for bools*/

    scKeyboardState(scInputDevice *Parent) : QObject(){
        connect(Parent, SIGNAL(keyPressSignal(QKeyEvent *)), this, SLOT(KeyPressed(QKeyEvent *)));
        connect(Parent, SIGNAL(keyReleaseSignal(QKeyEvent *)), this, SLOT(KeyReleased(QKeyEvent *)));
    }

    scKeyboardState() : QObject() {}

public slots:
    void KeyPressed(QKeyEvent *qke) {downKeyMap[qke->key()] = true;}
    void KeyReleased(QKeyEvent *qke) {downKeyMap[qke->key()] = false;}
};



#endif // SCKEYBOARDINPUT_H
