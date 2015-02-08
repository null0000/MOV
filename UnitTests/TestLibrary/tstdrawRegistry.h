#ifndef DRAWREGISTRY_H
#define DRAWREGISTRY_H

#include <QLineF>
#include <QString>
#include <QPainter>

#include <glbDefinitions.h>
#include <gcImage.h>
#include <gcDrawingImpl.h>

#include <vector>


/**
 * @brief The tst_drawRegistry class
 *
 * This class implements the gcDrawingImpl class and logs all
 *
 */

class tst_dummyPaintEngine;
class QPaintEvent;
class tst_dummyPaintDevice : public QPaintDevice
{
public:
    tst_dummyPaintDevice();
    ~tst_dummyPaintDevice();
    tst_dummyPaintDevice &operator =(const tst_dummyPaintDevice &Other);
    tst_dummyPaintDevice(const tst_dummyPaintDevice &Other);
    void paintEvent(QPaintEvent *){};
    QPaintEngine *paintEngine() const;


private:
   tst_dummyPaintEngine *pEngine;

};

class tst_drawRegistry : public gcDrawingImpl {
public:
    typedef std::vector<point> point_list;
    typedef point_list::const_iterator const_iterator;


    template <typename render_type>
    void Draw(render_type, point loc) {
        add(loc);
    }

    void Draw(gcImage, QRectF qrect){add(point(qrect.center().x(), qrect.center().y()));}

    tst_drawRegistry() :
        gcDrawingImpl(painter, QRect(0, 0, 1920, 1080), false), painter(&dummyDevice){
        painter.setTransform(QTransform());
    }

    bool hasDrawn(point p) const{
        return std::find(registry.begin(), registry.end(), p) != registry.end();
    }

    void PushTransform(QTransform t) {
        curLoc = point(t.dx(), t.dy());
        gcDrawingImpl::PushTransform(t);
    }

    void PopTransform() {
        gcDrawingImpl::PopTransform();
        QTransform topMat(CurTransform());
        curLoc = point(topMat.dx(), topMat.dy());
    }

private:
    void add(point p) {
        registry.push_back(point(curLoc.x() + p.x(), curLoc.y() + p.y()));
    }

    tst_dummyPaintDevice dummyDevice;
    point curLoc;
    QPainter painter;
    point_list registry;
};

#endif // DRAWREGISTRY_H
