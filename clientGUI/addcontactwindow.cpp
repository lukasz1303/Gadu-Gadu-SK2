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

void AddContactWindow::setSocket(QTcpSocket *socket)
{
    tcpSocket = socket;
    connect(tcpSocket, &QIODevice::readyRead, this,&AddContactWindow::readData);
    reading = true;
}

void AddContactWindow::readData(){
    int n = tcpSocket->readLine(buf,100);
    buf[n] = 0;
    qDebug() << buf;

    if (strcmp(buf, "ADD_CONT:OK") == 0){
        infoDialog = new InfoDialog(this);
        infoDialog->setLabelText("Dodano znajomego");
        disconnect(tcpSocket,&QIODevice::readyRead,0,0);
        infoDialog->show();
        hide();

    } else if(strcmp(buf, "ADD_CONT:EXISTS") == 0){
        infoDialog = new InfoDialog(this);
        infoDialog->setLabelText("Już istnieje znajomy o takiej nazwie lub numerze GG");
        infoDialog->show();
    }
    else if(strcmp(buf, "ADD_CONT:NO_SIGNED") == 0){
        infoDialog = new InfoDialog(this);
        infoDialog->setLabelText("Nie istnieje osoba o takim numerze GG");
        infoDialog->show();
    }
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
        if(number.toInt() == user->getNumberGG()){
            infoDialog = new InfoDialog(this);
            infoDialog->setLabelText("Podałeś własny numer GG");
            infoDialog->show();
        } else{
            msg.append(QString::number(user->getNumberGG()));
            msg.append(":");
            msg.append(name);
            msg.append(":");
            msg.append(number);
            tcpSocket->write(msg.toLatin1());
        }


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
