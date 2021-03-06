#include "mainwindow.h"


#include <QtCore/QCoreApplication>

#include <QtGui/QOpenGLContext>
#include <QtGui/QOpenGLPaintDevice>
#include <QtGui/QPainter>

#include <deque>

#include<GraphicsCore.h>
#include <gcRenderList.h>
#include <GlobalCore.h>
#include <CompositionCore.h>
#include <QElapsedTimer>

MainWindow *MainWindow::App = NULL;

MainWindow::MainWindow(QWindow *parent)
    : QWindow(parent)
    , updatePending(false)
    , animating(false)
    , context(0)
    , device(0)
    , inputDevice(this)
{
    setSurfaceType(QWindow::OpenGLSurface);


    //THERE CAN ONLY BE ONE
    //.... despite the fact that that's generally bad programming practices. Oh well.
    Q_ASSERT(!App);
    App = this;

}

void MainWindow::render(QPainter &painter){
    painter.drawText(QPoint(50,50), QString("QString::fromStdString(stream.str())"));
    gcDrawingImpl drawDevice(painter, geometry());
    device->setSize(size());
    world->draw(drawDevice);
}

void MainWindow::initialize(){
    static const QRect INIT_WINDOW_BOUNDS (0, 0, 1600, 900);


    animating = true;
    setWidth(INIT_WINDOW_BOUNDS.width());
    setHeight(INIT_WINDOW_BOUNDS.height());
    setPosition(0, 0);
    setVisibility(Windowed);
    world = coBootUp(&inputDevice, QRect(0, 0, width() * .75, height() * .75), INIT_WINDOW_BOUNDS);
}

void MainWindow::render()
{
    if (!device)
        device = new QOpenGLPaintDevice;

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

    QPainter painter(device);
    render(painter);
}

void MainWindow::renderLater()
{
    if (!updatePending) {
        updatePending = true;
        QCoreApplication::postEvent(this, new QEvent(QEvent::UpdateRequest));
    }
}

bool MainWindow::event(QEvent *event)
{
    switch (event->type()) {
    case QEvent::UpdateRequest:
        renderNow();
        return true;
    default:
            return QWindow::event(event);
    }
}

void MainWindow::exposeEvent(QExposeEvent *event)
{
    Q_UNUSED(event);

    if (isExposed())
        renderNow();
}

void MainWindow::resizeEvent(QResizeEvent *event)
{
    Q_UNUSED(event);

    if (isExposed())
        renderNow();
}

static QElapsedTimer timer = QElapsedTimer();
void MainWindow::renderNow()
{

    if (!isExposed())
        return;


    updatePending = false;

    bool needsInitialize = false;

    if (!context) {
        context = new QOpenGLContext(this);
        context->setFormat(requestedFormat());
        context->create();

        needsInitialize = true;
    }

    context->makeCurrent(this);

    if (world)
        world->simulate(timer.elapsed());
    timer.start();

    if (needsInitialize) {
        initializeOpenGLFunctions();
    }

    render();

    context->swapBuffers(this);
    if (animating)
        renderLater();
}
