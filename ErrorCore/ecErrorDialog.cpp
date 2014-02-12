#include "ErrorCore.h"
#include "ecErrorDialog.h"
#include "ui_errordialog.h"

ecErrorDialog::ecErrorDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ErrorDialog)
{
    ui->setupUi(this);
}

ecErrorDialog::ecErrorDialog(QWidget *parent, QString Message) :
    QDialog(parent),
    ui(new Ui::ErrorDialog)
{
    ui->setupUi(this);
    ui->label->setText(Message);
    setWindowTitle("Error");
}


ecErrorDialog::~ecErrorDialog()
{
    delete ui;
}

void ecErrorDialog::on_CloseButton_clicked()
{
    setVisible(false);
    emit closeButtonPressed();
}


QPushButton *ecErrorDialog::getPushButton()
{
    return ui->CloseButton;
}
