#ifndef SCKEYBOARDINPUT_H
#define SCKEYBOARDINPUT_H

#include <QMap>
#include <QKeyEvent>
#include <QWindow>

class scInputDevice : public QObject
{
    Q_OBJECT

public:
    scInputDevice(QWindow *Parent) :
        QObject()
    {
        connect(Parent, SIGNAL(keyPressEvent(QKeyEvent *)), this, SLOT(KeyPressEvent(QKeyEvent *)));
        connect(Parent, SIGNAL(keyReleaseEvent(QKeyEvent *)), this, SLOT(KeyReleaseEvent(QKeyEvent *)));
    }

signals:
    void KeyPressEvent(QKeyEvent *KeyPress);
    void KeyReleaseEvent(QKeyEvent *KeyRelease);

};


class Key {

    int mappedKey;

public:
    Key(int mappedKey) : mappedKey(mappedKey){}
    Key() : mappedKey(-1){}


    bool operator < (const Key &Other) const {return mappedKey < Other.mappedKey;}
    bool operator > (const Key &Other) const {return mappedKey > Other.mappedKey;}
    bool operator == (const Key &Other) const {return mappedKey == Other.mappedKey;}
};

class KeyMapping
{
public:
    typedef enum {upE, downE, leftE, rightE, useE} keyEnum;
    typedef QMap<keyEnum, Key> keyMapping_t;

    Key Up() const {return keyMap[upE];}
    Key Down() const {return keyMap[downE];}
    Key Left() const {return keyMap[leftE];}
    Key Right() const {return keyMap[rightE];}
    Key Use() const {return keyMap[useE];}


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
    QMap<keyEnum, Key> keyMap;
    static QMap<keyEnum, Key> obtainDefaultMap();

};


class KeyboardState : public QObject {

    Q_OBJECT

    QMap<Key, bool> downKeyMap;

public:
    bool isDown(Key k) const {return downKeyMap[k];}
    int keyScale(Key k) const {return downKeyMap[k] ? 1 : 0;} /*redundant, but I don't want to abuse implicit values for bools*/

    KeyboardState(scInputDevice *Parent) : QObject(){
        connect(Parent, SIGNAL(KeyPressEvent(QKeyEvent *)), this, SLOT(KeyPressed(QKeyEvent *)));
        connect(Parent, SIGNAL(KeyReleaseEvent(QKeyEvent *)), this, SLOT(KeyReleased(QKeyEvent *)));
    }

    KeyboardState() : QObject()
    {}

public slots:
    void KeyPressed(QKeyEvent qke) {downKeyMap[qke.key()] = true;}
    void KeyReleased(QKeyEvent qke) {downKeyMap[qke.key()] = true;}
};



#endif // SCKEYBOARDINPUT_H
