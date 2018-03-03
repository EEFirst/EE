#include "mainwindow.h"
#include "ui_mainwindow.h"

int qingling[10] = {FRONT,0x01,0x08,0x04,0x00,0x00,0x00,0x00,0x0d,END};
int tingzhi[10] = {FRONT,0x01,0x08,0x0c,0x00,0x00,0x00,0x00,0x0e,END};
//4id 8sum
int shezhi[10] = {FRONT,0xff,0x08,0x01,0x00,0x00,0x00,0x00,0x8e,END};
int dingchangzhi1[10] = {FRONT,0xff,0x08,0x02,0x00,0x00,0x00,0x00,0x8e,END};
int moshi[10] = {FRONT,0x00,0x08,0x03,0x00,0x00,0x00,0x00,0x8e,END};
   int kaishi[10] = {FRONT,0x01,0x08,0x05,0x00,0x00,0x00,0x00,0x0e,END};
    int sudu[10] = {FRONT,0x01,0x08,0x85,0x00,0x00,0x00,0x00,0x8e,END};
    int changdu[10] ={FRONT,0x01,0x08,0x84,0x00,0x00,0x00,0x00,0x8d,END};

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    uiBaseInit();
    ui->checkBox_2->setChecked(true);
    readHex = ui->checkBox_2->checkState();
    ui->deng1->setReadOnly(true);
    ui->deng1->setStyleSheet("background-color: rgb(250, 0, 0);font-size:60px;color:blue");
    ui->deng2->setReadOnly(true);
    ui->deng2->setStyleSheet("background-color: rgb(250, 0, 0);font-size:60px;color:blue");
    ui->deng3->setReadOnly(true);
    ui->deng3->setStyleSheet("background-color: rgb(250, 0, 0);font-size:60px;color:blue");
    ui->deng4->setReadOnly(true);
    ui->deng4->setStyleSheet("background-color: rgb(250, 0, 0);font-size:60px;color:blue");
    ui->deng5->setReadOnly(true);
    ui->deng5->setStyleSheet("background-color: rgb(250, 0, 0);font-size:60px;color:blue");
    ui->deng6->setReadOnly(true);
    ui->deng6->setStyleSheet("background-color: rgb(250, 0, 0);font-size:60px;color:blue");
    ui->deng7->setReadOnly(true);
    ui->deng7->setStyleSheet("background-color: rgb(250, 0, 0);font-size:60px;color:blue");
    ui->deng8->setReadOnly(true);
    ui->deng8->setStyleSheet("background-color: rgb(250, 0, 0);font-size:60px;color:blue");
    ui->deng9->setReadOnly(true);
    ui->deng9->setStyleSheet("background-color: rgb(250, 0, 0);font-size:60px;color:blue");
}

