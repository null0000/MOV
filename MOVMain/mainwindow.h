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

    class renderListImpl : public gcRenderList
    {

        QVector<gcRenderable *> renderableList;

    public:
        void pushRenderable(gcRenderable *newItem) {
            renderableList.push_back(newItem);
        }

        void render(gcDrawingImpl &renderer) {
            for (QVector<gcRenderable *>::iterator itr = renderableList.begin(); itr != renderableList.end(); itr++)
                (*itr)->draw(renderer);
        }

        ~renderListImpl(){}
    };

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
    bool updatePending;
    bool animating;
    renderListImpl renderList;
    QOpenGLContext *context;
    QOpenGLPaintDevice *device;
    scInputDevice inputDevice;
};
#endif // MAINWINDOW_H
