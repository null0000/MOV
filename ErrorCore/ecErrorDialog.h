#ifndef ERRORDIALOG_H
#define ERRORDIALOG_H

#include <QWidget>
#include <QDialog>

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

private slots:
    void on_CloseButton_clicked();

private:
    Ui::ErrorDialog *ui;
};

#endif // ERRORDIALOG_H