MainWindow::~MainWindow()
{
    delete ui;
}
/********************************************************************************
**********************************基础串口设置*************************************
********************************************************************************/
/*
    函数名：uiInit()
    参数: 无
    返回值：无
    函数功能：初始化UI控件
*/
void MainWindow::uiBaseInit()
{
    /*****************************UI基础设置**************************************/
    //通过鼠标点击事件获取串口名
    portName = new QLabel(ui->Base);
    portName->setGeometry(20,20,70,30);
    portName->setText("端口号:");
    portBox = new mycombobox(ui->Base);
    portBox->setGeometry(100,20,120,30);

    //设置串口波特率
    portRate = new QLabel(ui->Base);
    portRate->setGeometry(20,70,70,30);
    portRate->setText("波特率:");
    portRateValue = new QComboBox(ui->Base);
    portRateValue->setGeometry(100,70,120,30);
    rateList = {"300","600","1200","2400","4800","9600","19200","38400","43000","56000","57600","115200"};
    portRateValue->addItems(rateList);

    //设置串口数据位
    portData = new QLabel(ui->Base);
    portData->setGeometry(20,120,70,30);
    portData->setText("数据位:");
    portDataValue = new QComboBox(ui->Base);
    portDataValue->setGeometry(100,120,120,30);
    dataList = {"5","6","7","8"};
    portDataValue->addItems(dataList);

    //设置串口校验
    portCheck = new QLabel(ui->Base);
    portCheck->setGeometry(20,170,70,30);
    portCheck->setText("位校验:");
    portCheckValue = new QComboBox(ui->Base);
    portCheckValue->setGeometry(100,170,120,30);
    checkList = {"NO","EvenParity","OddParity","SpaceParity","MarkParity"};
    portCheckValue->addItems(checkList);

    //串口停止位
    portStop = new QLabel(ui->Base);
    portStop->setGeometry(20,220,70,30);
    portStop->setText("停止位:");
    portStopValue = new QComboBox(ui->Base);
    portStopValue->setGeometry(100,220,120,30);
    stopList = {"1","1.5","2"};
    portStopValue->addItems(stopList);

    //流控制
    porStream = new QLabel(ui->Base);
    porStream->setGeometry(20,270,70,30);
    porStream->setText("流控制:");
    portStreamValue = new QComboBox(ui->Base);
    portStreamValue->setGeometry(100,270,120,30);
    streamList = {"NO","Soft","Hard"};
    portStreamValue->addItems(streamList);

    //打开、关闭、发送、清空
    openButton = new QPushButton(ui->Base);
    openButton->setText("打开");
    openButton->setGeometry(20,320,100,30);
    closeButton = new QPushButton(ui->Base);
    closeButton->setText("关闭");
    closeButton->setGeometry(120,320,100,30);
    sendButton = new QPushButton(ui->Base);
    sendButton->setText("发送");
    sendButton->setGeometry(20,365,100,30);
    clearButton = new QPushButton(ui->Base);
    clearButton->setText("清空");
    clearButton->setGeometry(120,365,100,30);
    /****************************************************************************/

    /******************************连接信号与槽************************************/
    connect(openButton,SIGNAL(clicked(bool)),this,SLOT(openFunction()));
    connect(closeButton,SIGNAL(clicked(bool)),this,SLOT(closeFunction()));
    connect(sendButton,SIGNAL(clicked(bool)),this,SLOT(sendFunction()));
    connect(clearButton,SIGNAL(clicked(bool)),this,SLOT(clearFunction()));
    connect(&myPort, SIGNAL(readyRead()), this, SLOT(readFunction()));
    connect(&portTimer,SIGNAL(timeout()),this,SLOT(portTimerFunction()));
    connect(&setTimer,SIGNAL(timeout()),this,SLOT(setTimerFunction()));
    /****************************************************************************/

    /*********************************提示***************************************/
    //设置接收区和发送区的提示字符
    ui->readEdit->setPlaceholderText("接收区");
    ui->readEdit->setReadOnly(true);             //设置接收区为只读
    ui->writeEdit->setPlaceholderText("发送区");
    /****************************************************************************/

    //未打开串口前，设置关闭、发送为unEnabled
    closeButton->setEnabled(false);
    sendButton->setEnabled(false);
    ui->timerStart->setEnabled(false);
    ui->timerStop->hide();
//    ui->caiji1kaishi->visibleRegion(false);

    //设置串口默认初始值
    portRateValue->setCurrentText("9600");
    portDataValue->setCurrentText("8");
    portCheckValue->setCurrentText("NO");
    portStopValue->setCurrentText("1");
    portStreamValue->setCurrentText("NO");
    ui->timerEdit->setText("20");
    ui->cijizhouqi->setText("20");
}

