#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtDebug>
#include <QtNetwork>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void setSocket(QTcpSocket *socket);

private slots:

    void displayError(QAbstractSocket::SocketError socketError);
    void on_sendButton_clicked();
    void readData();
    void on_closeButton_clicked();

private:
    Ui::MainWindow *ui;
    QTcpSocket *tcpSocket;

};
#endif // MAINWINDOW_H
