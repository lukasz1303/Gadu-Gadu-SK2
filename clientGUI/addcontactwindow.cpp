#include "addcontactwindow.h"
#include "ui_addcontactwindow.h"

AddContactWindow::AddContactWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::AddContactWindow)
{
    ui->setupUi(this);
}

AddContactWindow::~AddContactWindow()
{
    delete ui;
}

void AddContactWindow::setSocket(QTcpSocket *socket)
{
    tcpSocket = socket;
    connect(tcpSocket, &QIODevice::readyRead, this,&AddContactWindow::readData);
    reading = true;
}

void AddContactWindow::readData(){
    int n = tcpSocket->readLine(buf,100);
    buf[n] = 0;
}
void AddContactWindow::on_addButton_clicked()
{
    if(tcpSocket->state() != QAbstractSocket::ConnectedState){
        tcpSocket->connectToHost("127.0.0.1", 1234);
    }
    if(tcpSocket->state() == QAbstractSocket::ConnectedState){
        if (!reading){
            connect(tcpSocket, &QIODevice::readyRead, this,&AddContactWindow::readData);
        }
        QString msg = "ADD_CONT:";
        QString name = ui->nameTextEdit->toPlainText();
        QString number = ui->numberTextEdit->toPlainText();
        User *user = user->getInstance();
        msg.append(QString::number(user->getNumberGG()));
        msg.append(":");
        msg.append(name);
        msg.append(":");
        msg.append(number);
        tcpSocket->write(msg.toLatin1());

    } else {
        infoDialog = new InfoDialog(this);
        infoDialog->setLabelText("Brak połączenia z serwerem");
        infoDialog->show();
    }
}

void AddContactWindow::on_cancelButton_clicked()
{
    close();
}