/*
    函数名：openFunction
    参数：无
    返回值：无
    功能：打开串口
*/
void MainWindow::openFunction()
{
    //获取串口名
    myPort.setPortName(portBox->currentText());
    //设置波特率
    myPort.setBaudRate(portRateValue->currentText().toInt());
    //设置串口数据位
    myPort.setDataBits(dataMap[portDataValue->currentText()]);
    //设置校验位
    myPort.setParity(checkMap[portCheckValue->currentText()]);
    //设置串口停止位
    myPort.setStopBits(stopMap[portStopValue->currentText()]);
    //设置流控制
    myPort.setFlowControl(FlopMap[portStreamValue->currentText()]);

    //打开串口
    if(myPort.open(QIODevice::ReadWrite)){
        //打开串口后，设置串口参数不可更改
        portBox->setEnabled(false);
        portRateValue->setEnabled(false);
        portDataValue->setEnabled(false);
        portCheckValue->setEnabled(false);
        portStopValue->setEnabled(false);
        portStreamValue->setEnabled(false);
        //串口打开后unEnabled打开按键
        openButton->setEnabled(false);
        //打开串口后，设置关闭、发送为Enabled
        closeButton->setEnabled(true);
        sendButton->setEnabled(true);
        ui->timerStart->setEnabled(true);
        ui->timerStop->setEnabled(false);
    }else{
        QMessageBox::warning(this,"警告","打开串口失败");
    }
}

/*
    函数名：closeFunction
    参数：无
    返回值：无
    功能：关闭串口
*/
void MainWindow::closeFunction()
{
    //关闭串口
    myPort.close();

    //关闭串口后，设置串口参数为可更改
    portBox->setEnabled(true);
    portRateValue->setEnabled(true);
    portDataValue->setEnabled(true);
    portCheckValue->setEnabled(true);
    portStopValue->setEnabled(true);
    portStreamValue->setEnabled(true);

    //未打开串口前，设置关闭、发送为unEnabled
    closeButton->setEnabled(false);
    sendButton->setEnabled(false);

    //串口关闭后，Enabled打开按键
    openButton->setEnabled(true);
}

/*
    函数名：sendFunction
    参数：无
    返回值：无
    功能：发送数据 设置界面下 发送按钮 每次更新九路发送标志。
    当前通道被选中idFlag[i]=1，发送使能。发送对应数据，否则不发送。
*/
void MainWindow::sendFunction()
{


    idFlag[0] = 0;
    idFlag[1] = ui->caiji1check->isChecked();
    idFlag[2] = ui->caiji2check->isChecked();
    idFlag[3] = ui->caiji3check->isChecked();
    idFlag[4] = ui->caiji4check->isChecked();
    idFlag[5] = ui->caiji5check->isChecked();
    idFlag[6] = ui->caiji6check->isChecked();
    idFlag[7] = ui->caiji7check->isChecked();
    idFlag[8] = ui->caiji8check->isChecked();
    idFlag[9] = ui->caiji9check->isChecked();

    portDataDeal portData;
    sendBuf = portData.timerSend(idFlag,&numCode,&port_exe_number,kaishi,sudu,changdu);   //发送数据更新
    myPort.write(sendBuf);
}

/*
    函数名：readFunction()
    参数：无
    返回值：无
    功能：接收串口数据
*/
void MainWindow::readFunction()
{
    QByteArray temp = myPort.readAll();
    QByteArray readTemp1;
    int num=0;
    int i=0;
    unsigned char sum = 0;
    int data_ok_num=0;
    bool data_ok_deal_Flag=0;


    read_readBuf.append(temp);
    int temp_size = read_readBuf.size();
    if(read_readBuf.size()<10)                //如果读到的数据长度<10  此次数据不完整 返回
    {
        return;
    }
    data_ok_num=temp_size/10;    //可能的有效数据组数

    for(;data_ok_num>=1;)                   //如果一次来多组有效数据，则需要for循环将所有有效数据查找完。
    {

    if(read_readBuf.contains(FRONT))        //大于10 ，查找头，如果包含头，则继续
    {
        num = read_readBuf.indexOf(FRONT);     //读取头在缓存中的位置

        if(read_readBuf[num+9] == END)           //如果头后第九个数据是尾，则数据有效
        {

            for(i = 0;i < 10;i++)
            {
                readTemp1[i] = read_readBuf[num+i];   //将头尾符合的 这十个数取出，放到readTemp中。
            }

            for(int i = 1;i<8;i++)                   //对readTemp中的数据进行校验和计算
            {
                sum += (unsigned char)readTemp1[i];
            }

            if(sum == (unsigned char)readTemp1[8])            //如果校验和也正确，则读出此组数据。
            {
                readBuf = readTemp1;
                read_readBuf.remove(0,num+10);               //并在read_readBuf中删除此有效数据
                data_ok_num=data_ok_num-1;                   //有效数据数减1
                data_ok_deal_Flag=1;                              //找到一组有效数据 需要处理
            }
        }
    }
    else
    {

        data_ok_num=0;             //如果没有有效数据 则data_ok_num=0 退出循环
    }

//    有效数据查找结束

    if(read_readBuf.size() > 31 && read_readBuf.size() >= temp_size)  //如果当前缓存中数据大于31 且无有效数据 则清空
    {
        read_readBuf.clear();
        data_ok_num=0;
        return;
    }
//   有效数据处理
    if(data_ok_deal_Flag)
    {
        rec_ok_data_deal();
        data_ok_deal_Flag=0;            //有效数据处理标志
    }



    if(readHex){
        QString readData = "";
        readTemp = readBuf.toHex();
        for(int i = 0;i<readTemp.length();i+=2)
        {
            QString st = readTemp.mid(i,2);//从i这个位置开始，返回2个字符串
            readData += st;
            readData += " ";
        }
        readTemp.clear();
        readTemp = readData;
    }else{
        readTemp = readBuf;
    }
    ui->readEdit->append(readTemp);
    ui->readEdit01->append(readTemp);

    readTemp.clear();
    temp.clear();
    }
}

