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
#include <QWindow>


class waitForClose : public QObject
{

};

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    MainWindow *mw = NULL;
    ecErrorDialog *ed = NULL;
    try
    {
        glbGlobals::LogAppDir();
        mw = new MainWindow();
        mw->initialize();
        qApp->setQuitOnLastWindowClosed(true);
        return a.exec();
    }
    catch (const ecError &err) {
        ed = new ecErrorDialog(NULL, "Fatal Error: "+ err.message());
        ed->show();
        if (mw)
        {
            mw->close();
        }
    }

    catch (...) {
        ed = new ecErrorDialog(NULL, "Fatal error of unknown type. Aborting...");
        ed->show();

        if (mw)
            mw->close();
    }

    return a.exec();

}
