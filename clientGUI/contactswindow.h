#ifndef CONTACTSWINDOW_H
#define CONTACTSWINDOW_H

#include <QMainWindow>
#include <QListWidgetItem>
#include <vector>
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
    QString getMyName() const;
    void setMyName(const QString &value);

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
    char buf[100];
    std::vector<int> numbersGG;
    std::vector<QString> names;
    std::vector<MainWindow *> mainWindows;
    QString myName;

};

#endif // CONTACTSWINDOW_H
