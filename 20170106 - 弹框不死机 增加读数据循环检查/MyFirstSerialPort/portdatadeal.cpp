#include "portdatadeal.h"

//int kaishi[] = {0x55,0x01,0x08,0x05,0x00,0x00,0x00,0x00,0x0e,0xaa};
//int sudu[] = {0x55,0x01,0x08,0x85,0x00,0x00,0x00,0x00,0x8e,0xaa};
//int changdu[] ={0x55,0x01,0x08,0x84,0x00,0x00,0x00,0x00,0x8d,0xaa};
//int qingling[] = {0x55,0x01,0x08,0x04,0x00,0x00,0x00,0x00,0x0d,0xaa};
//int tingzhi[] = {0x55,0x01,0x08,0x05,0x00,0x00,0x00,0x00,0x0e,0xaa};

portDataDeal::portDataDeal()
{

}

QByteArray portDataDeal::send(int *data,int id)
{
    myArray.resize(10);
    for(int i=0;i<10;i++){
        myArray[i] = data[i];
    }
    myArray[1] = id;
    data[1] = id;
    myArray[8] = Check(data);
    return myArray;
}

QByteArray portDataDeal::timerSend(int idFlag[10], int* numCode,int *port_exe_number,int *data1,int *data2,int *data3)
{
    QByteArray data;
    int i =  *port_exe_number;
    switch (*numCode)
    {
    case 1:
        //data = send(kaishi,idFlag);

        //系统中增加测控路数时，
        for(;i<=PORAUTONUMBER;i++){
            if(idFlag[i] == 1){
                data = send(data1,i);
                *port_exe_number = i+1;
                if(*port_exe_number == PORAUTONUMBER+1){
                    *port_exe_number = 1;
                    *numCode=2;
                }
                break;
            }

            *port_exe_number = i+1;
            if(*port_exe_number == PORAUTONUMBER+1){
                *port_exe_number = 1;
                *numCode=2;
            }
        }

        break;
    case 2:
        //data = send(kaishi,idFlag);

        //系统中增加测控路数时，
        for(;i<=PORAUTONUMBER;i++){
            if(idFlag[i] == 1){
                data = send(data2,i);
                *port_exe_number = i+1;
                if(*port_exe_number == PORAUTONUMBER+1){
                    *port_exe_number = 1;
                    *numCode=3;
                }
                break;
            }
            *port_exe_number = i+1;
            if(*port_exe_number == PORAUTONUMBER+1){
                *port_exe_number = 1;
                *numCode=3;
            }
        }

        break;
    case 3:
        //data = send(kaishi,idFlag);
        //系统中增加测控路数时，
        for(;i<=PORAUTONUMBER;i++){
            if(idFlag[i] == 1){
                data = send(data3,i);
                *port_exe_number = i+1;
                if(*port_exe_number == PORAUTONUMBER+1){
                    *port_exe_number = 1;
                    *numCode=2;
                }
                break;
            }
             *port_exe_number = i+1;
            if(*port_exe_number == PORAUTONUMBER+1){
                *port_exe_number = 1;
                *numCode=2;
            }
        }

        break;
    default:
        break;
    }
    return data;
}

