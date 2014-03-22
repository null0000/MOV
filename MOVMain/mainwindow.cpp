#include "mainwindow.h"


#include <QtCore/QCoreApplication>

#include <QtGui/QOpenGLContext>
#include <QtGui/QOpenGLPaintDevice>
#include <QtGui/QPainter>

#include <deque>

#include "../GraphicsCore/GraphicsCore.h"
#include <GlobalCore.h>

MainWindow *MainWindow::App = NULL;

MainWindow::MainWindow(QWindow *parent)
    : QWindow(parent)
    , m_update_pending(false)
    , m_animating(false)
    , m_context(0)
    , m_device(0)
    , inputDevice(*this)
{
    setSurfaceType(QWindow::OpenGLSurface);


    //THERE CAN ONLY BE ONE
    //.... despite the fact that that's generally bad programming practices. Oh well.
    Q_ASSERT(!App);
    App = this;
}

void MainWindow::render(QPainter *painter)
{
    gcDrawingImpl drawDevice(*painter);

    for (std::deque<gcRenderable *>::iterator itr = renderables.begin(); itr != renderables.end(); itr++)
        (*itr)->draw(drawDevice);
}

void MainWindow::initialize()
{
}

void MainWindow::render()
{
    if (!m_device)
        m_device = new QOpenGLPaintDevice;

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

    m_device->setSize(size());

    QPainter painter(m_device);
    render(&painter);
}

void MainWindow::renderLater()
{
    if (!m_update_pending) {
        m_update_pending = true;
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

    m_update_pending = false;

    bool needsInitialize = false;

    if (!m_context) {
        m_context = new QOpenGLContext(this);
        m_context->setFormat(requestedFormat());
        m_context->create();

        needsInitialize = true;
    }

    m_context->makeCurrent(this);

    if (needsInitialize) {
        initializeOpenGLFunctions();
        initialize();
    }

    render();

    m_context->swapBuffers(this);
    if (m_animating)
        renderLater();
}

void MainWindow::setAnimating(bool animating)
{
    m_animating = animating;

    if (animating)
        renderLater();
}

void MainWindow::attachRenderable(gcRenderable *renderable)
{
    renderables.push_back(renderable);
}
