#ifndef GCTEXTLIST_H
#define GCTEXTLIST_H

#include "gcRenderable.h"
#include "graphicscore_ie.h"

#include <glbStringCallback.h>
#include <vector>

class GFX_IE gcTextList  : public gcRenderable {
public:
    typedef size_t t_tag;

    static const t_tag NULL_TAG;


    void draw(gcDrawingImpl &impl) const;

    t_tag pushText(glbStringCallback_p scb);
    void removeText(t_tag orig);
    void clearText();

    gcTextList() : curtag(0){}

private:
    typedef std::pair<t_tag, glbStringCallback_p> tagged_cb;
    typedef std::vector<tagged_cb> cb_list;

    size_t curtag;
    cb_list list;

};

#endif // GCTEXTLIST_H
