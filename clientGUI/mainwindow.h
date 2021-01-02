#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtDebug>
#include <QtNetwork>
#include<QKeyEvent>
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
    int getReceiver();
    void setReceiver(int ggnumber);
    void setText(QByteArray buf);
    bool eventFilter(QObject *object, QEvent *event);
    void ReadLastMessages(int numberOfMessages);
    QString myname;
    QString reveivername;
    bool readhistory=false;
    void clear();
signals:
    void sendMessage(QByteArray buf);

private slots:

    void displayError(QAbstractSocket::SocketError socketError);
    void on_sendButton_clicked();
    void readData();
    void on_closeButton_clicked();

private:
    Ui::MainWindow *ui;
    QTcpSocket *tcpSocket;
    int receiver;



};
#endif // MAINWINDOW_H
