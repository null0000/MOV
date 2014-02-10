#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <deque>

#include <QtGui/QWindow>
#include <QtGui/QOpenGLFunctions>
#include <QOpenGLPaintDevice>

#include "../GraphicsCore/GraphicsCore.h"

namespace Ui {
class MainWindow;
}


class MainWindow : public QWindow, protected QOpenGLFunctions
{
    Q_OBJECT

public:
    explicit MainWindow(QWindow *parent = 0);

    virtual void render(QPainter *painter);
    virtual void render();

    virtual void initialize();

    void setAnimating(bool animating);

    void attachRenderable(gcRenderable *renderable);

public slots:
    void renderLater();
    void renderNow();

protected:
    bool event(QEvent *event);

    void exposeEvent(QExposeEvent *event);
    void resizeEvent(QResizeEvent *event);

private:
    bool m_update_pending;
    bool m_animating;

    QOpenGLContext *m_context;
    QOpenGLPaintDevice *m_device;
    std::deque<gcRenderable  *> renderables;
};
#endif // MAINWINDOW_H
