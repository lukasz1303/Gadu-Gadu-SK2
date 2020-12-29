#include "badlogindialog.h"
#include "ui_badlogindialog.h"

BadLoginDialog::BadLoginDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::BadLoginDialog)
{
    ui->setupUi(this);
}

BadLoginDialog::~BadLoginDialog()
{
    delete ui;
}

void BadLoginDialog::setLabelText(QString str)
{
    ui->label->setText(str);
}

void BadLoginDialog::on_pushButton_clicked()
{
    close();
}
