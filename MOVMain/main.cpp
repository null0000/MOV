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
    MainWindow *window = new MainWindow();

    try {
        gcImage faceImage = gcImage("face");
        window->show();
        window->setAnimating(true);
        window->attachRenderable(faceImage.toRenderable());
    } catch(ecError &e){
        ecErrorDialog *errorDialog = new ecErrorDialog(0, e.message());
        errorDialog->show();
        window->close();
    }

    qApp->setQuitOnLastWindowClosed(true);
    return a.exec();
}
