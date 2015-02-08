#ifndef GCDRAWINGIMPL_H
#define GCDRAWINGIMPL_H

#include "graphicscore_ie.h"
#include <stack>
#include <QTransform>

class gcImage;
class QLineF;
class QRectF;
class QTransform;
class QPainter;

//For unit testing purposes
#ifdef QT_DEBUG
#define DBG_VIRTUAL virtual
#else
#define DBG_VIRTUAL
#endif

class GFX_IE gcDrawingImpl{
public:
    DBG_VIRTUAL void Draw(gcImage i);
    DBG_VIRTUAL void Draw(gcImage i, QRectF qrect);
    DBG_VIRTUAL void Draw(QLineF l);
    DBG_VIRTUAL void Draw(QString s);
    DBG_VIRTUAL void Draw(QString s, QPoint loc);

    DBG_VIRTUAL QRect screenGeometry() const;

    DBG_VIRTUAL QFont curFont() const;

    DBG_VIRTUAL void PushTransform(QTransform mat);
    DBG_VIRTUAL void PopTransform();

    DBG_VIRTUAL void SetColor(QColor qc);

    DBG_VIRTUAL QTransform CurTransform();

    gcDrawingImpl(QPainter &painter, QRect windowBounds);

protected:
    gcDrawingImpl(QPainter &painter, QRect windowBounds, bool NOPUSH); //doesn't do anything with no push, just a hack so unit testing can do it's thing.

private:


    QPainter &painter;
    QRect windowBounds;
    std::stack<QTransform> matStack;
};

#endif // GCDRAWINGIMPL_H
