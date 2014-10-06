#ifndef CODEBUGHANDLER_H
#define CODEBUGHANDLER_H

#include "coWorld.h"
#include "compositioncore_ie.h"
#include "coWorldFullTag.h"



class CMP_IE coDebugHandler {
public:
    void registerPlayer(coWorldFullTag playerTag);

    typedef enum {PlayerInfoE} DebugKeyboardOptionsEnum;
    typedef scKeyboardMap<DebugKeyboardOptionsEnum> key_map;
    typedef coWorld::t_dbgStrTag t_tag;

    void showPlayerInfo();
    void hidePlayerInfo();

    void setKeyboardState(scKeyboardState_p ks);

    void setKeyboardMapping(key_map mapping);

    coDebugHandler();
    coDebugHandler(coWorld_p, scKeyboardState_p);
    coDebugHandler(coWorld_p, coWorldFullTag, scKeyboardState_p);

    coDebugHandler(const coDebugHandler &other);
    coDebugHandler &operator =(const coDebugHandler &Other);
    ~coDebugHandler();

private:
    class listener;
    friend class listener;

    void registerEvent(DebugKeyboardOptionsEnum e);

    void removeTags();
    void removeWorldTags();
    void removeKsTags();

    void addKeyStateListeners();
    void addPlayerInfo();

    static key_map defaultMap();

    bool showingPlayerInfo() const;

    coWorld_p world;
    coWorldFullTag playerTag;

    typedef coWorld::t_dbgStrTag str_tag;
    typedef std::pair<DebugKeyboardOptionsEnum, str_tag> str_tag_pair;
    typedef std::vector<str_tag_pair> str_tag_pairs;
    str_tag_pairs dbgTxtList;


    scKeyboardState_p ks;
    typedef scKeyboardState::t_tag ks_tag;
    typedef std::deque<ks_tag> ks_tag_list;
    ks_tag_list ksTagList;

    key_map mapping;

};


#endif // CODEBUGHANDLER_H
