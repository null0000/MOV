#ifndef GRAPHICSCORE_H
#define GRAPHICSCORE_H

#include "graphicscore_ie.h"

#include <qtglobal>
#include <stack>
#include <QGraphicsScene>
#include <QTransform>
#include <QPainter>
#include "gcImage.h"
#include "gcRenderable.h"
#include "gcDrawingImpl.h"

class QRectF;
class QPointF;
class QPixmap;
class QLineF;
class fcFile;
class QGraphicsItem;
class QGraphicsPixmapItem;

class GFX_IE gcRenderList{
public:
    virtual void pushRenderable(gcRenderable *) = 0;
    virtual ~gcRenderList(){}
};

typedef gcRenderList * gcRenderList_p;

#endif // GRAPHICSCORE_H
