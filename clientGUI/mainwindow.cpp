#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
    ui(new Ui::MainWindow),
    tcpSocket(new QTcpSocket(this))
{
    connect(tcpSocket, &QIODevice::readyRead, this,&MainWindow::readData);
    typedef void (QAbstractSocket::*QAbstractSocketErrorSignal)(QAbstractSocket::SocketError);
    connect(tcpSocket, static_cast<QAbstractSocketErrorSignal>(&QAbstractSocket::error), this, &MainWindow::displayError);
    ui->setupUi(this);
    ui->plainTextEdit->setPlaceholderText("Wprowadz wiadomosc");
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
    qDebug() << ui->plainTextEdit->toPlainText();
    tcpSocket->connectToHost("127.0.0.1", 1234);
}

void MainWindow::displayError(QAbstractSocket::SocketError socketError){
    qDebug() << socketError;
}

void MainWindow::readData(){
    char buf[100];
    int n = tcpSocket->readLine(buf,100);
    buf[n] = 0;
    qDebug() << buf;
    ui->textBrowser->insertPlainText(buf);
    ui->textBrowser->insertPlainText("\n");
}

void MainWindow::on_pushButton_2_clicked()
{
    tcpSocket->write(ui->plainTextEdit->toPlainText().toLatin1().data());
    ui->textBrowser->insertPlainText(ui->plainTextEdit->toPlainText());
    ui->textBrowser->insertPlainText("\n");
    ui->plainTextEdit->clear();
}
