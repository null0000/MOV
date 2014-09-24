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
    try
    {

        return a.exec();
    }
    catch (const ecError &err) {
        ecErrorDialog ed (NULL, "Fatal Error: "+ err.message());
        ed.show();
    }

    catch (...) {
        ecErrorDialog ed (NULL, "Fatal error of unknown type. Aborting...");
        ed.show();
    }
    return 1;

}
