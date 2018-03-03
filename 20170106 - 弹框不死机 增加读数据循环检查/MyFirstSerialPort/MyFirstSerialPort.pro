#-------------------------------------------------
#
# Project created by QtCreator 2017-12-18T12:16:58
#
#-------------------------------------------------

QT       += core gui
QT += serialport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = MyFirstSerialPort
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    mycombobox.cpp \
    portdatadeal.cpp

HEADERS  += mainwindow.h \
    mycombobox.h \
    portdatadeal.h

FORMS    += mainwindow.ui
