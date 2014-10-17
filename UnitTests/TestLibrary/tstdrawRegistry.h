#ifndef DRAWREGISTRY_H
#define DRAWREGISTRY_H

#include <QLineF>
#include <QString>
#include <QPainter>

#include <glbDefinitions.h>
#include <gcImage.h>
#include <gcDrawingImpl.h>

#include <vector>


class tst_drawRegistry : public gcDrawingImpl {
public:
    typedef std::vector<point> point_list;
    typedef point_list::const_iterator const_iterator;


    template <typename render_type>
    void Draw(render_type, point loc) {
        add(loc);
    }

    void Draw(gcImage, QRectF qrect){add(point(qrect.center().x(), qrect.center().y()));}

    tst_drawRegistry() : gcDrawingImpl(p, QRect(0, 0, 1920, 1080), false){
        p.setTransform(QTransform());
    }

    bool hasDrawn(point p) const{
        return std::find(registry.begin(), registry.end(), p) != registry.end();
    }

    void PushTransform(QTransform t) {
        curLoc = point(t.dx(), t.dy());
    }

private:
    void add(point p) {
        registry.push_back(point(curLoc.x() + p.x(), curLoc.y() + p.y()));
    }

    point curLoc;

    QPainter p;
    point_list registry;
};

#endif // DRAWREGISTRY_H
