/********************************************************************************
** Form generated from reading UI file 'contactswindow.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CONTACTSWINDOW_H
#define UI_CONTACTSWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ContactsWindow
{
public:
    QWidget *centralwidget;
    QPushButton *pushButton;
    QPushButton *pushButton_2;
    QListWidget *listWidget;
    QPushButton *quitButton;
    QPushButton *addButton;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *ContactsWindow)
    {
        if (ContactsWindow->objectName().isEmpty())
            ContactsWindow->setObjectName(QString::fromUtf8("ContactsWindow"));
        ContactsWindow->resize(394, 600);
        QPalette palette;
        QBrush brush(QColor(255, 255, 255, 255));
        brush.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Light, brush);
        palette.setBrush(QPalette::Active, QPalette::BrightText, brush);
        palette.setBrush(QPalette::Active, QPalette::Base, brush);
        QBrush brush1(QColor(245, 121, 0, 255));
        brush1.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Window, brush1);
        palette.setBrush(QPalette::Active, QPalette::HighlightedText, brush);
        palette.setBrush(QPalette::Active, QPalette::AlternateBase, brush);
#if QT_VERSION >= QT_VERSION_CHECK(5, 12, 0)
        palette.setBrush(QPalette::Active, QPalette::PlaceholderText, brush);
#endif
        palette.setBrush(QPalette::Inactive, QPalette::Light, brush);
        palette.setBrush(QPalette::Inactive, QPalette::BrightText, brush);
        palette.setBrush(QPalette::Inactive, QPalette::Base, brush);
        palette.setBrush(QPalette::Inactive, QPalette::Window, brush1);
        palette.setBrush(QPalette::Inactive, QPalette::HighlightedText, brush);
        QBrush brush2(QColor(247, 247, 247, 255));
        brush2.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Inactive, QPalette::AlternateBase, brush2);
#if QT_VERSION >= QT_VERSION_CHECK(5, 12, 0)
        palette.setBrush(QPalette::Inactive, QPalette::PlaceholderText, brush);
#endif
        palette.setBrush(QPalette::Disabled, QPalette::Light, brush);
        palette.setBrush(QPalette::Disabled, QPalette::BrightText, brush);
        palette.setBrush(QPalette::Disabled, QPalette::Base, brush1);
        palette.setBrush(QPalette::Disabled, QPalette::Window, brush1);
        palette.setBrush(QPalette::Disabled, QPalette::HighlightedText, brush);
        palette.setBrush(QPalette::Disabled, QPalette::AlternateBase, brush2);
#if QT_VERSION >= QT_VERSION_CHECK(5, 12, 0)
        palette.setBrush(QPalette::Disabled, QPalette::PlaceholderText, brush);
#endif
        ContactsWindow->setPalette(palette);
        ContactsWindow->setAutoFillBackground(false);
        centralwidget = new QWidget(ContactsWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        pushButton = new QPushButton(centralwidget);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(50, 20, 121, 61));
        pushButton_2 = new QPushButton(centralwidget);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));
        pushButton_2->setGeometry(QRect(220, 20, 121, 61));
        listWidget = new QListWidget(centralwidget);
        listWidget->setObjectName(QString::fromUtf8("listWidget"));
        listWidget->setGeometry(QRect(45, 110, 301, 391));
        QPalette palette1;
        QBrush brush3(QColor(255, 243, 138, 255));
        brush3.setStyle(Qt::SolidPattern);
        palette1.setBrush(QPalette::Active, QPalette::Base, brush3);
        palette1.setBrush(QPalette::Inactive, QPalette::Base, brush3);
        palette1.setBrush(QPalette::Disabled, QPalette::Base, brush1);
        listWidget->setPalette(palette1);
        quitButton = new QPushButton(centralwidget);
        quitButton->setObjectName(QString::fromUtf8("quitButton"));
        quitButton->setGeometry(QRect(80, 510, 91, 31));
        addButton = new QPushButton(centralwidget);
        addButton->setObjectName(QString::fromUtf8("addButton"));
        addButton->setGeometry(QRect(220, 510, 91, 31));
        ContactsWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(ContactsWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 394, 21));
        ContactsWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(ContactsWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        ContactsWindow->setStatusBar(statusbar);

        retranslateUi(ContactsWindow);

        QMetaObject::connectSlotsByName(ContactsWindow);
    } // setupUi

    void retranslateUi(QMainWindow *ContactsWindow)
    {
        ContactsWindow->setWindowTitle(QCoreApplication::translate("ContactsWindow", "MainWindow", nullptr));
        pushButton->setText(QCoreApplication::translate("ContactsWindow", "Znajomi", nullptr));
        pushButton_2->setText(QCoreApplication::translate("ContactsWindow", "Grupy", nullptr));
        quitButton->setText(QCoreApplication::translate("ContactsWindow", "Zamknij", nullptr));
        addButton->setText(QCoreApplication::translate("ContactsWindow", "Dodaj", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ContactsWindow: public Ui_ContactsWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CONTACTSWINDOW_H
