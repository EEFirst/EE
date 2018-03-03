#ifndef MYCOMBOBOX_H
#define MYCOMBOBOX_H

#include <QObject>
#include <QComboBox>
#include <QMouseEvent>
#include <QSerialPort>
#include <QSerialPortInfo>
#include <iostream>

#include "mainwindow.h"

class mycombobox : public QComboBox
{
    Q_OBJECT
public:
    mycombobox(QWidget *parent);
    ~mycombobox();

protected:
    void mousePressEvent(QMouseEvent *event);

private:

signals:
    void clicked(bool);
};

#endif // MYCOMBOBOX_H
