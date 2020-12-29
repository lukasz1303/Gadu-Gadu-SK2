#include "infodialog.h"
#include "ui_infodialog.h"

InfoDialog::InfoDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::InfoDialog)
{
    ui->setupUi(this);
}

InfoDialog::~InfoDialog()
{
    delete ui;
}

void InfoDialog::setLabelText(QString str)
{
    ui->label->setText(str);
}

void InfoDialog::on_pushButton_clicked()
{
    close();
}
