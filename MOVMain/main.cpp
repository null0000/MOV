#include <QApplication>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QDir>

#include <iostream>

#include "mainwindow.h"
#include "../GraphicsCore/GraphicsCore.h"
#include "../ErrorCore/ErrorCore.h"
#include "../ErrorCore/ecErrorDialog.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    try{

        MainWindow *window = new MainWindow();

        QDir::setCurrent("C:\\Users\\null\\MOV");

        gcImage faceImage = gcImage(QString("faced.gif"));

        window->show();
        window->setAnimating(true);
        window->attachRenderable(faceImage.toRenderable());
    } catch(ecError &e){
        ecErrorDialog *errorDialog = new ecErrorDialog(0, e.message());
        errorDialog->show();
    }

    return a.exec();
}
