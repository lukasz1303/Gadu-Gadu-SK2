#ifndef CONTACTSWINDOW_H
#define CONTACTSWINDOW_H

#include <QMainWindow>
#include <QListWidgetItem>
#include <vector>
#include "mainwindow.h"
#include "addcontactwindow.h"
#include "infodialog.h"
#include "serverselect.h"

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
    QString getMyName() const;
    void setMyName(const QString &value);
    int getMyGG() const;
    void setMyGG(int value);
    serverselect *serverSelect;

private slots:
    void on_quitButton_clicked();
    void on_listWidget_itemClicked(QListWidgetItem *item);
    void on_addButton_clicked();
    void readData();
    void on_refreshButton_clicked();

public slots:
    void sendMessageToServer(QByteArray buf);

private:
    void loadContacts();
    Ui::ContactsWindow *ui;
    QTcpSocket *tcpSocket;
    InfoDialog *infoDialog;
    AddContactWindow *addContactWindow = NULL;
    char buf[500];
    std::vector<int> numbersGG;
    std::vector<QString> names;
    std::vector<MainWindow *> mainWindows;
    QString myName;
    int myGG;

};

#endif // CONTACTSWINDOW_H
