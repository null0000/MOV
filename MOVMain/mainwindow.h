#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <deque>

#include <QtGui/QWindow>
#include <QtGui/QOpenGLFunctions>
#include <QOpenGLPaintDevice>

#include "../GraphicsCore/GraphicsCore.h"
#include <simulationcore.h>

namespace Ui {
class MainWindow;
}


class MainWindow : public QWindow, protected QOpenGLFunctions
{
    Q_OBJECT

    static MainWindow *App;

public:
    explicit MainWindow(QWindow *parent = 0);

    virtual void render(QPainter *painter);
    virtual void render();

    virtual void initialize();

    void setAnimating(bool animating);

    void attachRenderable(gcRenderable *renderable);

    MainWindow &AppWindow() const{Q_ASSERT(App); return *App;}

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
    scInputDevice inputDevice;
};
#endif // MAINWINDOW_H
