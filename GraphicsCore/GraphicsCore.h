#ifndef GRAPHICSCORE_H
#define GRAPHICSCORE_H


#include <qtglobal>
#include <stack>
#include <QGraphicsScene>
#include <QTransform>
#include <QPainter>
#include "gcImage.h"
#include "gcImageDescription.h"
#include "gcRenderable.h"
#include "gcDrawingImpl.h"

class QRectF;
class QPointF;
class QPixmap;
class QLineF;
class fcFile;
class QGraphicsItem;
class QGraphicsPixmapItem;

class gcRenderList{
public:
    virtual void pushRenderable(gcRenderable *) = 0;
    virtual ~gcRenderList(){}

};


#endif // GRAPHICSCORE_H
