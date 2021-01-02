#ifndef ADDCONTACTWINDOW_H
#define ADDCONTACTWINDOW_H

#include <QMainWindow>
#include <QtDebug>
#include <QtNetwork>
#include "infodialog.h"
#include "user.h"

namespace Ui {
class AddContactWindow;
}

class AddContactWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit AddContactWindow(QWidget *parent = nullptr);
    ~AddContactWindow();
    void setSocket(QTcpSocket *socket);

private slots:
    void readData();

    void on_addButton_clicked();

    void on_cancelButton_clicked();

signals:
    void sendMessage(QByteArray buf);

private:
    Ui::AddContactWindow *ui;
    QTcpSocket *tcpSocket;
    InfoDialog *infoDialog;
    char buf[100];
    bool reading = false;
};

#endif // ADDCONTACTWINDOW_H
