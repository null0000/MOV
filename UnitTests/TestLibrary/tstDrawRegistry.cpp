#include "tstDrawRegistry.h"

#include <QPaintEngine>
#include <QRect>
#include <QImage>
#include <QLine>
#include <QPainterPath>
#include <QPoint>
#include <QPixmap>


class tst_dummyPaintEngine : public QPaintEngine
{
    virtual bool	begin ( QPaintDevice * ){return true;}
    virtual void	drawEllipse ( const QRectF & ){}
    virtual void	drawEllipse ( const QRect & ){}
    virtual void	drawImage ( const QRectF &, const QImage &, const QRectF &, Qt::ImageConversionFlags = Qt::AutoColor ){}
    virtual void	drawLines ( const QLineF * , int  ){}
    virtual void	drawLines ( const QLine * , int  ){}
    virtual void	drawPath ( const QPainterPath &  ){}
    virtual void	drawPixmap ( const QRectF & , const QPixmap & , const QRectF &  ){}
    virtual void	drawPoints ( const QPointF * , int  ){}
    virtual void	drawPoints ( const QPoint * , int  ){}
    virtual void	drawPolygon ( const QPointF * , int , PolygonDrawMode  ){}
    virtual void	drawPolygon ( const QPoint * , int , PolygonDrawMode  ){}
    virtual void	drawRects ( const QRectF * , int  ){}
    virtual void	drawRects ( const QRect * , int  ){}
    virtual void	drawTextItem ( const QPointF & , const QTextItem &  ){}
    virtual void	drawTiledPixmap ( const QRectF & , const QPixmap & , const QPointF &  ){}
    virtual bool	end (){return false;}
    virtual void updateState(const QPaintEngineState &){}
    virtual Type type() const{return User;}
} ;

QPaintEngine *tst_dummyPaintDevice::paintEngine() const
{
    return pEngine;
}

tst_dummyPaintDevice::tst_dummyPaintDevice() :
    QPaintDevice(), pEngine(new tst_dummyPaintEngine()){}
tst_dummyPaintDevice::~tst_dummyPaintDevice()
{
    delete pEngine;
}

tst_dummyPaintDevice &tst_dummyPaintDevice::operator =(const tst_dummyPaintDevice &Other)
{
    if (this == &Other)
        return *this;
    if (!this || !&Other)
        return *this;
    delete pEngine;
    pEngine = new tst_dummyPaintEngine();
    return *this;
}

tst_dummyPaintDevice::tst_dummyPaintDevice(const tst_dummyPaintDevice &) :
    QPaintDevice(), pEngine(new tst_dummyPaintEngine()){}
