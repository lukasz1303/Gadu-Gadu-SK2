/********************************************************************************
** Form generated from reading UI file 'signupwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SIGNUPWINDOW_H
#define UI_SIGNUPWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SignUpWindow
{
public:
    QWidget *centralwidget;
    QLabel *label;
    QTextEdit *loginTextEdit;
    QTextEdit *nrGGTextEdit;
    QTextEdit *passTextEdit;
    QLabel *label_2;
    QLabel *label_3;
    QLabel *label_4;
    QPushButton *signUpButton;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *SignUpWindow)
    {
        if (SignUpWindow->objectName().isEmpty())
            SignUpWindow->setObjectName(QString::fromUtf8("SignUpWindow"));
        SignUpWindow->resize(376, 314);
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
        SignUpWindow->setPalette(palette);
        centralwidget = new QWidget(SignUpWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        label = new QLabel(centralwidget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(120, 20, 171, 31));
        QFont font;
        font.setPointSize(18);
        font.setBold(false);
        font.setWeight(50);
        label->setFont(font);
        loginTextEdit = new QTextEdit(centralwidget);
        loginTextEdit->setObjectName(QString::fromUtf8("loginTextEdit"));
        loginTextEdit->setGeometry(QRect(130, 70, 181, 31));
        QPalette palette1;
        QBrush brush2(QColor(255, 243, 138, 255));
        brush2.setStyle(Qt::SolidPattern);
        palette1.setBrush(QPalette::Active, QPalette::Base, brush2);
        palette1.setBrush(QPalette::Inactive, QPalette::Base, brush2);
        palette1.setBrush(QPalette::Disabled, QPalette::Base, brush1);
        loginTextEdit->setPalette(palette1);
        nrGGTextEdit = new QTextEdit(centralwidget);
        nrGGTextEdit->setObjectName(QString::fromUtf8("nrGGTextEdit"));
        nrGGTextEdit->setGeometry(QRect(130, 120, 181, 31));
        QPalette palette2;
        palette2.setBrush(QPalette::Active, QPalette::Base, brush2);
        palette2.setBrush(QPalette::Inactive, QPalette::Base, brush2);
        palette2.setBrush(QPalette::Disabled, QPalette::Base, brush1);
        nrGGTextEdit->setPalette(palette2);
        passTextEdit = new QTextEdit(centralwidget);
        passTextEdit->setObjectName(QString::fromUtf8("passTextEdit"));
        passTextEdit->setGeometry(QRect(130, 170, 181, 31));
        QPalette palette3;
        palette3.setBrush(QPalette::Active, QPalette::Base, brush2);
        palette3.setBrush(QPalette::Inactive, QPalette::Base, brush2);
        palette3.setBrush(QPalette::Disabled, QPalette::Base, brush1);
        passTextEdit->setPalette(palette3);
        label_2 = new QLabel(centralwidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(50, 80, 58, 16));
        label_3 = new QLabel(centralwidget);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(50, 130, 58, 16));
        label_4 = new QLabel(centralwidget);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(50, 180, 58, 16));
        signUpButton = new QPushButton(centralwidget);
        signUpButton->setObjectName(QString::fromUtf8("signUpButton"));
        signUpButton->setGeometry(QRect(150, 230, 80, 24));
        SignUpWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(SignUpWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 376, 21));
        SignUpWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(SignUpWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        SignUpWindow->setStatusBar(statusbar);

        retranslateUi(SignUpWindow);

        QMetaObject::connectSlotsByName(SignUpWindow);
    } // setupUi

    void retranslateUi(QMainWindow *SignUpWindow)
    {
        SignUpWindow->setWindowTitle(QCoreApplication::translate("SignUpWindow", "MainWindow", nullptr));
        label->setText(QCoreApplication::translate("SignUpWindow", "Rejestracja", nullptr));
        label_2->setText(QCoreApplication::translate("SignUpWindow", "Login:", nullptr));
        label_3->setText(QCoreApplication::translate("SignUpWindow", "Nr. GG", nullptr));
        label_4->setText(QCoreApplication::translate("SignUpWindow", "Has\305\202o:", nullptr));
        signUpButton->setText(QCoreApplication::translate("SignUpWindow", "Zarejestruj", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SignUpWindow: public Ui_SignUpWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SIGNUPWINDOW_H
