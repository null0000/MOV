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

class GFX_IE gcDrawingImpl{
public:
    void Draw(gcImage i);
    void Draw(gcImage i, QRectF qrect);
    void Draw(QLineF l);
    void Draw(QString s);
    void Draw(QString s, QPoint loc);

    QFont curFont() const;

    void PushTransform(QTransform mat);
    void PopTransform();

    void SetColor(QColor qc);

    gcDrawingImpl(QPainter &painter);

private:
    QPainter &painter;
    std::stack<QTransform> matStack;
};

#endif // GCDRAWINGIMPL_H
