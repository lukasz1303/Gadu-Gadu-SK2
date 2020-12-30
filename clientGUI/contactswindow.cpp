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
    mainWindow->setSocket(tcpSocket);
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
    int n = tcpSocket->readLine(buf,100);
    buf[n] = 0;
    qDebug() << buf;

    if (strncmp(buf, "CONTACT",7) == 0){
        User *user = user->getInstance();
        std::string s = buf;
        s = s.substr(s.find("CONTACT")+8,s.length());
        qDebug() << s.c_str();
        QString name = QString::fromStdString(s.substr(0,s.find(":")));
        QListWidgetItem *item = new QListWidgetItem(name);
        ui->listWidget->addItem(item);
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
