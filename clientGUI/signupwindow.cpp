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
        msg.append(ui->nrGGTextEdit->toPlainText());
        msg.append(":");
        msg.append(ui->passTextEdit->toPlainText());
        tcpSocket->write(msg.toLatin1());
    } else if (re2.indexIn(nrGG)>=0)
    {
        badlogindialog = new BadLoginDialog(this);
        badlogindialog->setLabelText("Nr Gadu-Gadu musi składać się wyłącznie z cyfr");
        badlogindialog->show();
    }
    else
    {
        badlogindialog = new BadLoginDialog(this);
        badlogindialog->show();
    }
}

void SignUpWindow::setSocket(QTcpSocket *socket)
{
    tcpSocket = socket;
}
