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
    int index = ui->listWidget->row(item);
    mainWindows.at(index)->setWindowTitle(names.at(index));
    //disconnect(tcpSocket,&QIODevice::readyRead,0,0);
    mainWindows.at(index)->clear();
    mainWindows.at(index)->setSocket(tcpSocket);

    mainWindows.at(index)->setReceiver(numbersGG[index]);
    mainWindows.at(index)->reveivername=names[index];
    mainWindows.at(index)->myname=this->myname;
    mainWindows.at(index)->ReadLastMessages(1);
    mainWindows.at(index)->show();
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
            names.push_back(name);
            mainWindows.push_back(new MainWindow(this));

            ui->listWidget->addItem(item);
        } else if (strncmp(buf, "RECV_MSG",8) == 0){
            std::string s = buf;
            s = s.substr(s.find("RECV_MSG")+9,s.length());
            QString senderGG = QString::fromStdString(s.substr(0,s.find(":")));

            int index = std::distance(numbersGG.begin() ,std::find(numbersGG.begin(), numbersGG.end(), senderGG.toInt()));
            qDebug() << index;
            qDebug() << numbersGG.at(index);
            QString msg = QString::fromStdString(s.substr(s.find(":")+1,s.length()));
            msg.prepend(": ");
            msg.prepend(names.at(index));
            mainWindows.at(index)->setText(msg.toUtf8());

        } else if (strncmp(buf, "RECV_HIS",8) == 0){
            std::string s = buf;
            s = s.substr(s.find("RECV_HIS")+9,s.length());
            QString receiverGG = QString::fromStdString(s.substr(0,s.find(":")));
            int index = std::distance(numbersGG.begin() ,std::find(numbersGG.begin(), numbersGG.end(), receiverGG.toInt()));
            s=(s.substr(s.find(":")+1,s.length()));
            int nr1;
            nr1=std::stoi(s.substr(0,s.find(":")));
            s=s.substr(s.find(":"),s.length());
            qDebug()<<nr1;
            if(nr1==mainWindows.at(index)->getReceiver()){
                s=(names[index]).toStdString()+s;


            }
            else{
                s=mainWindows.at(index)->myname.toStdString()+s;


            }

            mainWindows.at(index)->setText(QByteArray::fromStdString(s));

        }
    }
}

void ContactsWindow::loadContacts()
{
    if(tcpSocket->state() != QAbstractSocket::ConnectedState){
        tcpSocket->connectToHost("127.0.0.1", 1234);
        connect(tcpSocket, &QIODevice::readyRead, this,&ContactsWindow::readData);
    }
    if(tcpSocket->state() == QAbstractSocket::ConnectedState){
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

void ContactsWindow::sendMessageToServer(QByteArray buf)
{
    qDebug() << buf;
    if(tcpSocket->state() != QAbstractSocket::ConnectedState){
        tcpSocket->connectToHost("127.0.0.1", 1234);
        if(tcpSocket->state() == QAbstractSocket::ConnectedState){
            connect(tcpSocket, &QIODevice::readyRead, this,&ContactsWindow::readData);
        }
    }
    if(tcpSocket->state() == QAbstractSocket::ConnectedState){
        tcpSocket->write(buf);
    } else {
        infoDialog = new InfoDialog(this);
        infoDialog->setLabelText("Brak połączenia z serwerem");
        infoDialog->show();
    }
}

