#ifndef LOGINWINDOW_H
#define LOGINWINDOW_H

#include <QMainWindow>
#include <QtDebug>
#include <QtNetwork>
#include <QDesktopWidget>
#include <string>
#include "contactswindow.h"
#include "signupwindow.h"
#include "infodialog.h"
#include "serverselect.h"
namespace Ui {
class LoginWIndow;
}

class LoginWindow : public QMainWindow
{
    Q_OBJECT

public:
    QString login;
    serverselect *serverSelect;
    explicit LoginWindow(QWidget *parent = nullptr);
    ~LoginWindow();

private slots:
    void displayError(QAbstractSocket::SocketError socketError);
    void readData();
    void on_signInButton_clicked();
    void on_signUpButton_clicked();

    void on_pushButton_clicked();

public slots:
    void showWindow();

private:
    Ui::LoginWIndow *ui;
    QTcpSocket *tcpSocket;
    ContactsWindow *contactsWindows;
    SignUpWindow *signUpWindow;
    InfoDialog *infoDialog;
    char buf[100];

};

#endif // LOGINWINDOW_H