/*
    函数名：rec_ok_data_deal
    参数：无
    返回值：无
    功能：接收有效数据处理
*/
void MainWindow::rec_ok_data_deal()
{
    portDataDeal portDeal;
    portDeal.codeDeal(&id,&flag,&mydata,readBuf);
    switch (id)
    {
    case 1:
        switch (flag)
        {
        case 0x85:
            ui->changdu1->setText(mydata);            
            break;
        case 0x84:
            ui->sudu1->setText(mydata);
            break;
        case 0x04:
            if(mydata=="0")
            {
              QMessageBox::warning(this,"提示","通道1清除成功");
               ui->changdu2->setText("0");
               ui->sudu2->setText("0");

            }
            else
            {
               QMessageBox::warning(this,"警告","通道1清除失败");
            }
            break;
        case 0x0c:
            if(mydata=="0")
            {
               QMessageBox::warning(this,"提示","通道1停止成功");
            }
            else
            {
               QMessageBox::warning(this,"警告","通道1停止失败");
            }
            break;

        default:
            break;
        }
        break;
    case 2:
        switch (flag)
        {
        case 0x85:
            ui->changdu2->setText(mydata);
            break;
        case 0x84:
            ui->sudu2->setText(mydata);
            break;

        case 0x04:
            if(mydata=="0")
            {
              QMessageBox::warning(this,"提示","通道2清除成功");
               ui->changdu2->setText("0");
               ui->sudu2->setText("0");

            }
            else
            {
               QMessageBox::warning(this,"警告","通道2清除失败");
            }
            break;
        case 0x0c:
            if(mydata=="0")
            {
               QMessageBox::warning(this,"提示","通道2停止成功");
            }
            else
            {
               QMessageBox::warning(this,"警告","通道2停止失败");
            }
            break;

        default:
            break;
        }
        break;
    case 3:
        switch (flag) {
        case 0x85:
            ui->changdu3->setText(mydata);
            break;
        case 0x84:
            ui->sudu3->setText(mydata);
            break;
        case 0x04:
            if(mydata=="0")
            {
              QMessageBox::warning(this,"提示","通道3清除成功");
               ui->changdu3->setText("0");
               ui->sudu3->setText("0");

            }
            else
            {
               QMessageBox::warning(this,"警告","通道3清除失败");
            }
            break;
        case 0x0c:
            if(mydata=="1")
            {
               QMessageBox::warning(this,"提示","通道3停止成功");
            }
            else
            {
               QMessageBox::warning(this,"警告","通道3停止失败");
            }
            break;

        default:
            break;
        }
        break;
    case 4:
        switch (flag) {
        case 0x85:
            ui->changdu4->setText(mydata);
            break;
        case 0x84:
            ui->sudu4->setText(mydata);
            break;
        case 0x04:
            if(mydata=="0")
            {
             QMessageBox::warning(this,"提示","通道4清除成功");
               ui->changdu4->setText("0");
               ui->sudu4->setText("0");

            }
            else
            {
               QMessageBox::warning(this,"警告","通道4清除失败");
            }
            break;
        case 0x0c:
            if(mydata=="1")
            {
               QMessageBox::warning(this,"提示","通道4停止成功");
            }
            else
            {
               QMessageBox::warning(this,"警告","通道4停止失败");
            }
            break;


        default:
            break;
        }
        break;
    case 5:
        switch (flag) {
        case 0x85:
            ui->changdu5->setText(mydata);
            break;
        case 0x84:
            ui->sudu5->setText(mydata);
            break;
        case 0x04:
            if(mydata=="0")
            {
              // QMessageBox::warning(this,"提示","通道5清除成功");
               ui->changdu5->setText("0");
               ui->sudu5->setText("0");

            }
            else
            {
               QMessageBox::warning(this,"警告","通道5清除失败");
            }
            break;
        case 0x0c:
            if(mydata=="1")
            {
               QMessageBox::warning(this,"提示","通道5停止成功");
            }
            else
            {
               QMessageBox::warning(this,"警告","通道5停止失败");
            }
            break;


        default:
            break;
        }
        break;
    case 6:
        switch (flag) {
        case 0x85:
            ui->changdu6->setText(mydata);
            break;
        case 0x84:
            ui->sudu6->setText(mydata);
            break;
        case 0x04:
            if(mydata=="0")
            {
              // QMessageBox::warning(this,"提示","通道6清除成功");
               ui->changdu6->setText("0");
               ui->sudu6->setText("0");

            }
            else
            {
               QMessageBox::warning(this,"警告","通道6清除失败");
            }
            break;
        case 0x0c:
            if(mydata=="0")
            {
               QMessageBox::warning(this,"提示","通道6停止成功");
            }
            else
            {
               QMessageBox::warning(this,"警告","通道6停止失败");
            }
            break;


        default:
            break;
        }
        break;
    case 7:
        switch (flag) {
        case 0x85:
            ui->changdu7->setText(mydata);
            break;
        case 0x84:
            ui->sudu7->setText(mydata);
            break;
        case 0x04:
            if(mydata=="0")
            {
           //    QMessageBox::warning(this,"提示","通道7清除成功");
               ui->changdu7->setText("0");
               ui->sudu7->setText("0");

            }
            else
            {
               QMessageBox::warning(this,"警告","通道7清除失败");
            }
            break;
        case 0x0c:
            if(mydata=="1")
            {
               QMessageBox::warning(this,"提示","通道7停止成功");
            }
            else
            {
               QMessageBox::warning(this,"警告","通道7停止失败");
            }
            break;


        default:
            break;
        }
        break;
    case 8:
        switch (flag) {
        case 0x85:
            ui->changdu8->setText(mydata);
            break;
        case 0x84:
            ui->sudu8->setText(mydata);
            break;
        case 0x04:
            if(mydata=="0")
            {
             //  QMessageBox::warning(this,"提示","通道8清除成功");
               ui->changdu8->setText("0");
               ui->sudu8->setText("0");

            }
            else
            {
               QMessageBox::warning(this,"警告","通道8清除失败");
            }
            break;
        case 0x0c:
            if(mydata=="1")
            {
               QMessageBox::warning(this,"提示","通道8停止成功");
            }
            else
            {
               QMessageBox::warning(this,"警告","通道8停止失败");
            }
            break;
        default:
            break;
        }
        break;
    case 9:
        switch (flag) {

        case 0x85:
            ui->changdu9->setText(mydata);
            break;
        case 0x84:
            ui->sudu9->setText(mydata);
            break;
        case 0x04:
            if(mydata=="0")
            {
            //   QMessageBox::warning(this,"提示","通道9清除成功");
               ui->changdu9->setText("0");
               ui->sudu9->setText("0");

            }
            else
            {
               QMessageBox::warning(this,"警告","通道9清除失败");
            }
            break;
        case 0x0c:
            if(mydata=="1")
            {
               QMessageBox::warning(this,"提示","通道9停止成功");
            }
            else
            {
               QMessageBox::warning(this,"警告","通道9停止失败");
            }
            break;
        default:
            break;
        }
        break;
        break;
    default:
        break;
    }
    flag=0xff;
}



