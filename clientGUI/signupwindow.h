#ifndef SIGNUPWINDOW_H
#define SIGNUPWINDOW_H

#include <QMainWindow>
#include <QtNetwork>
#include "infodialog.h"
#include "serverselect.h"
namespace Ui {
class SignUpWindow;
}

class SignUpWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit SignUpWindow(QWidget *parent = nullptr);
    ~SignUpWindow();
    void setSocket(QTcpSocket *socket);
    serverselect *serverSelect;
    bool CheckCredentials();
private slots:
    void on_signUpButton_clicked();
    void readData();

    void on_changeserwer_clicked();

    void on_return_2_clicked();

signals:
    void showParent();

private:
    Ui::SignUpWindow *ui;
    QTcpSocket *tcpSocket;
    InfoDialog *infoDialog;
    char buf[100];
    bool reading = false;

};

#endif // SIGNUPWINDOW_H
