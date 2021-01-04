#include "addcontactwindow.h"
#include "ui_addcontactwindow.h"

AddContactWindow::AddContactWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::AddContactWindow)
{
    ui->setupUi(this);
    connect(this, SIGNAL(sendMessage(QByteArray)), parent, SLOT(sendMessageToServer(QByteArray)));
}

AddContactWindow::~AddContactWindow()
{
    delete ui;
}


void AddContactWindow::on_addButton_clicked()
{

    QByteArray msg = "ADD_CONT:";
    QByteArray name = ui->nameTextEdit->toPlainText().toUtf8();
    QByteArray number = ui->numberTextEdit->toPlainText().toUtf8();
    if(number.toInt() == myGG){
        infoDialog = new InfoDialog(this);
        infoDialog->setLabelText("Podałeś własny numer GG");
        infoDialog->show();
    } else{
        msg.append(QByteArray::number(myGG));
        msg.append(":");
        msg.append(name);
        msg.append(":");
        msg.append(number);
        emit sendMessage(msg);
    }

}

void AddContactWindow::on_cancelButton_clicked()
{
    close();
}

int AddContactWindow::getMyGG() const
{
    return myGG;
}

void AddContactWindow::setMyGG(int value)
{
    myGG = value;
}
