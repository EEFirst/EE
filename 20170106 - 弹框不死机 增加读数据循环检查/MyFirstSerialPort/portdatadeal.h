#ifndef PORTDATADEAL_H
#define PORTDATADEAL_H

#include <QByteArray>
#include <QString>
#include "mainwindow.h"

#include "mainwindow.h"

#define PORAUTONUMBER 9

class portDataDeal
{
private:

    int kaishi_num_code = 1;
    QByteArray myArray;

public:
    portDataDeal();
    QByteArray send(int *data,int id);
    QByteArray timerSend(int idFlag[10], int* numCode, int *port_exe_number,int *data1,int *data2,int *data3);
    QString read(int *data);
    void codeDeal(int *num, int *flag, QString *mydata, QByteArray data);
    int Check(int *data);
    unsigned int Check(QByteArray data);
};

#endif // PORTDATADEAL_H
