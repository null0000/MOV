

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

QTransform gcDrawingImpl::CurTransform()
{
    return matStack.top();
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
    QTransform topMat(matStack.top());
    matStack.pop();
    Q_ASSERT(matStack.size() > 0);
    painter.setTransform(topMat, false);
}

void gcDrawingImpl::Draw(gcImage i, QRectF qrect)
{
    painter.drawPixmap(QPointF(0, 0), i.ToPixmap(), qrect);
}

gcDrawingImpl::gcDrawingImpl(QPainter &painter,QRect windowBounds) :
    painter(painter), windowBounds(windowBounds) {
    matStack.push(painter.transform());
}

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

QRect gcDrawingImpl::screenGeometry() const {
    return windowBounds;
}

gcDrawingImpl::gcDrawingImpl(QPainter &painter, QRect windowBounds, bool) : //doesn't do anything with no push, just a hack so unit testing can do it's thing
        painter(painter), windowBounds(windowBounds) {

    matStack.push(painter.transform());

}
