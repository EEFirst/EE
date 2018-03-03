#include "mycombobox.h"

mycombobox::mycombobox(QWidget*parent=0):QComboBox(parent)
{

}

mycombobox::~mycombobox()
{

}

/*
    当产生鼠标点击事件时，刷新使能串口在界面上的显示
*/
void mycombobox::mousePressEvent(QMouseEvent *event)
{
    std::cout<<"MousePressEvent Refresh PortName!"<<std::endl;
    this->clear();
    foreach (const QSerialPortInfo &tempInfo, QSerialPortInfo::availablePorts()){
        this->addItem(tempInfo.portName());     //这里会更新在界面上显示的串口名
    }
    this->showPopup();
    event->ignore();
}


