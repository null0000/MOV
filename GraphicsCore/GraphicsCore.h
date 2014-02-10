#ifndef GRAPHICSCORE_H
#define GRAPHICSCORE_H


#include <qtglobal>
#include <stack>
#include <QGraphicsScene>
#include <QTransform>
#include <QPainter>

class QRectF;
class gcImage;
class gcLine;
class gcShape;
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


class gcImage{
public:
    gcImage(QString InputFile);
    gcImage();

    void Load(QString inputFile);

    QPixmap ToPixmap() const;
    bool IsLoaded();

    gcRenderable *toRenderable() const;

private:
    QPixmap map;

    class gcImageRenderable;
};



#endif // GRAPHICSCORE_H
