#ifndef SERVERSELECT_H
#define SERVERSELECT_H

#include <QDialog>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <QTcpSocket>
#include <infodialog.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include"mainwindow.h"
namespace Ui {
class serverselect;
}

class serverselect : public QDialog
{
    Q_OBJECT

public:
    explicit serverselect(QWidget *parent = nullptr);
    QString hostname="127.0.0.1";
    int portnumber=1234;


    ~serverselect();


    void setSocket(QTcpSocket *socket);
private slots:

    void connectViaIpOrDomain();
    void on_Confirm_clicked();

    void on_Cancel_clicked();
signals:
    void showParent();

private:
    Ui::serverselect *ui;
     QTcpSocket *tcpSocket;
     InfoDialog *infoDialog;
};

#endif // SERVERSELECT_H
