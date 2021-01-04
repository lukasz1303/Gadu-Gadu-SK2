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
    connect(this, SIGNAL(sendMessage(QByteArray)), parent, SLOT(sendMessageToServer(QByteArray)));
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
            on_closeButton_clicked();//to w sumie troche glupie - tak
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

int MainWindow::getReceiver()
{
    return receiver;
}

void MainWindow::setReceiver(int ggnumber)
{
    this->receiver=ggnumber;
}

void MainWindow::setText(QByteArray buf)
{
    ui->textBrowser->insertPlainText(buf);
    ui->textBrowser->ensureCursorVisible();
}

void MainWindow::clear(){
    ui->textBrowser->clear();
}

void MainWindow::ReadLastMessages(int numberOfMessages)
{
        QByteArray msg = "GET_HISTORY:";
        msg.append(std::to_string(getReceiver()).c_str());
        msg.append(":");
        printf("%d",getReceiver());
        msg.append(std::to_string(numberOfMessages).c_str());
        emit sendMessage(msg);
        this->readhistory=false;
}

void MainWindow::on_sendButton_clicked()
{
    QByteArray msg =ui->textEdit->toMarkdown().toUtf8();
    QByteArray msg2=msg;
    msg2.prepend(": ");
    msg2.prepend(std::to_string(getReceiver()).c_str());
    msg2.prepend("SEND_MSG:");
    msg.prepend(": ");
    msg.prepend(this->myname.QString::toUtf8());
    msg = msg.left(msg.indexOf("\n"));

    emit sendMessage(msg2);

    ui->textBrowser->insertPlainText(msg);
    ui->textBrowser->insertPlainText("\n");
    ui->textBrowser->ensureCursorVisible();
    ui->textEdit->clear();
}

void MainWindow::on_closeButton_clicked()
{
    close();
}

QString MainWindow::getReveivername() const
{
    return reveivername;
}

void MainWindow::setReveivername(const QString &value)
{
    reveivername = value;
}

QString MainWindow::getMyname() const
{
    return myname;
}

void MainWindow::setMyname(const QString &value)
{
    myname = value;
}

