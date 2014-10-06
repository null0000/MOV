

#include "coDebugHandler.h"

#include <scTagMsgCallback.h>
#include <QKeyEvent>

coDebugHandler::~coDebugHandler() {
    removeTags();
}


void coDebugHandler::removeTags() {
    removeWorldTags();
    removeKsTags();
}

void coDebugHandler::removeWorldTags() {
    for (str_tag_pair tag : dbgTxtList)
        world->removeDebugText(tag.second);
}


void coDebugHandler::removeKsTags() {
    for (ks_tag t : ksTagList)
        ks->removeListener(t);
}

coDebugHandler::coDebugHandler() :
    mapping(defaultMap()){}


coDebugHandler::coDebugHandler(coWorld_p world, scKeyboardState_p ks) :
    world(world), ks(ks), mapping(defaultMap()){addKeyStateListeners();}

coDebugHandler::coDebugHandler(coWorld_p world, coWorldFullTag ptag, scKeyboardState_p ks) :
    world(world), playerTag(ptag), ks(ks), mapping(defaultMap()){addKeyStateListeners();}

coDebugHandler::coDebugHandler(const coDebugHandler &other) :
    world(other.world), playerTag(other.playerTag), mapping(other.mapping) {
    addKeyStateListeners();
}

coDebugHandler &coDebugHandler::operator =(const coDebugHandler &Other) {
    if (this == &Other)
        return *this;
    removeTags();

    world = Other.world;
    playerTag = Other.playerTag;
    setKeyboardMapping(Other.mapping);
    setKeyboardState(Other.ks);

    if (!showingPlayerInfo())
        showPlayerInfo();
    return *this;
}

class coDebugHandler::listener : public scKeyListener
{
public:
    listener(coDebugHandler &parent, DebugKeyboardOptionsEnum e) :
        parent(parent), e(e){}
    void registerEvent() {parent.registerEvent(e);}
private:
    coDebugHandler &parent;
    DebugKeyboardOptionsEnum e;
};

void coDebugHandler::addKeyStateListeners() {
    if (ks.isNull())
        return;
    for (auto itr : mapping) {
        QSharedPointer<scKeyListener> lstnrPtr(new listener(*this, itr.first));
        ksTagList.push_back(ks->registerListener(itr.second, lstnrPtr));
    }
}

void coDebugHandler::registerPlayer(coWorldFullTag newTag) {
    playerTag = newTag;
}

void coDebugHandler::showPlayerInfo() {
    if (playerTag == coWorld::NULL_SIM_TAG)
        return;

    str_tag playerListener;
    playerListener = world->addDebugText(glbStringCallback_p(new scTagMsgCallback("Player", playerTag)));
    dbgTxtList.push_back(str_tag_pair(PlayerInfoE, playerListener));

}

void coDebugHandler:: hidePlayerInfo() {
    typedef std::vector<str_tag_pairs::iterator> pair_iterator_list;
    pair_iterator_list remList;
    for (auto pairItr = dbgTxtList.begin(); pairItr != dbgTxtList.end(); pairItr++){
        if (pairItr->first == PlayerInfoE) {
            remList.push_back(pairItr);
        }
    }
    for (auto i : remList) {
        world->removeDebugText(i->second);
        dbgTxtList.erase(i);
    }
}

void coDebugHandler::setKeyboardState(scKeyboardState_p newKS) {
    removeKsTags();
    ks = newKS;
}

void coDebugHandler::setKeyboardMapping(key_map newMapping) {
    removeKsTags();
    mapping = newMapping;
    addKeyStateListeners();
}


void coDebugHandler::registerEvent(DebugKeyboardOptionsEnum e) {
    switch(e) {
        case PlayerInfoE:
            if (!showingPlayerInfo())
                showPlayerInfo();
            else
                hidePlayerInfo();
            break;
    }
}

coDebugHandler::key_map coDebugHandler::defaultMap() {
    typedef key_map::key_pair key_pair;
    std::vector<key_pair> map;
    map.push_back(key_pair(PlayerInfoE, Qt::Key_F11));
    return key_map(map.begin(), map.end());
}


bool coDebugHandler::showingPlayerInfo() const {
    for (str_tag_pair pair : dbgTxtList) {
        if (pair.first == PlayerInfoE)
            return true;
    }
    return false;
}
