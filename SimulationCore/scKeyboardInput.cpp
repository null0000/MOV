#include "scKeyboardInput.h"

void scKeyboardState::notifyListeners(int key) {
    listenerSetMap::iterator itr = listenerMap.find(key);
    if (itr == listenerMap.end())
        return;

    listenerSet &lSet = itr->second;
    for (listenerSet::iterator setItr = lSet.begin(); setItr != lSet.end(); setItr++)
        (*setItr)->registerEvent();
}

void scKeyboardState::registerListener(int key, scKeyListener *obj) {
    Q_ASSERT(obj);
    listenerMap[key].insert(obj);
}

scKeyboardState::scKeyboardState(scInputDevice_p Parent) : QObject(){
    connect(Parent, SIGNAL(keyPressSignal(QKeyEvent *)), this, SLOT(KeyPressed(QKeyEvent *)));
    connect(Parent, SIGNAL(keyReleaseSignal(QKeyEvent *)), this, SLOT(KeyReleased(QKeyEvent *)));
}

scKeyboardState::scKeyboardState() : QObject() {}

bool scKeyboardState::isDown(Key k) const {return downKeyMap[k];}
int scKeyboardState::keyScale(Key k) const {return downKeyMap[k] ? 1 : 0;} /*redundant, but I don't want to abuse implicit values for bools*/
void scKeyboardState::KeyPressed(QKeyEvent *qke) {downKeyMap[qke->key()] = true; notifyListeners(qke->key());}
void scKeyboardState::KeyReleased(QKeyEvent *qke) {downKeyMap[qke->key()] = false;}


Key scKeyboardMap::returnFind(keyEnum k) const
{
    keyMapping_t::const_iterator fr = keyMap.find(k);
    if (fr != keyMap.end())
        return keyMap.find(k)->second;
    return Key(0);
}

scKeyboardMap scKeyboardMap::stdMap() {
    keyMapping_t map;
    map[upE] = Key(Qt::Key_W);
    map[downE] = Key(Qt::Key_S);
    map[leftE] = Key(Qt::Key_A);
    map[rightE] = Key(Qt::Key_D);
    map[useE] = Key(Qt::Key_E);
    return map;
}

