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
    int getReceiver();
    void setReceiver(int ggnumber);
    void setText(QByteArray buf);
    bool eventFilter(QObject *object, QEvent *event);
    void ReadLastMessages(int numberOfMessages);
    void clear();
    QString getMyname() const;
    void setMyname(const QString &value);
    QString getReveivername() const;
    void setReveivername(const QString &value);


signals:
    void sendMessage(QByteArray buf);

private slots:
    void on_sendButton_clicked();
    void on_closeButton_clicked();

private:
    Ui::MainWindow *ui;
    QTcpSocket *tcpSocket;
    int receiver;
    bool readhistory=false;
    QString myname;
    QString reveivername;

};
#endif // MAINWINDOW_H
