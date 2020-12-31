/********************************************************************************
** Form generated from reading UI file 'loginwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LOGINWINDOW_H
#define UI_LOGINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_LoginWIndow
{
public:
    QWidget *centralwidget;
    QLabel *label;
    QTextEdit *loginTextEdit;
    QLabel *label_2;
    QLabel *label_3;
    QPushButton *signInButton;
    QLabel *label_4;
    QPushButton *signUpButton;
    QLineEdit *passwordLineEdit;
    QMenuBar *menubar;

    void setupUi(QMainWindow *LoginWIndow)
    {
        if (LoginWIndow->objectName().isEmpty())
            LoginWIndow->setObjectName(QString::fromUtf8("LoginWIndow"));
        LoginWIndow->resize(462, 357);
        QPalette palette;
        QBrush brush(QColor(255, 255, 255, 255));
        brush.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Base, brush);
        QBrush brush1(QColor(245, 121, 0, 255));
        brush1.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Window, brush1);
        palette.setBrush(QPalette::Inactive, QPalette::Base, brush);
        palette.setBrush(QPalette::Inactive, QPalette::Window, brush1);
        palette.setBrush(QPalette::Disabled, QPalette::Base, brush1);
        palette.setBrush(QPalette::Disabled, QPalette::Window, brush1);
        LoginWIndow->setPalette(palette);
        centralwidget = new QWidget(LoginWIndow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        label = new QLabel(centralwidget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(150, 10, 121, 51));
        QFont font;
        font.setPointSize(18);
        label->setFont(font);
        loginTextEdit = new QTextEdit(centralwidget);
        loginTextEdit->setObjectName(QString::fromUtf8("loginTextEdit"));
        loginTextEdit->setGeometry(QRect(170, 110, 211, 31));
        QPalette palette1;
        QBrush brush2(QColor(255, 243, 138, 255));
        brush2.setStyle(Qt::SolidPattern);
        palette1.setBrush(QPalette::Active, QPalette::Base, brush2);
        palette1.setBrush(QPalette::Inactive, QPalette::Base, brush2);
        palette1.setBrush(QPalette::Disabled, QPalette::Base, brush1);
        loginTextEdit->setPalette(palette1);
        label_2 = new QLabel(centralwidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(70, 110, 58, 31));
        QFont font1;
        font1.setPointSize(11);
        label_2->setFont(font1);
        label_3 = new QLabel(centralwidget);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(70, 170, 71, 31));
        label_3->setFont(font1);
        signInButton = new QPushButton(centralwidget);
        signInButton->setObjectName(QString::fromUtf8("signInButton"));
        signInButton->setGeometry(QRect(190, 230, 80, 24));
        label_4 = new QLabel(centralwidget);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(290, 10, 51, 51));
        label_4->setPixmap(QPixmap(QString::fromUtf8(":/images/icon")));
        label_4->setScaledContents(true);
        signUpButton = new QPushButton(centralwidget);
        signUpButton->setObjectName(QString::fromUtf8("signUpButton"));
        signUpButton->setGeometry(QRect(20, 290, 80, 24));
        passwordLineEdit = new QLineEdit(centralwidget);
        passwordLineEdit->setObjectName(QString::fromUtf8("passwordLineEdit"));
        passwordLineEdit->setGeometry(QRect(170, 170, 211, 31));
        QPalette palette2;
        palette2.setBrush(QPalette::Active, QPalette::Base, brush2);
        palette2.setBrush(QPalette::Inactive, QPalette::Base, brush2);
        palette2.setBrush(QPalette::Disabled, QPalette::Base, brush1);
        passwordLineEdit->setPalette(palette2);
        QFont font2;
        font2.setPointSize(14);
        passwordLineEdit->setFont(font2);
        LoginWIndow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(LoginWIndow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 462, 21));
        LoginWIndow->setMenuBar(menubar);

        retranslateUi(LoginWIndow);

        QMetaObject::connectSlotsByName(LoginWIndow);
    } // setupUi

    void retranslateUi(QMainWindow *LoginWIndow)
    {
        LoginWIndow->setWindowTitle(QCoreApplication::translate("LoginWIndow", "MainWindow", nullptr));
        label->setText(QCoreApplication::translate("LoginWIndow", "Gadu-Gadu", nullptr));
        label_2->setText(QCoreApplication::translate("LoginWIndow", "Login:", nullptr));
        label_3->setText(QCoreApplication::translate("LoginWIndow", "Has\305\202o:", nullptr));
        signInButton->setText(QCoreApplication::translate("LoginWIndow", "Zaloguj", nullptr));
        label_4->setText(QString());
        signUpButton->setText(QCoreApplication::translate("LoginWIndow", "Zarejestruj", nullptr));
    } // retranslateUi

};

namespace Ui {
    class LoginWIndow: public Ui_LoginWIndow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOGINWINDOW_H
