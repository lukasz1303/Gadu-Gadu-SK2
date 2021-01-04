#include "contactswindow.h"
#include "ui_contactswindow.h"

ContactsWindow::ContactsWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ContactsWindow)
{
    ui->setupUi(this);
    ui->listWidget->setSpacing(3);
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
    mainWindows.at(index)->clear();
    mainWindows.at(index)->setReceiver(numbersGG[index]);
    mainWindows.at(index)->setReveivername(names[index]);
    mainWindows.at(index)->setMyname(this->myName);
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

    if (addContactWindow == NULL || addContactWindow->isHidden()){
        addContactWindow = new AddContactWindow(this);
        addContactWindow->show();
    }
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
            std::string statusStr = gg.substr(gg.find(":")+1,gg.length());
            statusStr = statusStr.substr(0,statusStr.find("\n"));
            QIcon statusIcon;
            if (statusStr.compare("online")==0){
                 statusIcon = QIcon(":/images/online.png");
            } else {
                 statusIcon = QIcon(":/images/offline.png");
            }

            QListWidgetItem *item = new QListWidgetItem(name);
            item->setIcon(statusIcon);
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
            msg.prepend(":");
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
                s=mainWindows.at(index)->getMyname().toStdString()+s;
            }
            mainWindows.at(index)->setText(QByteArray::fromStdString(s));
        } else if (strncmp(buf, "ADD_CONT:OK",11) == 0){
            infoDialog = new InfoDialog(this);
            infoDialog->setLabelText("Dodano znajomego");
            infoDialog->show();
            numbersGG.clear();
            names.clear();
            ui->listWidget->clear();
            loadContacts();
            addContactWindow->hide();

        } else if(strncmp(buf, "ADD_CONT:EXISTS",15) == 0){
            infoDialog = new InfoDialog(addContactWindow);
            infoDialog->setLabelText("Już istnieje znajomy o takiej nazwie lub numerze GG");
            infoDialog->show();

        } else if(strncmp(buf, "ADD_CONT:NO_SIGNED",18) == 0){
            infoDialog = new InfoDialog(addContactWindow);
            infoDialog->setLabelText("Nie istnieje osoba o takim numerze GG");
            infoDialog->show();
        }
    }
}

void ContactsWindow::loadContacts()
{
    if(tcpSocket->state() != QAbstractSocket::ConnectedState){
        tcpSocket->connectToHost("127.0.0.1", 1234);
        tcpSocket->waitForConnected(500);
    }
    if(tcpSocket->state() == QAbstractSocket::ConnectedState){
        QString msg = "GET_CONT:";
        User *user = user->getInstance();
        msg.append(QString::number(user->getNumberGG()));
        msg.append('\n');
        tcpSocket->write(msg.toLatin1());

    }
}

QString ContactsWindow::getMyName() const
{
    return myName;
}

void ContactsWindow::setMyName(const QString &value)
{
    myName = value;
}

void ContactsWindow::sendMessageToServer(QByteArray buf)
{
    qDebug() << buf;
    if(tcpSocket->state() != QAbstractSocket::ConnectedState){
        tcpSocket->connectToHost("127.0.0.1", 1234);
        tcpSocket->waitForConnected(500);
    }
    if(tcpSocket->state() == QAbstractSocket::ConnectedState){
        buf.append("\n");
        tcpSocket->write(buf);
    }
}

void ContactsWindow::on_refreshButton_clicked()
{
    numbersGG.clear();
    names.clear();
    ui->listWidget->clear();
    loadContacts();
}
