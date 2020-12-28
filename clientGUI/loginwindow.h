#ifndef LOGINWINDOW_H
#define LOGINWINDOW_H

#include <QMainWindow>
#include <QtDebug>
#include <QtNetwork>
#include "contactswindow.h"

namespace Ui {
class LoginWIndow;
}

class LoginWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit LoginWindow(QWidget *parent = nullptr);
    ~LoginWindow();

private slots:
    void displayError(QAbstractSocket::SocketError socketError);
    void readData();
    void on_pushButton_clicked();

private:
    Ui::LoginWIndow *ui;
    QTcpSocket *tcpSocket;
    ContactsWindow *contactsWindows;
};

#endif // LOGINWINDOW_H
