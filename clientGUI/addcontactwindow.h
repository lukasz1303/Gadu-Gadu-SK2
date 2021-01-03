#ifndef ADDCONTACTWINDOW_H
#define ADDCONTACTWINDOW_H

#include <QMainWindow>
#include <QtDebug>
#include <QtNetwork>
#include "infodialog.h"
#include "user.h"

namespace Ui {
class AddContactWindow;
}

class AddContactWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit AddContactWindow(QWidget *parent = nullptr);
    ~AddContactWindow();

private slots:
    void on_addButton_clicked();
    void on_cancelButton_clicked();

signals:
    void sendMessage(QByteArray buf);

private:
    Ui::AddContactWindow *ui;
    InfoDialog *infoDialog;
    char buf[100];
};

#endif // ADDCONTACTWINDOW_H
