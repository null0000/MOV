#ifndef GRAPHICSCORE_H
#define GRAPHICSCORE_H


#include <qtglobal>
#include <stack>
#include <QGraphicsScene>
#include <QTransform>
#include <QPainter>
#include "gcImage.h"
#include "gcImageDescription.h"


class QRectF;
class QPointF;
class QPixmap;
class QLineF;
class fcFile;
class QGraphicsItem;
class QGraphicsPixmapItem;

class gcDrawingImpl{
public:
    void Draw(gcImage i);
    void Draw(gcImage i, QRectF qrect);
    void Draw(QLineF l);

    void PushTransform(QTransform mat);
    void PopTransform();

    gcDrawingImpl(QPainter &painter);

private:
    QPainter &painter;
    std::stack<QTransform> matStack;
    QTransform topMat;
};

class gcRenderable{
public:
    virtual void draw(gcDrawingImpl &impl) = 0;
    virtual ~gcRenderable(){}
};




#endif // GRAPHICSCORE_H
