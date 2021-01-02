#ifndef SIGNUPWINDOW_H
#define SIGNUPWINDOW_H

#include <QMainWindow>
#include <QtNetwork>
#include "infodialog.h"

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

private slots:
    void on_signUpButton_clicked();
    void readData();

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
