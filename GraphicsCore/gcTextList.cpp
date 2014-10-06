
#include "gcTextList.h"
#include "gcDrawingImpl.h"

#include <QString>
#include <QColor>
#include <sstream>
#include <algorithm>

#include <iostream>
#include <qfontmetrics.h>

const gcTextList::t_tag gcTextList::NULL_TAG = -1;

void gcTextList::draw(gcDrawingImpl &impl) const {
    static const size_t V_OFF_START = 10;
    static const size_t V_OFF_PAD = 5;

    impl.SetColor(Qt::white);

    size_t voffset = V_OFF_START;
    QFontMetrics met (impl.curFont());

    for (tagged_cb gcbPair : list)
    {
        glbStringCallback_p gcb (gcbPair.second);
        if (gcb.isNull() || gcb->msg() == "")
            continue;
        impl.Draw(QString::fromStdString(gcb->msg()), QPoint(0, voffset));
        voffset += met.height() + V_OFF_PAD;
    }
}

gcTextList::t_tag gcTextList::pushText(glbStringCallback_p scb) {
    t_tag rtag = curtag++;
    list.push_back(tagged_cb(rtag, scb));
    return rtag;
}


typedef std::pair<size_t, glbStringCallback_p> t_taggedCallback;
struct predicate{
    bool operator()(t_taggedCallback elem, size_t val) const {return elem.first < val;}
};

void gcTextList::removeText(t_tag orig){
    Q_ASSERT(orig != NULL_TAG);
    if (orig == NULL_TAG) //don't crash during run time.
        return;
    typedef std::vector<cb_list::iterator> itr_list;
    itr_list delLocs;
    for (cb_list::iterator i = list.begin(); i != list.end(); i++) {
        if (i->first == orig)
            delLocs.push_back(i);
    }
    for (cb_list::iterator i : delLocs) list.erase(i);
}

void gcTextList::clearText() {
    list.clear();
}
