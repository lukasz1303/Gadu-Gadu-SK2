#include "signupwindow.h"
#include "ui_signupwindow.h"

SignUpWindow::SignUpWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::SignUpWindow)
{
    ui->setupUi(this);
    connect(this, SIGNAL(showParent()), parent, SLOT(showWindow()));
}

SignUpWindow::~SignUpWindow()
{
    delete ui;
}

void SignUpWindow::on_signUpButton_clicked()
{
    QString msg = "SIGN_UP:";
    QRegExp re("[^A-Za-z0-9]");
    QRegExp re2("[^0-9]");
    QString login = ui->loginTextEdit->toPlainText();
    QString nrGG = ui->nrGGTextEdit->toPlainText();
    QString password = ui->passTextEdit->toPlainText();

    if(re.indexIn(login)<0 && re.indexIn(password)<0 && re2.indexIn(nrGG)<0)
    {
        if(tcpSocket->state() != QAbstractSocket::ConnectedState){
            tcpSocket->connectToHost("127.0.0.1", 1234);
            tcpSocket->waitForConnected(500);
        }
        if(tcpSocket->state() == QAbstractSocket::ConnectedState){
            if (!reading){
               connect(tcpSocket, &QIODevice::readyRead, this,&SignUpWindow::readData);
            }
            msg.append(ui->loginTextEdit->toPlainText());
            msg.append(":");
            msg.append(ui->passTextEdit->toPlainText());
            msg.append(":");
            msg.append(ui->nrGGTextEdit->toPlainText());
            tcpSocket->write(msg.toLatin1());
        }else {
            infoDialog = new InfoDialog(this);
            infoDialog->setLabelText("Brak połączenia z serwerem");
            infoDialog->show();
        }

    }
    else if (re2.indexIn(nrGG)>=0)
    {
        infoDialog = new InfoDialog(this);
        infoDialog->setLabelText("Nr Gadu-Gadu musi składać się wyłącznie z cyfr");
        infoDialog->show();
    }
    else
    {
        infoDialog = new InfoDialog(this);
        infoDialog->show();
    }
}

void SignUpWindow::setSocket(QTcpSocket *socket)
{
    tcpSocket = socket;
    connect(tcpSocket, &QIODevice::readyRead, this,&SignUpWindow::readData);
    reading = true;
}

void SignUpWindow::readData(){
    int n = tcpSocket->readLine(buf,100);
    buf[n] = 0;

    if (strcmp(buf, "SIGN_UP:OK") == 0){
        infoDialog = new InfoDialog(this);
        infoDialog->setLabelText("Rejestracja zakończona pomyślnie");
        disconnect(tcpSocket,&QIODevice::readyRead,0,0);
        hide();
        emit showParent();
        infoDialog->show();
    } else {
        infoDialog = new InfoDialog(this);
        infoDialog->setLabelText("Rejestracja zakończona niepowodzeniem");
        infoDialog->show();
    }
}
