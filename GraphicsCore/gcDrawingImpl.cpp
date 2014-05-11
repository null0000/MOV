

#include <QPainter>
#include <QGraphicsPixmapItem>
#include <QGraphicsLineItem>
#include "GraphicsCore.h"

void gcDrawingImpl::Draw(gcImage i)
{
    painter.drawPixmap(QPointF(0, 0), i.ToPixmap());
}

void gcDrawingImpl::Draw(QLineF l)
{
    painter.drawLine(l);
}

void gcDrawingImpl::PushTransform(QTransform mat)
{
    topMat = topMat * mat;
    matStack.push(mat);
    painter.setTransform(topMat, false);
}
void gcDrawingImpl::PopTransform()
{
    matStack.pop();
    Q_ASSERT(matStack.size() > 0);
    topMat = matStack.top();
    painter.setTransform(topMat, false);
}

void gcDrawingImpl::Draw(gcImage i, QRectF qrect)
{
    painter.drawPixmap(QPointF(0, 0), i.ToPixmap(), qrect);
}

gcDrawingImpl::gcDrawingImpl(QPainter &painter) :
    painter(painter), matStack(), topMat(){matStack.push(topMat);}

void gcDrawingImpl::Draw(QString s){
    painter.drawText(QPoint(0, 0), s);
}