/*
    函数名：portTimerFunction
    参数：无
    返回值：无
    功能：定时器出发定时发送信号
*/
void MainWindow::portTimerFunction()
{
    sendButton->clicked();
}

void MainWindow::setTimerFunction()
{
    //4id 8sum
    //int shezhi[10] = {FRONT,0xff,0x08,0x01,0x00,0x00,0x00,0x00,0x8e,END};

    shezhi[4] = ui->shebeihao->text().toInt();
    int temp = 0;
    for(int i = 1;i < 8;i ++){
        temp+=shezhi[i];
    }
    shezhi[8] = temp;

    QByteArray sendBuf;
    sendBuf.resize(10);
    for(int i = 0;i<10;i++){
        sendBuf[i] = shezhi[i];
    }
    myPort.write(sendBuf);
    std::cout<<"这是下位机的ID设置"<<std::endl;
    setTimer.stop();
}

/*
    函数名：clearFunction()
    参数：无
    返回值：无
    功能：清空接收区
*/
void MainWindow::clearFunction()
{
    ui->readEdit->clear();
}

/*
    函数名：on_checkBox_clicked()
    参数：bool checked
    返回值：无
    函数功能：检查是否以16进制发送数据
*/
void MainWindow::on_checkBox_clicked(bool checked)
{
    sendHex = checked;
}

