#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMdiSubWindow>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->plainTextEdit->setPlaceholderText("Wprowadz wiadomosc");
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


void MainWindow::on_pushButton_clicked()
{
    qDebug() << ui->plainTextEdit->toPlainText();
}

void MainWindow::displayError(QAbstractSocket::SocketError socketError){
    qDebug() << socketError;
}

void MainWindow::on_sendButton_clicked()
{
    tcpSocket->write(ui->plainTextEdit->toPlainText().toLatin1().data());
    ui->textBrowser->insertPlainText(ui->plainTextEdit->toPlainText());
    ui->textBrowser->insertPlainText("\n");
    ui->plainTextEdit->clear();
}

void MainWindow::on_pushButton_3_clicked()
{
    close();
}
