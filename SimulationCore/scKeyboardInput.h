#ifndef SCKEYBOARDINPUT_H
#define SCKEYBOARDINPUT_H

#include <QMap>
#include <QKeyEvent>
#include <QWindow>
#include <iostream>
#include <map>

#include "simulationcore_ie.h"

class scKeyboardState;
template <typename keyType> class scKeyboardMap;
typedef enum {upE, downE, leftE, rightE, useE} MovementEnum;
typedef scKeyboardMap<MovementEnum> scKeyboardMovementMap;
class scInputDevice;
typedef QSharedPointer<const scKeyboardState> scKeyboardState_ccp;
typedef QSharedPointer<scKeyboardState> scKeyboardState_p;
typedef QSharedPointer<const scKeyboardState> scKeyboardState_cp;
typedef QSharedPointer<const scKeyboardMovementMap> scKeyboardMap_ccp;
typedef QSharedPointer<const scKeyboardMovementMap> scKeyboardMap_cp;
typedef const scInputDevice *scInputDevice_p;

/**
 * @brief The scInputDevice class
 *
 *This acts as a bridge between the outside world
 *and the simulation core for input signals. To use
 *this class, Implement it and connect your signals to it,
 *then pass that instantiation to SC.
 */
class SIM_IE scInputDevice : public QObject
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
class SIM_IE Key {

    int mappedKey;

public:
    Key(int mappedKey) : mappedKey(mappedKey){}
    Key() : mappedKey(-1){}

    int toInt()const {return mappedKey;}
    operator int(){return toInt();}

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
template<typename keyEnum>
class SIM_IE scKeyboardMap
{
public:
    typedef std::pair<keyEnum, Key> key_pair;
    typedef std::map<keyEnum, Key> key_map;
    typedef typename key_map::iterator key_pair_iterator;
    typedef typename key_map::const_iterator const_key_pair_iterator;

    Key Up() const {return returnFind(upE);}
    Key Down() const {return returnFind(downE);}
    Key Left() const {return returnFind(leftE);}
    Key Right() const {return returnFind(rightE);}
    Key Use() const {return returnFind(useE);}


    scKeyboardMap(key_map map) :keyMap(map){}

    template<typename PairingItr>
    scKeyboardMap(PairingItr begin, PairingItr end) : keyMap(begin, end){}

    template<typename PairingItr>
    void Insert(PairingItr begin, PairingItr end){
        keyMap.insert(begin, end);
    }

    void Insert(key_pair newVal) {keyMap.insert(newVal);}

    void remap(keyEnum key, Key newKey) {keyMap[key] = newKey;}

    static scKeyboardMovementMap stdMovementMap();

    key_pair_iterator begin();
    const_key_pair_iterator begin() const;

    key_pair_iterator end();
    const_key_pair_iterator end() const;

private:
    Key returnFind(keyEnum k) const;
    key_map keyMap;

};



class SIM_IE scKeyListener
{
public:
    virtual void registerEvent() = 0;
    virtual ~scKeyListener(){}
};

typedef QSharedPointer<scKeyListener> scKeyListener_p;

/**
 * @brief The KeyboardState class
 *  Represents the current state of the player's
 *  keyboard. Query it to see what's going on using
 *  isDown. keyScale can be used for multiplication
 *  purposes when dealing with velocities (i.e.
 *  write mySpeed * ks.keyScale(keyDir);
 */
class SIM_IE scKeyboardState : public QObject {

    Q_OBJECT
public:
    typedef size_t t_tag;

    const static t_tag NULL_TAG = -1;

    bool isDown(Key k) const;
    int keyScale(Key k) const;

    scKeyboardState(scInputDevice_p Parent);

    scKeyboardState();

    t_tag registerListener(int key, scKeyListener_p obj);
    void removeListener(t_tag tag);

    static t_tag nullTag() {return NULL_TAG;}

public slots:
    void KeyPressed(QKeyEvent *qke);
    void KeyReleased(QKeyEvent *qke);

private:
    struct t_removeTag;//used as a functor
    void notifyListeners(int key);
    typedef std::pair<t_tag, scKeyListener_p> t_listenerPair;
    typedef std::multimap<int,  t_listenerPair> listenerSetMap;
    QMap<Key, bool> downKeyMap;
    listenerSetMap listenerMap;
    t_tag curTag;
};



template <typename enumType>
Key scKeyboardMap<enumType>::returnFind(enumType k) const
{
    typename key_map::const_iterator fr (keyMap.find(k));
    if (fr != keyMap.end())
        return keyMap.find(k)->second;
    return Key(0);
}

template <typename enumType>
scKeyboardMovementMap scKeyboardMap<enumType>::stdMovementMap() {
    key_map map;
    map[upE] = Key(Qt::Key_W);
    map[downE] = Key(Qt::Key_S);
    map[leftE] = Key(Qt::Key_A);
    map[rightE] = Key(Qt::Key_D);
    map[useE] = Key(Qt::Key_E);
    return map;
}

template <typename enumType>
typename scKeyboardMap<enumType>::key_pair_iterator scKeyboardMap<enumType>::begin() {return keyMap.begin();}

template <typename enumType>
typename scKeyboardMap<enumType>::const_key_pair_iterator scKeyboardMap<enumType>::begin() const {return keyMap.begin();}


template <typename enumType>
typename scKeyboardMap<enumType>::key_pair_iterator scKeyboardMap<enumType>::end() {return keyMap.end();}


template <typename enumType>
typename scKeyboardMap<enumType>::const_key_pair_iterator scKeyboardMap<enumType>::end() const {return keyMap.end();}


#endif // SCKEYBOARDINPUT_H

