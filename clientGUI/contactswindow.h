#ifndef CONTACTSWINDOW_H
#define CONTACTSWINDOW_H

#include <QMainWindow>
#include <QListWidgetItem>
#include "mainwindow.h"

namespace Ui {
class ContactsWindow;
}

class ContactsWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit ContactsWindow(QWidget *parent = nullptr);
    ~ContactsWindow();
    void setSocket(QTcpSocket *socket);

private slots:
    void on_quitButton_clicked();

    void on_listWidget_itemClicked(QListWidgetItem *item);

    void on_pushButton_4_clicked();


private:
    Ui::ContactsWindow *ui;
    QTcpSocket *tcpSocket;
    MainWindow *mainWindow;
};

#endif // CONTACTSWINDOW_H
