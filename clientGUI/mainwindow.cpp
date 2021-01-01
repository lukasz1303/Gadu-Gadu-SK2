#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMdiSubWindow>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->textEdit->setPlaceholderText("Wprowadź wiadomość");
    ui->textEdit->installEventFilter(this);

}

MainWindow::~MainWindow()
{
    delete ui;
}
bool MainWindow::eventFilter(QObject *object, QEvent *event)
{
    if (object == ui->textEdit && event->type() == QEvent::KeyPress)
    {
        QKeyEvent *keyEvent = static_cast<QKeyEvent *>(event);
        if (keyEvent->key() == Qt::Key_Return)
        {
            on_sendButton_clicked();

            return true;
        }
        else if(keyEvent->key() ==Qt::Key_Escape){
            on_closeButton_clicked();//to w sumie troche glupie
        }
        else
        {
            return QMainWindow::eventFilter(object, event);
        }
    }
    else
    {
        return QMainWindow::eventFilter(object, event);
    }
}
void MainWindow::setSocket(QTcpSocket *socket)
{
     tcpSocket = socket;
     connect(tcpSocket, &QIODevice::readyRead, this,&MainWindow::readData);

}

void MainWindow::readData(){
    char buf[1000];
    while(tcpSocket->canReadLine()){
        memset(buf,0,sizeof(buf));
        int n = tcpSocket->readLine(buf,1000);
        buf[n] = 0;
        qDebug() << buf;
        ui->textBrowser->insertPlainText(buf);
        ui->textBrowser->ensureCursorVisible();
    }
}


void MainWindow::displayError(QAbstractSocket::SocketError socketError){
    qDebug() << socketError;
}
void MainWindow::ReadLastMessages(int numberOfMessages)
{

        QByteArray msg = "GET_HISTORY:";

        msg.append(std::to_string(getReceiver()).c_str());
        msg.append(":");
        printf("%d",getReceiver());
        msg.append(std::to_string(numberOfMessages).c_str());
        tcpSocket->write(msg);
        readData();


}
void MainWindow::on_sendButton_clicked()
{
    QByteArray msg =ui->textEdit->toMarkdown().toUtf8();
    QByteArray msg2=msg;
    msg2.prepend(":");
    msg2.prepend(std::to_string(getReceiver()).c_str());
    msg2.prepend("SEND_MSG:");
    printf("%d",getReceiver());
    msg.prepend("Ty: ");

    msg = msg.left(msg.indexOf("\n"));
    tcpSocket->write(msg2);
    ui->textBrowser->insertPlainText(msg);
    ui->textBrowser->insertPlainText("\n");
    ui->textBrowser->ensureCursorVisible();
    ui->textEdit->clear();
}

void MainWindow::on_closeButton_clicked()
{
    close();
}
