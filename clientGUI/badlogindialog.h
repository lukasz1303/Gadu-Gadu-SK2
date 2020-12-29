#ifndef BADLOGINDIALOG_H
#define BADLOGINDIALOG_H

#include <QDialog>

namespace Ui {
class BadLoginDialog;
}

class BadLoginDialog : public QDialog
{
    Q_OBJECT

public:
    explicit BadLoginDialog(QWidget *parent = nullptr);
    ~BadLoginDialog();
    void setLabelText(QString str);

private slots:
    void on_pushButton_clicked();

private:
    Ui::BadLoginDialog *ui;
};

#endif // BADLOGINDIALOG_H
