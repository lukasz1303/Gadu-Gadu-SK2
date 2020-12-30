#ifndef CONTACTSWINDOW_H
#define CONTACTSWINDOW_H

#include <QMainWindow>
#include <QListWidgetItem>
#include "mainwindow.h"
#include "addcontactwindow.h"
#include "infodialog.h"

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
    void on_addButton_clicked();
    void readData();

private:
    void loadContacts();
    Ui::ContactsWindow *ui;
    QTcpSocket *tcpSocket;
    MainWindow *mainWindow;
    InfoDialog *infoDialog;
    AddContactWindow *addContactWindow;
    char buf[100];
    bool reading = false;
};

#endif // CONTACTSWINDOW_H
