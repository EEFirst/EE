#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QList>
#include <QString>
#include <iostream>
#include <QLabel>
#include <QPushButton>
#include <QComboBox>
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QMessageBox>
#include <QByteArray>
#include <QMap>
#include <QTimer>

#include "mycombobox.h"
#include "portdatadeal.h"

#define FRONT 0x55
#define END 0x51

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void uiBaseInit();
private slots:
    void openFunction();
    void closeFunction();
    void sendFunction();
    void clearFunction();
    void readFunction();
    void portTimerFunction();
    void setTimerFunction();
    void on_checkBox_clicked(bool checked);
    void on_checkBox_2_clicked(bool checked);

    void on_timerStart_clicked();

    void on_timerStop_clicked();

    void on_caiji1qingling_clicked();

    void on_caijiyitingzhi_clicked();

    void on_caiji1kaishi_clicked();

    void on_quanxuan_clicked();

    void on_qingkongxuanxiang_clicked();

    void on_quanxuan_2_clicked();

    void on_zidongfasong_clicked();

    void on_shezhiButton_clicked();

    void on_moshidingchang_clicked();

    void on_dingchang_clicked();

    void on_pushButton_12_clicked();

    void on_pushButton_13_clicked();

    void on_pushButton_15_clicked();

    void on_pushButton_16_clicked();

    void on_pushButton_25_clicked();

    void on_pushButton_24_clicked();

    void on_pushButton_22_clicked();

    void on_pushButton_21_clicked();

    void on_pushButton_19_clicked();

    void on_pushButton_18_clicked();

    void on_pushButton_28_clicked();

    void on_pushButton_27_clicked();

    void on_pushButton_31_clicked();

    void on_pushButton_30_clicked();

    void on_pushButton_34_clicked();

    void on_pushButton_33_clicked();

    void on_changdu1_cursorPositionChanged(int arg1, int arg2);

    void on_pushButton_11_clicked();

    void rec_ok_data_deal();

private:
    Ui::MainWindow *ui;
    QList<QString> list;
    bool sendHex;
    bool readHex;
    QString sendTemp;
    QByteArray sendBuf;
    QString readTemp;
    QByteArray readBuf;
    bool kaishi_Flag = 0;
    int numCode = 1;
    int id = 0;
    int flag = 0;
    QString mydata;
    QByteArray readT;
    QByteArray read_readBuf;
    int idFlag[10];
    bool zidong = 0;
    int port_exe_number = 1;
    bool setNumber = 0;

    //定时器
    QTimer portTimer;
    QTimer setTimer;

    //串口操作句柄
    QSerialPort myPort;
    QSerialPortInfo myInfo;

    //串口号
    QLabel *portName;
    QComboBox *portBox; //通过重构QComboBox鼠标点击事件获取

    //串口波特率
    QLabel *portRate;
    QComboBox *portRateValue;
    QList<QString> rateList;    //用来初始化串口波特率

    //串口数据位
    QList<QString> dataList;
    QLabel *portData;
    QComboBox *portDataValue;
    QMap<QString,QSerialPort::DataBits> dataMap = {{"5",QSerialPort::Data5},
                                                   {"6",QSerialPort::Data6},
                                                   {"7",QSerialPort::Data7},
                                                   {"8",QSerialPort::Data8}};

    //校验
    QList<QString> checkList;
    QLabel *portCheck;
    QComboBox *portCheckValue;
    QMap<QString,QSerialPort::Parity> checkMap = {{"NO",QSerialPort::NoParity},
                                                  {"EvenParity",QSerialPort::EvenParity},
                                                  {"OddParity",QSerialPort::OddParity},
                                                  {"SpaceParity",QSerialPort::SpaceParity},
                                                  {"MarkParity",QSerialPort::MarkParity}};

    //停止位
    QList<QString> stopList;
    QLabel *portStop;
    QComboBox *portStopValue;
    QMap<QString,QSerialPort::StopBits> stopMap = {{"1",QSerialPort::OneStop},
                                                   {"1.5",QSerialPort::OneAndHalfStop},
                                                   {"2",QSerialPort::TwoStop}};

    //流控制
    QList<QString> streamList;
    QLabel *porStream;
    QComboBox *portStreamValue;
    QMap<QString,QSerialPort::FlowControl> FlopMap = {{"No",QSerialPort::NoFlowControl},
                                                     {"Hard",QSerialPort::HardwareControl},
                                                     {"Soft",QSerialPort::SoftwareControl},};

    //打开、关闭、发送、清空接收区
    QPushButton *openButton;
    QPushButton *closeButton;
    QPushButton *sendButton;
    QPushButton *clearButton;
};

#endif // MAINWINDOW_H
