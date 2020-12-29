#include "contactswindow.h"
#include "ui_contactswindow.h"

ContactsWindow::ContactsWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ContactsWindow)
{
    ui->setupUi(this);
    QListWidgetItem *item = new QListWidgetItem("Tantal");
    ui->listWidget->addItem(item);

}

ContactsWindow::~ContactsWindow()
{
    delete ui;
}

void ContactsWindow::on_quitButton_clicked()
{
    QApplication::quit();
}

void ContactsWindow::on_listWidget_itemClicked(QListWidgetItem *item)
{
    mainWindow = new MainWindow(this);
    mainWindow->setWindowTitle(item->text());
    mainWindow->setSocket(tcpSocket);
    mainWindow->show();
}

void ContactsWindow::on_pushButton_4_clicked()
{

}

void ContactsWindow::setSocket(QTcpSocket *socket)
{
    tcpSocket = socket;
}
