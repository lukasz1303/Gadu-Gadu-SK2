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
    User *user = user->getInstance();
    if(number.toInt() == user->getNumberGG()){
        infoDialog = new InfoDialog(this);
        infoDialog->setLabelText("Podałeś własny numer GG");
        infoDialog->show();
    } else{
        msg.append(QByteArray::number(user->getNumberGG()));
        msg.append(":");
        msg.append(name);
        msg.append(":");
        msg.append(number);
        //tcpSocket->write(msg.toLatin1());
        emit sendMessage(msg);
    }

}

void AddContactWindow::on_cancelButton_clicked()
{
    close();
}
