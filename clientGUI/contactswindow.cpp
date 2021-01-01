#include "contactswindow.h"
#include "ui_contactswindow.h"

ContactsWindow::ContactsWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ContactsWindow)
{
    ui->setupUi(this);

}

ContactsWindow::~ContactsWindow()
{
    delete ui;
}

void ContactsWindow::on_quitButton_clicked()
{
    QApplication::quit();
}

void ContactsWindow::on_listWidget_itemClicked(QListWidgetItem *item)
{
    mainWindow = new MainWindow(this);
    mainWindow->setWindowTitle(item->text());
    disconnect(tcpSocket,&QIODevice::readyRead,0,0);
    mainWindow->setSocket(tcpSocket);   
    mainWindow->setReceiver(numbersGG[ui->listWidget->row(item)]);

    mainWindow->ReadLastMessages(1);
    mainWindow->show();
}

void ContactsWindow::setSocket(QTcpSocket *socket)
{
    tcpSocket = socket;
    connect(tcpSocket, &QIODevice::readyRead, this,&ContactsWindow::readData);
    loadContacts();
}

void ContactsWindow::on_addButton_clicked()
{
    addContactWindow = new AddContactWindow(this);
    disconnect(tcpSocket,&QIODevice::readyRead,0,0);
    addContactWindow->setSocket(tcpSocket);
    addContactWindow->show();
}


void ContactsWindow::readData(){

    while(tcpSocket->canReadLine()){
        memset(buf,0,sizeof(buf));
        tcpSocket->readLine(buf,100);
        qDebug() << buf;

        if (strncmp(buf, "CONTACT",7) == 0){
            User *user = user->getInstance();
            std::string s = buf;
            s = s.substr(s.find("CONTACT")+8,s.length());
            QString name = QString::fromStdString(s.substr(0,s.find(":")));
            std::string gg = s.substr(s.find(":")+1,s.length());

            int number  = std::stoi(gg.substr(0,gg.find(":")));
            gg=gg.substr(gg.find(":")+1,gg.length());
            QString status=QString::fromStdString(gg);
            QListWidgetItem *item = new QListWidgetItem(name+" - "+status);
            numbersGG.push_back(number);

            ui->listWidget->addItem(item);
        }
    }
}

void ContactsWindow::loadContacts()
{
    if(tcpSocket->state() != QAbstractSocket::ConnectedState){
        tcpSocket->connectToHost("127.0.0.1", 1234);
    }
    if(tcpSocket->state() == QAbstractSocket::ConnectedState){
        if (!reading)
        {
            connect(tcpSocket, &QIODevice::readyRead, this,&ContactsWindow::readData);
        }
        QString msg = "GET_CONT:";
        User *user = user->getInstance();
        msg.append(QString::number(user->getNumberGG()));
        tcpSocket->write(msg.toLatin1());

    } else {
        infoDialog = new InfoDialog(this);
        infoDialog->setLabelText("Brak połączenia z serwerem");
        infoDialog->show();
    }

}

void ContactsWindow::on_pushButton_3_clicked()
{
    numbersGG.clear();
    ui->listWidget->clear();
    loadContacts();
}