/*
    函数名：on_checkBox_2_clicked()
    参数：bool checked
    返回值：无
    函数功能：检查是否以16进制显示数据
*/
void MainWindow::on_checkBox_2_clicked(bool checked)
{
    readHex = checked;
}

/***********************************************************************/
//此部分开始与主体框架无关，加入定时发送功能
/*
    函数名:on_timerStart_clicked
    参数：无
    返回值：无
    功能：单击打开定时器
*/
void MainWindow::on_timerStart_clicked()
{
    ui->timerStop->setEnabled(true);
    ui->timerStart->setEnabled(false);
    portTimer.start(ui->cijizhouqi->text().toInt());
}

/*
    函数名:on_timerStop_clicked
    参数：无
    返回值：无
    功能：单击时关闭定时器
*/
void MainWindow::on_timerStop_clicked()
{
    ui->timerStart->setEnabled(true);
    ui->timerStop->setEnabled(false);
    portTimer.stop();
}

/********************************************************************************
*********************************采集设置*****************************************
********************************************************************************/

void MainWindow::on_caiji1qingling_clicked()
{
    portDataDeal myDataDeal;
    sendBuf = myDataDeal.send(qingling,0x01);
    myPort.write(sendBuf);
    ui->changdu1->clear();
    ui->sudu1->clear();
}

void MainWindow::on_caijiyitingzhi_clicked()
{
    portDataDeal myDataDeal;
    sendBuf = myDataDeal.send(tingzhi,0x01);
    myPort.write(sendBuf);
}

void MainWindow::on_caiji1kaishi_clicked()
{
/*    kaishi_Flag=!kaishi_Flag;
    if(!kaishi_Flag)
    {
        ui->caiji1kaishi->setText("开始");
        portTimer.stop();
    }
    else
    {

        portTimer.start(ui->timerEdit->text().toInt());
        ui->caiji1kaishi->setText("暂停");
        //kaishi_num_code=1;
        numCode = 1;
    }*/
}

void MainWindow::on_quanxuan_clicked()
{
    ui->caiji1check->setChecked(true);
    ui->caiji2check->setChecked(true);
    ui->caiji3check->setChecked(true);
    ui->caiji4check->setChecked(true);
    ui->caiji5check->setChecked(true);
    ui->caiji6check->setChecked(true);
    ui->caiji7check->setChecked(true);
    ui->caiji8check->setChecked(true);
    ui->caiji9check->setChecked(true);
}

