#ifndef ADDCONTACTWINDOW_H
#define ADDCONTACTWINDOW_H

#include <QMainWindow>
#include <QtDebug>
#include <QtNetwork>
#include "infodialog.h"

namespace Ui {
class AddContactWindow;
}

class AddContactWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit AddContactWindow(QWidget *parent = nullptr);
    ~AddContactWindow();
    int getMyGG() const;
    void setMyGG(int value);

private slots:
    void on_addButton_clicked();
    void on_cancelButton_clicked();

signals:
    void sendMessage(QByteArray buf);

private:
    Ui::AddContactWindow *ui;
    InfoDialog *infoDialog;
    char buf[100];
    int myGG;
};

#endif // ADDCONTACTWINDOW_H
