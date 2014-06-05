#ifndef GCDRAWINGIMPL_H
#define GCDRAWINGIMPL_H

#include "graphicscore_ie.h"

class GFX_IE gcDrawingImpl{
public:
    void Draw(gcImage i);
    void Draw(gcImage i, QRectF qrect);
    void Draw(QLineF l);
    void Draw(QString s);

    void PushTransform(QTransform mat);
    void PopTransform();

    gcDrawingImpl(QPainter &painter);

private:
    QPainter &painter;
    std::stack<QTransform> matStack;
    QTransform topMat;
};

#endif // GCDRAWINGIMPL_H
