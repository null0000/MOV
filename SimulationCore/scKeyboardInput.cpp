#include "scKeyboardInput.h"

void scKeyboardState::notifyListeners(int key) {
    auto listeners = listenerMap.equal_range(key);
    for (auto setItr = listeners.first; setItr != listeners.second; setItr++)
        setItr->second.second->registerEvent(); //iterator, then pair, then pair, then scKeyListener_p... sorry.
}

scKeyboardState::t_tag scKeyboardState::registerListener(int key, scKeyListener_p obj) {
    Q_ASSERT(obj);
    t_tag tag = curTag++;
    listenerMap.insert(listenerSetMap::value_type(key, t_listenerPair(tag, obj)));
    return tag;
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


struct scKeyboardState::t_removeTag{
    bool operator()(listenerSetMap::value_type vType){return vType.second.first == tag;}
    size_t tag;
};

template<typename container, typename forward_itr, typename predicate>
void erase_if(container &c, forward_itr begin, forward_itr end, predicate p) {
    for (auto i = begin; i != end; i++)
        if (p(*i))
            c.erase(i);
}

void scKeyboardState::removeListener(t_tag tag) {
    erase_if(listenerMap, listenerMap.begin(), listenerMap.end(), (t_removeTag){tag});
}
