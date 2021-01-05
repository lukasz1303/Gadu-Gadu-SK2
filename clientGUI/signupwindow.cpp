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
bool SignUpWindow::CheckCredentials(){
    QString login = ui->loginTextEdit->toPlainText();
    QString nrGG = ui->nrGGTextEdit->toPlainText();
    QString password = ui->passTextEdit->toPlainText();
    bool result=true;
    QString errorMessage;
    if(login.length()>12 || login.length()<3){
        result=false;
        errorMessage="Dlugosc loginu powinna wynosic miedzy 3 a 12 znakami!\n";

    }
    else if(nrGG.length()>12||nrGG.length()<4){
        result=false;
        errorMessage="Dlugosc numeru GG powinna wynosic miedzy 4 a 12 cyframi!\n";

    }
    else if(password.length()>16||password.length()<4){
        result=false;
        errorMessage="Dlugosc hasla powinna wynosic miedzy 4 a 16 znakami!\n";
    }
    if(!result){

        infoDialog = new InfoDialog(this);

        infoDialog->setLabelText(errorMessage);
        infoDialog->adjustSize();
        infoDialog->show();
        return result;

    }

    return true;


}
void SignUpWindow::on_signUpButton_clicked()
{
    QString msg = "SIGN_UP:";
    QRegExp re("[^A-Za-z0-9]");
    QRegExp re2("[^0-9]");
    QString login = ui->loginTextEdit->toPlainText();
    QString nrGG = ui->nrGGTextEdit->toPlainText();
    QString password = ui->passTextEdit->toPlainText();
    bool lengthCorrectness=CheckCredentials();
    if(re.indexIn(login)<0 && re.indexIn(password)<0 && re2.indexIn(nrGG)<0&&lengthCorrectness)
    {
        if(tcpSocket->state() != QAbstractSocket::ConnectedState){
            tcpSocket->connectToHost(serverSelect->hostname, serverSelect->portnumber);
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
            msg.append('\n');
            tcpSocket->write(msg.toLatin1());
        }

    }
    else if(!lengthCorrectness){

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

void SignUpWindow::on_changeserwer_clicked()
{


    this->serverSelect->show();
}

void SignUpWindow::on_return_2_clicked()
{
    hide();
    emit showParent();
}
