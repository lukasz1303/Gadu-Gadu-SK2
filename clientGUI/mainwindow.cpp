#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMdiSubWindow>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->textEdit->setPlaceholderText("Wprowadź wiadomość");
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setSocket(QTcpSocket *socket)
{
     tcpSocket = socket;
     connect(tcpSocket, &QIODevice::readyRead, this,&MainWindow::readData);
}

void MainWindow::readData(){
    char buf[100];
    int n = tcpSocket->readLine(buf,100);
    buf[n] = 0;
    qDebug() << buf;
    ui->textBrowser->insertPlainText(buf);
    ui->textBrowser->insertPlainText("\n");
}


void MainWindow::displayError(QAbstractSocket::SocketError socketError){
    qDebug() << socketError;
}

void MainWindow::on_sendButton_clicked()
{
    QByteArray msg =ui->textEdit->toMarkdown().toUtf8();
    QByteArray msg2=msg;
    msg2.prepend(":");
    msg2.prepend(std::to_string(getReceiver()).c_str());
    msg2.prepend("SEND_MSG:");
    printf("%d",getReceiver());


    msg = msg.left(msg.lastIndexOf("\n\n"));
    tcpSocket->write(msg2);
    ui->textBrowser->insertPlainText(msg);
    ui->textBrowser->insertPlainText("\n");
    ui->textEdit->clear();
}

void MainWindow::on_closeButton_clicked()
{
    close();
}
