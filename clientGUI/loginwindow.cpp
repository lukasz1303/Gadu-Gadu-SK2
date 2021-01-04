#include "loginwindow.h"
#include "ui_loginwindow.h"

LoginWindow::LoginWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::LoginWIndow),
    tcpSocket(new QTcpSocket(this))
{
    ui->setupUi(this);
    connect(tcpSocket, &QIODevice::readyRead, this,&LoginWindow::readData);
    typedef void (QAbstractSocket::*QAbstractSocketErrorSignal)(QAbstractSocket::SocketError);
    connect(tcpSocket, static_cast<QAbstractSocketErrorSignal>(&QAbstractSocket::error), this, &LoginWindow::displayError);   
    ui->passwordLineEdit->setEchoMode(QLineEdit::Password);
    tcpSocket->connectToHost("127.0.0.1", 1234);
}

LoginWindow::~LoginWindow()
{
    delete ui;
}

void LoginWindow::displayError(QAbstractSocket::SocketError socketError){
    if(socketError==QAbstractSocket::RemoteHostClosedError){
        infoDialog = new InfoDialog(this);
        infoDialog->setLabelText("Serwer uległ awarii lub osiagnął limit użytkownikow - spróbuj ponownie później");
        infoDialog->setGeometry(
                    QStyle::alignedRect(
                        Qt::LeftToRight,
                    Qt::AlignCenter,
                        infoDialog->size(),
                        qApp->desktop()->availableGeometry()));
        infoDialog->show();
    }
    else if(socketError==QAbstractSocket::ConnectionRefusedError){
        infoDialog = new InfoDialog(this);
        infoDialog->setLabelText("Brak połączenia z serwerem");
        infoDialog->setGeometry(
                    QStyle::alignedRect(
                        Qt::LeftToRight,
                    Qt::AlignCenter,
                        infoDialog->size(),
                        qApp->desktop()->availableGeometry()));
        infoDialog->show();
    }

    qDebug() << socketError;
}

void LoginWindow::readData(){
    int n = tcpSocket->readLine(buf,100);
    buf[n] = 0;
    qDebug() << buf;

    if (strncmp(buf, "SIGN_IN:OK",10) == 0){
        User *user = user->getInstance();
        std::string s = buf;
        user->setNumberGG(std::stoi(s.substr(s.find("SIGN_IN:OK:") + strlen("SIGN_IN:OK:"))));
        hide();
        disconnect(tcpSocket,&QIODevice::readyRead,0,0);
        contactsWindows = new ContactsWindow(this);
        contactsWindows->setSocket(tcpSocket);
        contactsWindows->setMyName(login);
        contactsWindows->show();
    } else if(strcmp(buf, "SIGN_IN:ERROR") == 0){
        infoDialog = new InfoDialog(this);
        infoDialog->setLabelText("Podano nieprawidłowy login lub hasło");
        infoDialog->show();
    }
    else if(strcmp(buf,"SIGN_IN:LOGGED")==0){
        infoDialog = new InfoDialog(this);
        infoDialog->setLabelText("To konto jest w tej chwili w użytku - wyloguj sie z pozostalych urządzeń by z niego korzystać!");
        infoDialog->show();
    }
}

void LoginWindow::on_signInButton_clicked()
{
    if(tcpSocket->state() != QAbstractSocket::ConnectedState){
        tcpSocket->connectToHost("127.0.0.1", 1234);
        tcpSocket->waitForConnected(500);
    }
    if(tcpSocket->state() == QAbstractSocket::ConnectedState){
        QString msg = "SIGN_IN:";
        QRegExp re("[^A-Za-z0-9]");
        this->login = ui->loginTextEdit->toPlainText();
        QString password = ui->passwordLineEdit->text();

        if(re.indexIn(login)<0 && re.indexIn(password)<0)
        {
            msg.append(login);
            msg.append(":");
            msg.append(password);
            msg.append('\n');
            tcpSocket->write(msg.toLatin1());
        }
        else
        {
            infoDialog = new InfoDialog(this);
            infoDialog->show();
        }
    }

}

void LoginWindow::on_signUpButton_clicked()
{
    signUpWindow = new SignUpWindow(this);
    disconnect(tcpSocket,&QIODevice::readyRead,0,0);
    signUpWindow->setSocket(tcpSocket);
    signUpWindow->show();
    hide();
}

void LoginWindow::showWindow()
{
    show();
    connect(tcpSocket, &QIODevice::readyRead, this,&LoginWindow::readData);
}