void MainWindow::on_qingkongxuanxiang_clicked()
{
    ui->caiji1check->setChecked(false);
    ui->caiji2check->setChecked(false);
    ui->caiji3check->setChecked(false);
    ui->caiji4check->setChecked(false);
    ui->caiji5check->setChecked(false);
    ui->caiji6check->setChecked(false);
    ui->caiji7check->setChecked(false);
    ui->caiji8check->setChecked(false);
    ui->caiji9check->setChecked(false);
}

void MainWindow::on_quanxuan_2_clicked()
{

}

void MainWindow::on_zidongfasong_clicked()
{
    idFlag[0] = 0;
    idFlag[1] = ui->caiji1check->isChecked();
    idFlag[2] = ui->caiji2check->isChecked();
    idFlag[3] = ui->caiji3check->isChecked();
    idFlag[4] = ui->caiji4check->isChecked();
    idFlag[5] = ui->caiji5check->isChecked();
    idFlag[6] = ui->caiji6check->isChecked();
    idFlag[7] = ui->caiji7check->isChecked();
    idFlag[8] = ui->caiji8check->isChecked();
    idFlag[9] = ui->caiji9check->isChecked();

    QVector<QLineEdit *> myVector;
    myVector.append(ui->deng1);
    myVector.append(ui->deng2);
    myVector.append(ui->deng3);
    myVector.append(ui->deng4);
    myVector.append(ui->deng5);
    myVector.append(ui->deng6);
    myVector.append(ui->deng7);
    myVector.append(ui->deng8);
    myVector.append(ui->deng9);

    zidong=!zidong;
    if(!zidong)
    {
        ui->zidongfasong->setText("开始");
        portTimer.stop();
        for(int i = 1;i < 10;i++){
            myVector[i-1]->setStyleSheet("background-color: rgb(255, 0, 0);font-size:60px;color:blue");
        }
    }
    else
    {
        for(int i = 1;i < 10;i++){
            if(idFlag[i]){
                myVector[i-1]->setStyleSheet("background-color: rgb(0, 255, 0);font-size:60px;color:blue");
            }
        }

        ui->zidongfasong->setText("停止");
        portTimer.start(ui->cijizhouqi->text().toInt());
        numCode = 1;
        port_exe_number = 1;
    }
}

void MainWindow::on_shezhiButton_clicked()
{
    setNumber = 1;
    setTimer.start(200);
}

void MainWindow::on_moshidingchang_clicked()
{
    int temp = 0;
    QByteArray byteArray;
    byteArray.resize(10);
    for(int i = 0;i < 10;i ++){
        byteArray[i] = moshi[i];
    }

    if(ui->moshi1->isChecked()){
        temp = temp | 0x01;
    }
    if( ui->moshi2->isChecked()){
        temp = temp | 0x02;
    }
    if(ui->moshi3->isChecked()){
        temp = temp | 0x04;
    }
    if(ui->moshi4->isChecked()){
        temp = temp | 0x08;
    }
    byteArray[4] = byteArray[4] | temp;

    byteArray[1] = ui->moshi->currentText().toInt();

    temp = 0;
    for(int i = 1;i<8;i++){
        temp += byteArray[i];
    }
    byteArray[8] = temp;
    myPort.write(byteArray);


    union u_temp{
        int u;
        char u1[4];
    };

    union u_temp u_data;
    int mytemp = 0;
    u_data.u = ui->dingchangzhi->text().toUInt();
    for(int i = 4;i < 8;i ++){
        dingchangzhi1[i] = u_data.u1[i];
    }
    dingchangzhi1[1] = ui->moshi->currentText().toInt();
    for(int i = 1;i < 8;i ++){
        mytemp += dingchangzhi1[i];
    }

    dingchangzhi1[8] = mytemp;

    QByteArray dingArray;
    dingArray.resize(10);
    for(int i = 0;i < 10;i ++){
        dingArray[i] = dingchangzhi1[i];
    }

    myPort.write(dingArray);
}

