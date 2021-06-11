#include "mydialog.h"
#include "ui_mydialog.h"

MyDialog::MyDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MyDialog)
{
    ui->setupUi(this);
}

MyDialog::~MyDialog()
{
    delete ui;
}

void MyDialog::on_acceptBtn_clicked()
{
    this->accept();
}

void MyDialog::on_rejectBtn_clicked()
{
    this->reject();
}

void MyDialog::on_doneBtn_clicked()
{
    this->done(1);
}
