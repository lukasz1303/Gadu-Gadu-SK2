#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMdiSubWindow>
#include <QtCore>
#include <QtGui>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->textEdit->setPlaceholderText("Wprowadź wiadomość");
    ui->textCounter->setText("0/250");
    ui->textEdit->installEventFilter(this);
    connect(ui->textEdit,  SIGNAL(textChanged ()),   this,  SLOT(contents_changed()));
    connect(this, SIGNAL(sendMessage(QByteArray)), parent, SLOT(sendMessageToServer(QByteArray)));
}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::contents_changed(){
    QString textContent = ui->textEdit->toPlainText();


    int length = textContent.count();
    int maxLength = 250;
    ui->textCounter->clear();
    if(length > maxLength) {
        int position = ui->textEdit->textCursor().position();
        QTextCursor textCursor = ui->textEdit->textCursor();

        textContent.remove(position-(length-maxLength), length-maxLength);
        ui->textEdit->setText(textContent);
        textCursor.setPosition(position-(length-maxLength));
        ui->textEdit->setTextCursor(textCursor);

        ui->textCounter->setText(QString::fromStdString(std::to_string(maxLength)+"/"+std::to_string(maxLength)));
    }
    else{
    ui->textCounter->setText(QString::fromStdString(std::to_string(length)+"/"+std::to_string(maxLength)));}
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
void MainWindow::messageLength(QByteArray message){

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