void MainWindow::on_dingchang_clicked()
{
    union u_temp{
        int u;
        char u1[4];
    };

    union u_temp u_data;
    int mytemp = 0;
    u_data.u = ui->dingchangzhi->text().toInt();
    for(int i = 4;i < 8;i ++){

        dingchangzhi1[11-i] = u_data.u1[i-4];
    }
    dingchangzhi1[1] = ui->moshi->currentText().toInt();
    for(int i = 1;i < 8;i ++){
        mytemp += dingchangzhi1[i];
    }

    dingchangzhi1[8] = mytemp;

    QByteArray dingArray;
    dingArray.resize(10);
    for(int i = 0;i < 10;i ++){
        dingArray[i] = dingchangzhi1[i];
    }

    myPort.write(dingArray);
}

void MainWindow::on_pushButton_12_clicked()
{
    portDataDeal myDataDeal;
    sendBuf = myDataDeal.send(qingling,0x02);
    myPort.write(sendBuf);
}

void MainWindow::on_pushButton_13_clicked()
{
    portDataDeal myDataDeal;
    sendBuf = myDataDeal.send(tingzhi,0x02);
    myPort.write(sendBuf);
}

void MainWindow::on_pushButton_15_clicked()
{
    portDataDeal myDataDeal;
    sendBuf = myDataDeal.send(qingling,0x03);
    myPort.write(sendBuf);
}

void MainWindow::on_pushButton_16_clicked()
{
    portDataDeal myDataDeal;
    sendBuf = myDataDeal.send(tingzhi,0x03);
    myPort.write(sendBuf);
}

void MainWindow::on_pushButton_25_clicked()
{
    portDataDeal myDataDeal;
    sendBuf = myDataDeal.send(tingzhi,0x06);
    myPort.write(sendBuf);
}

void MainWindow::on_pushButton_24_clicked()
{
    portDataDeal myDataDeal;
    sendBuf = myDataDeal.send(qingling,0x06);
    myPort.write(sendBuf);
}

void MainWindow::on_pushButton_22_clicked()
{
    portDataDeal myDataDeal;
    sendBuf = myDataDeal.send(tingzhi,0x05);
    myPort.write(sendBuf);
}

void MainWindow::on_pushButton_21_clicked()
{
    portDataDeal myDataDeal;
    sendBuf = myDataDeal.send(qingling,0x05);
    myPort.write(sendBuf);
}

void MainWindow::on_pushButton_19_clicked()
{
    portDataDeal myDataDeal;
    sendBuf = myDataDeal.send(tingzhi,0x04);
    myPort.write(sendBuf);
}

void MainWindow::on_pushButton_18_clicked()
{
    portDataDeal myDataDeal;
    sendBuf = myDataDeal.send(qingling,0x04);
    myPort.write(sendBuf);
}

void MainWindow::on_pushButton_28_clicked()
{
    portDataDeal myDataDeal;
    sendBuf = myDataDeal.send(tingzhi,0x07);
    myPort.write(sendBuf);
}

void MainWindow::on_pushButton_27_clicked()
{
    portDataDeal myDataDeal;
    sendBuf = myDataDeal.send(qingling,0x07);
    myPort.write(sendBuf);
}

void MainWindow::on_pushButton_31_clicked()
{
    portDataDeal myDataDeal;
    sendBuf = myDataDeal.send(tingzhi,0x08);
    myPort.write(sendBuf);}

void MainWindow::on_pushButton_30_clicked()
{

    portDataDeal myDataDeal;
    sendBuf = myDataDeal.send(qingling,0x08);
    myPort.write(sendBuf);
}

void MainWindow::on_pushButton_34_clicked()
{
    portDataDeal myDataDeal;
    sendBuf = myDataDeal.send(tingzhi,0x09);
    myPort.write(sendBuf);
}

void MainWindow::on_pushButton_33_clicked()
{
    portDataDeal myDataDeal;
    sendBuf = myDataDeal.send(qingling,0x09);
    myPort.write(sendBuf);


}





void MainWindow::on_changdu1_cursorPositionChanged(int arg1, int arg2)
{

}

void MainWindow::on_pushButton_11_clicked()
{

}
