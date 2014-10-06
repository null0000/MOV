

#include "coDebugHandler.h"

#include <scTagMsgCallback.h>
#include <QKeyEvent>

#include <sstream>

class cameraInfoPrinter : public glbStringCallback
{
public:
    cameraInfoPrinter(coWorld_p world) : world(world){}
    std::string msg() const {
        QVector2D off(world->cameraOffset());
        std::stringstream str;
        str << "Camera: (" << off.x() << ", " << off.y() << ")";
        return str.str();
    }
private:
    coWorld_p world;
};

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
    for (size_t i = 0; i < (size_t) LastInfoE; i++){
        if (!showingInfoType((DbgInfoEnum)i))
            showGeneroInfo((DbgInfoEnum)i);
    }
    return *this;
}

class coDebugHandler::listener : public scKeyListener
{
public:
    listener(coDebugHandler &parent, DbgInfoEnum e) :
        parent(parent), e(e){}
    void registerEvent() {parent.registerEvent(e);}
private:
    coDebugHandler &parent;
    DbgInfoEnum e;
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

void coDebugHandler::setKeyboardState(scKeyboardState_p newKS) {
    removeKsTags();
    ks = newKS;
}

void coDebugHandler::setKeyboardMapping(key_map newMapping) {
    removeKsTags();
    mapping = newMapping;
    addKeyStateListeners();
}


glbStringCallback *coDebugHandler::CreateStrCB(DbgInfoEnum type) const {
    switch(type) {
        case PlayerInfoE:
            if (playerTag != coWorld::NULL_SIM_TAG)
                return new scTagMsgCallback("Player", playerTag);
            return new glbNullStrCallback();
        case CameraInfoE:
            return new cameraInfoPrinter(world);
        case LastInfoE:
            break; //error case
    }
    Q_ASSERT(false); //none shall pass.... in debug, anyway.
    return new glbNullStrCallback();
}

void coDebugHandler::registerEvent(DbgInfoEnum e) {
    if (showingInfoType(e))
        hideGeneroInfo(e);
    else
        showGeneroInfo(e);
}

coDebugHandler::key_map coDebugHandler::defaultMap() {
    typedef key_map::key_pair key_pair;
    std::vector<key_pair> map;
    map.push_back(key_pair(PlayerInfoE, Qt::Key_F11));
    map.push_back(key_pair(CameraInfoE, Qt::Key_F12));
    Q_ASSERT(map.size() == (size_t)LastInfoE);
    return key_map(map.begin(), map.end());
}


bool coDebugHandler::showingInfoType(DbgInfoEnum iType) const {
    for (str_tag_pair pair : dbgTxtList) {
        if (pair.first == iType)
            return true;
    }
    return false;
}



void coDebugHandler::showGeneroInfo(DbgInfoEnum infoType) {
    str_tag t (world->addDebugText(glbStringCallback_p(CreateStrCB(infoType))));
    dbgTxtList.push_back(str_tag_pair(infoType, t));

}

void coDebugHandler::hideGeneroInfo(DbgInfoEnum infoType) {
    typedef std::vector<str_tag_pairs::iterator> iterator_list;
    iterator_list iList;
    for (auto i = dbgTxtList.begin(); i != dbgTxtList.end(); i++)
        if (i->first == infoType)
            iList.push_back(i);
    Q_ASSERT(iList.size() == 1);
    for (auto i : iList) {
        world->removeDebugText(i->second);
        dbgTxtList.erase(i);
    }
}
