#include "serverselect.h"
#include "ui_serverselect.h"

#include <QStyle>

serverselect::serverselect(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::serverselect),
    tcpSocket(new QTcpSocket(this))
{
    ui->setupUi(this);
    connect(this, SIGNAL(showParent()), parent, SLOT(showWindow()));
}

serverselect::~serverselect()
{
    delete ui;
}

void serverselect::on_Confirm_clicked()
{
    connectViaIpOrDomain();
}

void serverselect::connectViaIpOrDomain(){
    QString ipordomain;
    int portNumber;
    ipordomain=ui->domainipTextEdit->text();
    struct addrinfo hints, *res, *p;
    int status;
    char ipstr[30];
    qDebug()<<(this->hostname);
    QRegExp re("[^0-9]");
    if(re.indexIn(ui->portnumber->text())<0){
        portNumber=ui->portnumber->text().toInt();

    memset(&hints, 0, sizeof hints);
    hints.ai_family = AF_INET; //IPv4
    hints.ai_socktype = SOCK_STREAM;

    std::string data = ipordomain.toUtf8().constData();
    status = getaddrinfo(data.c_str(), NULL, &hints, &res);
    if (status != 0) {

        tcpSocket->connectToHost(ipordomain, portNumber);
        tcpSocket->waitForConnected(500);
         }
   else{

        for(p = res;p != NULL; p = p->ai_next) {
             struct sockaddr_in *sa = (struct sockaddr_in *)p->ai_addr;
             inet_ntop(p->ai_family, &(sa->sin_addr), ipstr, sizeof ipstr);
             tcpSocket->connectToHost(ipstr, portNumber);

             tcpSocket->waitForConnected(500);
              }
       }
   if(tcpSocket->state() != QAbstractSocket::ConnectedState){
       infoDialog = new InfoDialog(this);
       infoDialog->setLabelText("Nie można połączyć się z podanym hostem!");
       infoDialog->show();
   }
   else{
       infoDialog = new InfoDialog(this);
       infoDialog->setLabelText("Pomyślna zmiana serwera!");
       infoDialog->show();

       this->hostname=ipstr;
       this->portnumber=portNumber;
       qDebug()<<(ipstr);
       tcpSocket->disconnectFromHost();

   }
    }
   else{
        infoDialog = new InfoDialog(this);
        infoDialog->setLabelText("Nie zgadza się numer portu!");
        infoDialog->show();

    }
}

void serverselect::setSocket(QTcpSocket *socket)
{
    tcpSocket = socket;

}
void serverselect::on_Cancel_clicked()
{

    this->hide();
}
