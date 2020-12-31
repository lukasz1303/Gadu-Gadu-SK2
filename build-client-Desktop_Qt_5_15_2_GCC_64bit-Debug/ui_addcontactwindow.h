/********************************************************************************
** Form generated from reading UI file 'addcontactwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ADDCONTACTWINDOW_H
#define UI_ADDCONTACTWINDOW_H

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

class Ui_AddContactWindow
{
public:
    QWidget *centralwidget;
    QLabel *titleLabel;
    QLabel *numberLabel;
    QLabel *label_3;
    QTextEdit *nameTextEdit;
    QTextEdit *numberTextEdit;
    QPushButton *addButton;
    QPushButton *cancelButton;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *AddContactWindow)
    {
        if (AddContactWindow->objectName().isEmpty())
            AddContactWindow->setObjectName(QString::fromUtf8("AddContactWindow"));
        AddContactWindow->resize(443, 307);
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
        AddContactWindow->setPalette(palette);
        centralwidget = new QWidget(AddContactWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        titleLabel = new QLabel(centralwidget);
        titleLabel->setObjectName(QString::fromUtf8("titleLabel"));
        titleLabel->setGeometry(QRect(100, 10, 241, 31));
        QFont font;
        font.setPointSize(16);
        titleLabel->setFont(font);
        titleLabel->setAlignment(Qt::AlignCenter);
        numberLabel = new QLabel(centralwidget);
        numberLabel->setObjectName(QString::fromUtf8("numberLabel"));
        numberLabel->setGeometry(QRect(80, 90, 58, 16));
        QFont font1;
        font1.setPointSize(11);
        numberLabel->setFont(font1);
        label_3 = new QLabel(centralwidget);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(80, 140, 58, 16));
        label_3->setFont(font1);
        nameTextEdit = new QTextEdit(centralwidget);
        nameTextEdit->setObjectName(QString::fromUtf8("nameTextEdit"));
        nameTextEdit->setGeometry(QRect(140, 80, 201, 31));
        QPalette palette1;
        QBrush brush2(QColor(255, 243, 138, 255));
        brush2.setStyle(Qt::SolidPattern);
        palette1.setBrush(QPalette::Active, QPalette::Base, brush2);
        palette1.setBrush(QPalette::Inactive, QPalette::Base, brush2);
        palette1.setBrush(QPalette::Disabled, QPalette::Base, brush1);
        nameTextEdit->setPalette(palette1);
        numberTextEdit = new QTextEdit(centralwidget);
        numberTextEdit->setObjectName(QString::fromUtf8("numberTextEdit"));
        numberTextEdit->setGeometry(QRect(140, 130, 201, 31));
        QPalette palette2;
        palette2.setBrush(QPalette::Active, QPalette::Base, brush2);
        palette2.setBrush(QPalette::Inactive, QPalette::Base, brush2);
        palette2.setBrush(QPalette::Disabled, QPalette::Base, brush1);
        numberTextEdit->setPalette(palette2);
        addButton = new QPushButton(centralwidget);
        addButton->setObjectName(QString::fromUtf8("addButton"));
        addButton->setGeometry(QRect(190, 180, 80, 24));
        cancelButton = new QPushButton(centralwidget);
        cancelButton->setObjectName(QString::fromUtf8("cancelButton"));
        cancelButton->setGeometry(QRect(20, 220, 80, 24));
        AddContactWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(AddContactWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 443, 21));
        AddContactWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(AddContactWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        AddContactWindow->setStatusBar(statusbar);

        retranslateUi(AddContactWindow);

        QMetaObject::connectSlotsByName(AddContactWindow);
    } // setupUi

    void retranslateUi(QMainWindow *AddContactWindow)
    {
        AddContactWindow->setWindowTitle(QCoreApplication::translate("AddContactWindow", "MainWindow", nullptr));
        titleLabel->setText(QCoreApplication::translate("AddContactWindow", "Dodawanie kontaktu", nullptr));
        numberLabel->setText(QCoreApplication::translate("AddContactWindow", "Nazwa:", nullptr));
        label_3->setText(QCoreApplication::translate("AddContactWindow", "Nr GG:", nullptr));
        addButton->setText(QCoreApplication::translate("AddContactWindow", "Dodaj", nullptr));
        cancelButton->setText(QCoreApplication::translate("AddContactWindow", "Anuluj", nullptr));
    } // retranslateUi

};

namespace Ui {
    class AddContactWindow: public Ui_AddContactWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ADDCONTACTWINDOW_H
