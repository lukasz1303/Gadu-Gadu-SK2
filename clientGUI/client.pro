QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    addcontactwindow.cpp \
    contactswindow.cpp \
    infodialog.cpp \
    loginwindow.cpp \
    main.cpp \
    mainwindow.cpp \
    serverselect.cpp \
    signupwindow.cpp \
    user.cpp

HEADERS += \
    addcontactwindow.h \
    contactswindow.h \
    infodialog.h \
    loginwindow.h \
    mainwindow.h \
    serverselect.h \
    signupwindow.h \
    user.h

FORMS += \
    addcontactwindow.ui \
    contactswindow.ui \
    infodialog.ui \
    loginwindow.ui \
    mainwindow.ui \
    serverselect.ui \
    signupwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    images/green-circle-md.png

RESOURCES += \
    images/images.qrc
