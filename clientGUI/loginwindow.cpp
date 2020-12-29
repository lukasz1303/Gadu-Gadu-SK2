#include "loginwindow.h"
#include "ui_loginwindow.h"

LoginWindow::LoginWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::LoginWIndow),
    tcpSocket(new QTcpSocket(this))
{
    connect(tcpSocket, &QIODevice::readyRead, this,&LoginWindow::readData);
    typedef void (QAbstractSocket::*QAbstractSocketErrorSignal)(QAbstractSocket::SocketError);
    connect(tcpSocket, static_cast<QAbstractSocketErrorSignal>(&QAbstractSocket::error), this, &LoginWindow::displayError);
    ui->setupUi(this);
    tcpSocket->connectToHost("127.0.0.1", 1234);

}

LoginWindow::~LoginWindow()
{
    delete ui;
}

void LoginWindow::displayError(QAbstractSocket::SocketError socketError){
    qDebug() << socketError;
}

void LoginWindow::readData(){
    char buf[100];
    int n = tcpSocket->readLine(buf,100);
    buf[n] = 0;
    qDebug() << buf;
   // ui->textBrowser->insertPlainText(buf);
    //ui->textBrowser->insertPlainText("\n");
}

void LoginWindow::on_signInButton_clicked()
{
    QString msg = "SIGN_IN:";
    msg.append(ui->textEdit->toPlainText());
    msg.append(":");
    msg.append(ui->textEdit_2->toPlainText());
    tcpSocket->write(msg.toLatin1());

    hide();
    contactsWindows = new ContactsWindow(this);
    disconnect(tcpSocket,&QIODevice::readyRead,0,0);
    contactsWindows->setSocket(tcpSocket);
    contactsWindows->show();

}

void LoginWindow::on_signUpButton_clicked()
{
    signUpWindow = new SignUpWindow(this);
    signUpWindow->setSocket(tcpSocket);
    signUpWindow->show();
}
