#include "mainwindow.h"


#include <QtCore/QCoreApplication>

#include <QtGui/QOpenGLContext>
#include <QtGui/QOpenGLPaintDevice>
#include <QtGui/QPainter>

#include <deque>

#include<GraphicsCore.h>
#include <GlobalCore.h>
#include <CompositionCore.h>

MainWindow *MainWindow::App = NULL;

MainWindow::MainWindow(QWindow *parent)
    : QWindow(parent)
    , updatePending(false)
    , animating(false)
    , renderList()
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

void MainWindow::render(QPainter *painter){gcDrawingImpl drawDevice(*painter);}

void MainWindow::initialize(){

    scWorld *world = new scWorld();
    ccBootUp(*world, renderList, inputDevice);

}

void MainWindow::render()
{
    if (!device)
        device = new QOpenGLPaintDevice;

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

    device->setSize(size());

    QPainter painter(device);
    render(&painter);
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

    if (needsInitialize) {
        initializeOpenGLFunctions();
        initialize();
    }

    render();

    context->swapBuffers(this);
    if (animating)
        renderLater();
}

void MainWindow::setAnimating(bool animating)
{
    animating = animating;

    if (animating)
        renderLater();
}

void MainWindow::attachRenderable(gcRenderable *renderable)
{
    renderList.pushRenderable(renderable);
}
