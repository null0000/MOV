#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <deque>

#include <QtGui/QWindow>
#include <QtGui/QOpenGLFunctions>
#include <QOpenGLPaintDevice>

#include <coWorld.h>

namespace Ui {
class MainWindow;
}


class MainWindow : public QWindow, protected QOpenGLFunctions
{
    Q_OBJECT

    static MainWindow *App;

    class inputImpl : public scInputDevice {

    public:
        inputImpl(MainWindow *Parent) :
            scInputDevice() {
            connect(Parent, SIGNAL(keyPressSignal(QKeyEvent*)), this, SIGNAL(keyPressSignal(QKeyEvent*)));
            connect(Parent, SIGNAL(keyReleaseSignal(QKeyEvent*)), this, SIGNAL(keyReleaseSignal(QKeyEvent*)));
        }
    };

public:
    explicit MainWindow(QWindow *parent = 0);

    virtual void render(QPainter &painter);
    virtual void render();

    virtual void initialize();

    MainWindow &AppWindow() const{Q_ASSERT(App); return *App;}

public slots:
    void renderLater();
    void renderNow();

protected:
    bool event(QEvent *event);

    void exposeEvent(QExposeEvent *event);
    void resizeEvent(QResizeEvent *event);
    virtual void keyPressEvent(QKeyEvent *e){emit keyPressSignal(e);}
    virtual void keyReleaseEvent(QKeyEvent *e){emit keyReleaseSignal(e);}

signals:
    void keyPressSignal(QKeyEvent *);
    void keyReleaseSignal(QKeyEvent *);

private:
    bool updatePending;
    bool animating;
    QOpenGLContext *context;
    QOpenGLPaintDevice *device;
    inputImpl inputDevice;
    coWorld_p world;
};
#endif // MAINWINDOW_H
