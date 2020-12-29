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
    msg.append(ui->loginTextEdit->toPlainText());
    msg.append(":");
    msg.append(ui->nrGGTextEdit->toPlainText());
    msg.append(":");
    msg.append(ui->passTextEdit->toPlainText());
    tcpSocket->write(msg.toLatin1());
}

void SignUpWindow::setSocket(QTcpSocket *socket)
{
    tcpSocket = socket;
}
