#ifndef LOGINWINDOW_H
#define LOGINWINDOW_H

#include <QMainWindow>
#include <QtDebug>
#include <QtNetwork>
#include <string>
#include "contactswindow.h"
#include "signupwindow.h"
#include "badlogindialog.h"

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
    void on_signInButton_clicked();

    void on_signUpButton_clicked();

private:
    Ui::LoginWIndow *ui;
    QTcpSocket *tcpSocket;
    ContactsWindow *contactsWindows;
    SignUpWindow *signUpWindow;
    BadLoginDialog *badlogindialog;
};

#endif // LOGINWINDOW_H
