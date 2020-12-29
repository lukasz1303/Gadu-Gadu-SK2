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
    ui->passwordLineEdit->setEchoMode(QLineEdit::Password);

}

LoginWindow::~LoginWindow()
{
    delete ui;
}

void LoginWindow::displayError(QAbstractSocket::SocketError socketError){
    qDebug() << socketError;
}

void LoginWindow::readData(){
    int n = tcpSocket->readLine(buf,100);
    buf[n] = 0;
    qDebug() << buf;

    if (strcmp(buf, "OK") == 0){
        hide();
        contactsWindows = new ContactsWindow(this);
        disconnect(tcpSocket,&QIODevice::readyRead,0,0);
        contactsWindows->setSocket(tcpSocket);
        contactsWindows->show();
    } else {
        infoDialog = new InfoDialog(this);
        infoDialog->setLabelText("Podano nieprawidłowy login lub hasło");
        infoDialog->show();
    }
}

void LoginWindow::on_signInButton_clicked()
{
    QString msg = "SIGN_IN:";
    QRegExp re("[^A-Za-z0-9]");
    QString login = ui->loginTextEdit->toPlainText();
    QString password = ui->passwordLineEdit->text();
    if(re.indexIn(login)<0 && re.indexIn(password)<0)
    {
        msg.append(login);
        msg.append(":");
        msg.append(password);
        tcpSocket->write(msg.toLatin1());
    }
    else
    {
        infoDialog = new InfoDialog(this);
        infoDialog->show();
    }

}

void LoginWindow::on_signUpButton_clicked()
{
    signUpWindow = new SignUpWindow(this);
    disconnect(tcpSocket,&QIODevice::readyRead,0,0);
    signUpWindow->setSocket(tcpSocket);
    signUpWindow->show();
}