QString portDataDeal::read(int *data)
{
    return "";
}
void portDataDeal::codeDeal(int *id,int *flag,QString *mydata,QByteArray data)
{
    union u_temp{
        int u;
        char u1[4];
    };
    union u_temp u_show_data;
    int i=0;
    float show_temp;
    for(i=0;i<4;i++)
    {
        u_show_data.u1[i]=data[7-i];

    }

    switch (data[1]) {
    case 1:
        *id = 1;
        if(data[3] == 0x84){
            show_temp=u_show_data.u;
            show_temp=show_temp/1000;
            *mydata =mydata->number(show_temp,'f',3);
            *flag = 0x84;
        }else if(data[3] == 0x85){
            show_temp=u_show_data.u;
            show_temp=show_temp/1000;
            *mydata =mydata->number(show_temp,'f',3);
            *flag = 0x85;
        }
        else if(data[3] == 0x04){
                    *mydata =mydata->number(data[4]);
                    *flag = 0x04;
                }
        else if(data[3] == 0x0c){
                    *mydata =mydata->number(data[4]);
                    *flag = 0x0c;
                }
        else
        {
            *flag = 0xff;
        }

        break;
    case 2:
        *id = 2;
        if(data[3] == 0x84){
            show_temp=u_show_data.u;
            show_temp=show_temp/1000;
            *mydata =mydata->number(show_temp,'f',3);
            *flag = 0x84;
        }else if(data[3] == 0x85){
            show_temp=u_show_data.u;
            show_temp=show_temp/1000;
            *mydata =mydata->number(show_temp,'f',3);
            *flag = 0x85;
        }
        else if(data[3] == 0x04){
                    *mydata =mydata->number(data[4]);
                    *flag = 0x04;
                }
        else if(data[3] == 0x0c){
                    *mydata =mydata->number(data[4]);
                    *flag = 0x0c;
                }
        else
        {
            *flag = 0xff;
        }

        break;

    case 3:
        *id = 3;
        if(data[3] == 0x84){
            show_temp=u_show_data.u;
            show_temp=show_temp/1000;
            *mydata =mydata->number(show_temp,'f',3);
            *flag = 0x84;
        }else if(data[3] == 0x85){
            show_temp=u_show_data.u;
            show_temp=show_temp/1000;
            *mydata =mydata->number(show_temp,'f',3);
            *flag = 0x85;
        }
        else if(data[3] == 0x04){
                    *mydata =mydata->number(data[4]);
                    *flag = 0x04;
                }
        else if(data[3] == 0x0c){
                    *mydata =mydata->number(data[4]);
                    *flag = 0x0c;
                }
        else
        {
            *flag = 0xff;
        }

        break;

    case 4:
        *id = 4;
        if(data[3] == 0x84){
            show_temp=u_show_data.u;
            show_temp=show_temp/1000;
            *mydata =mydata->number(show_temp,'f',3);
            *flag = 0x84;
        }else if(data[3] == 0x85){
            show_temp=u_show_data.u;
            show_temp=show_temp/1000;
            *mydata =mydata->number(show_temp,'f',3);
            *flag = 0x85;
        }
        else if(data[3] == 0x04){
                    *mydata =mydata->number(data[4]);
                    *flag = 0x04;
                }
        else if(data[3] == 0x0c){
                    *mydata =mydata->number(data[4]);
                    *flag = 0x0c;
                }
        else
        {
            *flag = 0xff;
        }

        break;
    case 5:
        *id = 5;
        if(data[3] == 0x84){
            show_temp=u_show_data.u;
            show_temp=show_temp/1000;
            *mydata =mydata->number(show_temp,'f',3);
            *flag = 0x84;
        }else if(data[3] == 0x85){
            show_temp=u_show_data.u;
            show_temp=show_temp/1000;
            *mydata =mydata->number(show_temp,'f',3);
            *flag = 0x85;
        }
        else if(data[3] == 0x04){
                    *mydata =mydata->number(data[4]);
                    *flag = 0x04;
                }
        else if(data[3] == 0x0c){
                    *mydata =mydata->number(data[4]);
                    *flag = 0x0c;
                }
        else
        {
            *flag = 0xff;
        }

        break;

    case 6:
        *id = 6;
        if(data[3] == 0x84){
            show_temp=u_show_data.u;
            show_temp=show_temp/1000;
            *mydata =mydata->number(show_temp,'f',3);
            *flag = 0x84;
        }else if(data[3] == 0x85){
            show_temp=u_show_data.u;
            show_temp=show_temp/1000;
            *mydata =mydata->number(show_temp,'f',3);
            *flag = 0x85;
        }
        else if(data[3] == 0x04){
                    *mydata =mydata->number(data[4]);
                    *flag = 0x04;
                }
        else if(data[3] == 0x0c){
                    *mydata =mydata->number(data[4]);
                    *flag = 0x0c;
                }
        else
        {
            *flag = 0xff;
        }

        break;
    case 7:
        *id =7;
        if(data[3] == 0x84){
            show_temp=u_show_data.u;
            show_temp=show_temp/1000;
            *mydata =mydata->number(show_temp,'f',3);
            *flag = 0x84;
        }else if(data[3] == 0x85){
            show_temp=u_show_data.u;
            show_temp=show_temp/1000;
            *mydata =mydata->number(show_temp,'f',3);
            *flag = 0x85;
        }
        else if(data[3] == 0x04){
                    *mydata =mydata->number(data[4]);
                    *flag = 0x04;
                }
        else if(data[3] == 0x0c){
                    *mydata =mydata->number(data[4]);
                    *flag = 0x0c;
                }
        else
        {
            *flag = 0xff;
        }

        break;
    case 8:
        *id = 8;
        if(data[3] == 0x84){
            show_temp=u_show_data.u;
            show_temp=show_temp/1000;
            *mydata =mydata->number(show_temp,'f',3);
            *flag = 0x84;
        }else if(data[3] == 0x85){
            show_temp=u_show_data.u;
            show_temp=show_temp/1000;
            *mydata =mydata->number(show_temp,'f',3);
            *flag = 0x85;
        }
        else if(data[3] == 0x04){
                    *mydata =mydata->number(data[4]);
                    *flag = 0x04;
                }
        else if(data[3] == 0x0c){
                    *mydata =mydata->number(data[4]);
                    *flag = 0x0c;
                }
        else
        {
            *flag = 0xff;
        }

        break;
    case 9:
        *id = 9;
        if(data[3] == 0x84){
            show_temp=u_show_data.u;
            show_temp=show_temp/1000;
            *mydata =mydata->number(show_temp,'f',3);
            *flag = 0x84;
        }else if(data[3] == 0x85){
            show_temp=u_show_data.u;
            show_temp=show_temp/1000;
            *mydata =mydata->number(show_temp,'f',3);
            *flag = 0x85;
        }
        else if(data[3] == 0x04){
                    *mydata =mydata->number(data[4]);
                    *flag = 0x04;
                }
        else if(data[3] == 0x0c){
                    *mydata =mydata->number(data[4]);
                    *flag = 0x0c;
                }
        else
        {
            *flag = 0xff;
        }

        break;
    default:
        break;
    }
}

int portDataDeal::Check(int *data)
{
    unsigned char sum = 0;
    for(int i = 1;i<8;i++){
        sum += data[i];
    }
    return sum;
}

unsigned int portDataDeal::Check(QByteArray data)
{
    unsigned char sum = 0;
    for(int i = 1;i<8;i++){
        sum += data[i];
    }
    return sum;
}
