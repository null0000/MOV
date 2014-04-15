#include <QApplication>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QDir>

#include <iostream>

#include "mainwindow.h"
#include <GraphicsCore.h>
#include <ErrorCore.h>
#include <ecErrorDialog.h>
#include <GlobalCore.h>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    glbGlobals::LogAppDir();
    (new MainWindow())->initialize();
    qApp->setQuitOnLastWindowClosed(true);
    return a.exec();
}
