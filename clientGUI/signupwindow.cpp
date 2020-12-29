#include "signupwindow.h"
#include "ui_signupwindow.h"

SignUpWindow::SignUpWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::SignUpWindow)
{
    ui->setupUi(this);
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
        msg.append(ui->loginTextEdit->toPlainText());
        msg.append(":");
        msg.append(ui->passTextEdit->toPlainText());
        msg.append(":");
        msg.append(ui->nrGGTextEdit->toPlainText());
        tcpSocket->write(msg.toLatin1());

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
}

void SignUpWindow::readData(){
    int n = tcpSocket->readLine(buf,100);
    buf[n] = 0;

    if (strcmp(buf, "OK") == 0){
        infoDialog = new InfoDialog(this);
        infoDialog->setLabelText("Rejestracja zakończona pomyślnie");
        hide();
        infoDialog->show();
    } else {
        infoDialog = new InfoDialog(this);
        infoDialog->setLabelText("Rejestracja zakończona niepowodzeniem");
        infoDialog->show();
    }

}
