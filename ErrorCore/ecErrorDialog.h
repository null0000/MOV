#ifndef ERRORDIALOG_H
#define ERRORDIALOG_H

#include <QWidget>
#include <QDialog>

#include "errorcore_ie.h"

namespace Ui {
class ErrorDialog;
}

class ERR_IE ecErrorDialog : public QDialog
{
    Q_OBJECT


public:
    explicit ecErrorDialog(QWidget *parent = 0);
    ecErrorDialog(QWidget *parent, QString Message);


    QPushButton *__getPushButton();

    ~ecErrorDialog();

signals:
    void closeButtonPressed();

private slots:
    void on_CloseButton_clicked();

private:
    Ui::ErrorDialog *ui;


    //UNIT TESTING GARBAGE

};

#endif // ERRORDIALOG_H
