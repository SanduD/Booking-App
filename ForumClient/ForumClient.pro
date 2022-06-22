QT       += core gui
QT       += network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    client.cpp \
    iclient.cpp \
    main.cpp \
    mainwindow.cpp \
    mainwindowsingleton.cpp \
    others.cpp \
    popupwindow.cpp

HEADERS += \
    client.h \
    iclient.h \
    mainwindow.h \
    mainwindowsingleton.h \
    others.h \
    popupwindow.h

FORMS += \
    mainwindow.ui \
    others.ui \
    popupwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    Darkeum.qss \
    Devsion.qss \
    Diffnes.qss \
    Toolery.qss
