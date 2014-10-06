

#include <QPainter>
#include <QGraphicsPixmapItem>
#include <QGraphicsLineItem>
#include "gcDrawingImpl.h"
#include "gcImage.h"


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
    matStack.push(painter.transform());
    painter.setTransform(mat, true);
    QTransform t(painter.transform());
    Q_ASSERT(t.isAffine());
}
void gcDrawingImpl::PopTransform()
{
    matStack.pop();
    Q_ASSERT(matStack.size() > 0);
    QTransform topMat(matStack.top());
    painter.setTransform(topMat, false);
}

void gcDrawingImpl::Draw(gcImage i, QRectF qrect)
{
    painter.drawPixmap(QPointF(0, 0), i.ToPixmap(), qrect);
}

gcDrawingImpl::gcDrawingImpl(QPainter &painter) :
    painter(painter) {matStack.push(painter.transform());}

void gcDrawingImpl::Draw(QString s){
    painter.drawText(QPoint(0, 0), s);
}

void gcDrawingImpl::Draw(QString s, QPoint loc) {
    painter.drawText(loc, s);
}

void gcDrawingImpl::SetColor(QColor qc) {
    painter.setBrush(qc);
    painter.setPen(qc);
}


QFont gcDrawingImpl::curFont() const{
    return painter.font();
}
