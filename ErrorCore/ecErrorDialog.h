#ifndef ERRORDIALOG_H
#define ERRORDIALOG_H

#include <QWidget>
#include <QDialog>

class testErrorRegister; //UNIT TESTING

namespace Ui {
class ErrorDialog;
}

class ecErrorDialog : public QDialog
{
    Q_OBJECT


public:
    explicit ecErrorDialog(QWidget *parent = 0);
    ecErrorDialog(QWidget *parent, QString Message);

    ~ecErrorDialog();

signals:
    void closeButtonPressed();

private slots:
    void on_CloseButton_clicked();

private:
    Ui::ErrorDialog *ui;


    //UNIT TESTING GARBAGE

    friend testErrorRegister;
    QPushButton *getPushButton();
};

#endif // ERRORDIALOG_H
