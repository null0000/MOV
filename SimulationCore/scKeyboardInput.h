#ifndef SCKEYBOARDINPUT_H
#define SCKEYBOARDINPUT_H

#include <QMap>
#include <QKeyEvent>
#include <QWindow>
#include <iostream>
#include <set>


class scKeyboardState;
class scKeyboardMap;
class scInputDevice;
typedef const QSharedPointer<const scKeyboardState> scKeyboardState_ccp;
typedef const QSharedPointer<scKeyboardState> scKeyboardState_p;
typedef QSharedPointer<const scKeyboardState> scKeyboardState_cp;
typedef const QSharedPointer<const scKeyboardMap> scKeyboardMap_ccp;
typedef QSharedPointer<const scKeyboardMap> scKeyboardMap_cp;
typedef const scInputDevice *scInputDevice_p;

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

    int toInt()const {return mappedKey;}

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
class scKeyboardMap
{
public:
    typedef enum {upE, downE, leftE, rightE, useE} keyEnum;
    typedef std::map<keyEnum, Key> keyMapping_t;

    Key Up() const {return returnFind(upE);}
    Key Down() const {return returnFind(downE);}
    Key Left() const {return returnFind(leftE);}
    Key Right() const {return returnFind(rightE);}
    Key Use() const {return returnFind(useE);}


    scKeyboardMap(keyMapping_t map) :keyMap(map){}

    void remap(keyEnum key, Key newKey) {keyMap[key] = newKey;}

    static scKeyboardMap stdMap();

private:
    Key returnFind(keyEnum k) const;
    keyMapping_t keyMap;

};

class scKeyListener
{
public:
    virtual void registerEvent() = 0;
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
public:

    bool isDown(Key k) const;
    int keyScale(Key k) const;

    scKeyboardState(scInputDevice_p Parent);

    scKeyboardState();

    void registerListener(int key, scKeyListener *obj);

public slots:
    void KeyPressed(QKeyEvent *qke);
    void KeyReleased(QKeyEvent *qke);

private:
    void notifyListeners(int key);
    typedef std::set<scKeyListener *> listenerSet;
    typedef std::map<int,  listenerSet> listenerSetMap;
    QMap<Key, bool> downKeyMap;
    listenerSetMap listenerMap;
};



#endif // SCKEYBOARDINPUT_H

