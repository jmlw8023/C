#pragma once
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <time.h>
#include <cstring>
#include<WINSOCK2.H>  
#include<STDIO.H>  
#include<iostream>  
#include<cstring>  
#include <string>
#include<WS2tcpip.h>
//#include "modbus.h"     //引用 libmodbus库
using namespace std;
#pragma comment(lib, "ws2_32.lib")  

//#define IP_ADDR     "172.10.6.36"
#define IP_ADDR_8      "192.168.10.232"         //5#3##8
#define IP_ADDR_11     "192.168.10.238"        //4#4##11
#define IP_ADDR_12     "192.168.10.231"        //5#3##12
#define IP_ADDR_20     "192.168.10.239"        //4#3##20
#define IP_ADDR_23     "192.168.10.233"        //5#7##23
#define IP_ADDR_29     "192.168.10.240"        //5#3##29
#define IP_ADDR_30     "192.168.10.237"        //5#7##30
#define IP_ADDR_31     "192.168.10.235"        //5#6##31
#define IP_ADDR_32     "192.168.10.236"        //5#7##32
#define IP_ADDR_33     "192.168.10.234"        //4#2##33

#define SERVER          0x03
//#define BUF_LEN         64
#define IP_PORT         9999
#define COM_VALUE        5

int main(int argc,char *argv[])
{
  
    int status = 0;
    int ret, tx;
    char recData[255] = { 0 };
    uint16_t rx_data[64] = { 0 };
    SOCKET scl;
    sockaddr_in Addr;
    time_t in_time, out_time; //设置时间
    float current;
    //char recvbuf[BUF_LEN] = { 0 };
    //uint16_t tx_data[] = { 0x02,0x03,0x00,0x00,0x00,0x02,0xC4,0x38 };//020300000002C438
    //int tx_data_len = sizeof(tx_data) / sizeof(tx_data[0]);
    //const char sendData2[] = { 0x02,0x03,0x00,0x00,0x00,0x02,0xC4,0x38 };//温度传感器
    //const char sendData3[] = { 0x03,0x03,0x00,0x00,0x00,0x02,0xC5,0xE9 };//温度传感器

    const char sendData8[] =  { 0x08,0x03,0x00,0x48,0x00,0x0A,0x45,0x42 };//电流传感器 08 03 00 48 00 0A 45 42
    const char sendData11[] = { 0x0B,0x03,0x00,0x48,0x00,0x0A,0x45,0x71 };//0B 03 00 48 00 0A 45 71
    const char sendData12[] = { 0x0C,0x03,0x00,0x48,0x00,0x0A,0x44,0xC6 };//0C 03 00 48 00 0A 44 C6
    const char sendData20[] = { 0x14,0x03,0x00,0x48,0x00,0x0A,0x47,0x1E };//14 03 00 48 00 0A 47 1E
    const char sendData23[] = { 0x17,0x03,0x00,0x48,0x00,0x0A,0x47,0x2D };//17 03 00 48 00 0A 47 2D
    const char sendData29[] = { 0x1D,0x03,0x00,0x48,0x00,0x0A,0x47,0x87 };//1D 03 00 48 00 0A 47 87
    const char sendData30[] = { 0x1E,0x03,0x00,0x48,0x00,0x0A,0x47,0xB4 };//1E 03 00 48 00 0A 47 B4
    const char sendData31[] = { 0x1F,0x03,0x00,0x48,0x00,0x0A,0x46,0x65 };//1F 03 00 48 00 0A 46 65
    const char sendData32[] = { 0x20,0x03,0x00,0x48,0x00,0x0A,0x43,0x6A };//20 03 00 48 00 0A 43 6A
    const char sendData33[] = { 0x21,0x03,0x00,0x48,0x00,0x0A,0x42,0xBB };//21 03 00 48 00 0A 42 BB
   
    //初始化WSA windows自带的socket
    WORD sockVersion = MAKEWORD(2, 2);
    WSADATA data;
    if (WSAStartup(sockVersion, &data) != 0)
    {
        return 0;
    }

    //创建客户端套接字
    while (1)
    {

        //第一个传感器
        SOCKET sclient8 = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP); //客户端套接字
        if (sclient8 == INVALID_SOCKET)
        {
            printf("invalid  socket8!");
            return 0;
        }
        printf("start connet!!\n");
        sockaddr_in serAddr8;
        serAddr8.sin_family = AF_INET;
        serAddr8.sin_port = htons(IP_PORT); //监听端口
        inet_pton(AF_INET, IP_ADDR_8, (void*)&serAddr8.sin_addr.S_un.S_addr);
        if (connect(sclient8, (sockaddr*)&serAddr8, sizeof(serAddr8)) == SOCKET_ERROR) //与指定IP地址和端口的服务端连接
        {
            printf("connect sclient8 error !");
            closesocket(sclient8);
            return 0;
        }
        else
        {
            cout << "connect sclient8 success !" << endl;
        }
       
        Sleep(1000);//延时一秒
        //数据发送
        send(sclient8, sendData8, sizeof(sendData8), 0);  

        //设置时间
        //time(&in_time);
        //cout << "in time:" << time(&in_time) << endl;
        //Sleep(1000);
        //time(&out_time);
        //cout << "out time:" << time(&out_time) << endl;
        //cout << "stop time:" << out_time-in_time  << endl;
 
        //数据接收
        //ZeroMemory(recData, sizeof(recData));
        //cout <<  "接收到server的报文是："  <<  endl;
        ret = recv(sclient8, recData, 64, 0);
        printf("the recv data is:\n");
        //cout <<  "the recv data is:" <<  ret << endl;
        if (ret > 0) 
        {
           // recData[ret] = 0x00;
            //printf(recData);
            for (size_t i = 0; i < ret; i++)
            {
                rx_data[i] = recData[i];
                printf("%02X\n", recData[i]);
            }
            cout << endl;
        }
        for (size_t i = 0; i < ret; i++)
        {
            printf("%8X",rx_data[i]);
        }       
        current = (float)((rx_data[5] << 8) | rx_data[6]);
        printf("\nCurrent is :%4f \n", current/1000);
        Sleep(1000);
        cout << endl << "over" << endl;
        closesocket(sclient8);

        //链接服务器
        scl = socket(AF_INET, SOCK_STREAM, 0); //客户端套接字IPPROTO_TCP
        if (scl == INVALID_SOCKET)
        {
            printf("invalid socket!");
            return 0;
        }
     
        Addr.sin_family = AF_INET;
        Addr.sin_port = htons(6688); //监听端口
        //Addr.sin_addr.s_addr = inet_addr("192.168.10.119");
        inet_pton(AF_INET, "192.168.10.119 ", (void*)&Addr.sin_addr.S_un.S_addr);
        if (connect(scl, (sockaddr*)&Addr, sizeof(Addr)) == SOCKET_ERROR) //与指定IP地址和端口的服务端连接
        {
            printf("connect error !");
            closesocket(scl);
            return 0;
        }
        else
        {
            cout << "============ connect success ===========!" << endl;
        }
        char  text[] = "this is a test!!!\n";
        tx = send(scl, text, sizeof(text), 0);  //数据发送
        printf("tx = %d\n", tx);


        //第二个传感器连接
        SOCKET sclient11 = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP); //客户端套接字
        if (sclient11 == INVALID_SOCKET)
        {
            printf("invalid  socket11!");
            return 0;
        }

        printf("start connet11!!\n");
        sockaddr_in serAddr11;
        serAddr11.sin_family = AF_INET;
        serAddr11.sin_port = htons(IP_PORT); //监听端口
        inet_pton(AF_INET, IP_ADDR_11, (void*)&serAddr11.sin_addr.S_un.S_addr);
        if (connect(sclient11, (sockaddr*)&serAddr11, sizeof(serAddr11)) == SOCKET_ERROR) //与指定IP地址和端口的服务端连接
        {
            printf("connect sclient31 error !");
            closesocket(sclient11);
            return 0;
        }
        else
        {
            cout << "connect sclient31 success !" << endl;
        }

        Sleep(1000);//延时一秒
        //数据发送
        send(sclient11, sendData11, sizeof(sendData11), 0);

       // //设置时间
       // //time_t in_time, out_time;
       // time(&in_time);
       // cout << "in time:" << time(&in_time) << endl;
       // //Sleep(3000);
       // time(&out_time);
       // cout << "out time:" << time(&out_time) << endl;
       // cout << "stop time:" << out_time - in_time << endl;

        //数据接收
        ret = recv(sclient11, recData, 64, 0);
        printf("the recv data is:\n");
        for (size_t i = 0; i < ret; i++)
        {
            printf("%6X", recData[i]);
        }
        current = (float)((recData[5] << 8) | recData[6]);
        printf("\nCurrent is :%4f \n", current / 1000);
        Sleep(1000);
        cout << endl << "over" << endl;
        closesocket(sclient11);

        //链接服务器
         scl = socket(AF_INET, SOCK_STREAM, 0); //客户端套接字IPPROTO_TCP
        if (scl == INVALID_SOCKET)
        {
            printf("invalid socket!");
            return 0;
        }
       
        Addr.sin_family = AF_INET;
        Addr.sin_port = htons(6688); //监听端口
        //Addr.sin_addr.s_addr = inet_addr("192.168.10.119");
        inet_pton(AF_INET, "192.168.10.119 ", (void*)&Addr.sin_addr.S_un.S_addr);
        if (connect(scl, (sockaddr*)&Addr, sizeof(Addr)) == SOCKET_ERROR) //与指定IP地址和端口的服务端连接
        {
            printf("connect error !");
            closesocket(scl);
            return 0;
        }
        else
        {
            cout << "============ connect success ===========!" << endl;
        }
        //char  text[] = "this is a test!!!\n";
        tx = send(scl, text, sizeof(text), 0);  //数据发送
        printf("tx = %d\n", tx);
        memset(recData, 0, sizeof(recData));


       // //第三个传感器连接
       // SOCKET sclient12 = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP); //客户端套接字
       // if (sclient12 == INVALID_SOCKET)
       // {
       //     printf("invalid  socket12!");
       //     return 0;
       // }

       // printf("start connet12!!\n");
       // sockaddr_in serAddr12;
       // serAddr12.sin_family = AF_INET;
       // serAddr12.sin_port = htons(IP_PORT); //监听端口
       // inet_pton(AF_INET, IP_ADDR_12, (void*)&serAddr12.sin_addr.S_un.S_addr);
       // if (connect(sclient12, (sockaddr*)&serAddr12, sizeof(serAddr12)) == SOCKET_ERROR) //与指定IP地址和端口的服务端连接
       // {
       //     printf("connect sclient12 error !");
       //     closesocket(sclient12);
       //     return 0;
       // }
       // else
       // {
       //     cout << "connect sclient12 success !" << endl;
       // }

       // Sleep(1000);//延时一秒
       // //数据发送
       // send(sclient12, sendData12, sizeof(sendData12), 0);

       // //设置时间
       // //time_t in_time, out_time;
       // time(&in_time);
       // cout << "in time:" << time(&in_time) << endl;
       // Sleep(1000);
       // time(&out_time);
       // cout << "out time:" << time(&out_time) << endl;
       // cout << "stop time:" << out_time - in_time << endl;

       // //数据接收
       // ret = recv(sclient12, recData, 64, 0);
       // printf("the recv data is:\n");
       // for (size_t i = 0; i < ret; i++)
       // {
       //     printf("%6X", rx_data[i]);
       // }
       // current = (float)((rx_data[5] << 8) | rx_data[6]);
       // printf("\nCurrent is :%4f \n", current / 1000);
       // Sleep(1000);
       // cout << endl << "over" << endl;
       // closesocket(sclient12);

       // //链接服务器
       // scl = socket(AF_INET, SOCK_STREAM, 0); //客户端套接字IPPROTO_TCP
       // if (scl == INVALID_SOCKET)
       // {
       //     printf("invalid socket!");
       //     return 0;
       // }
       // 
       // Addr.sin_family = AF_INET;
       // Addr.sin_port = htons(6688); //监听端口
       // //Addr.sin_addr.s_addr = inet_addr("192.168.10.119");
       // inet_pton(AF_INET, "192.168.10.119 ", (void*)&Addr.sin_addr.S_un.S_addr);
       // if (connect(scl, (sockaddr*)&Addr, sizeof(Addr)) == SOCKET_ERROR) //与指定IP地址和端口的服务端连接
       // {
       //     printf("connect error !");
       //     closesocket(scl);
       //     return 0;
       // }
       // else
       // {
       //     cout << "============ connect success ===========!" << endl;
       // }

       // tx = send(scl, text, sizeof(text), 0);  //数据发送
       // printf("tx = %d\n", tx);
       //memset(recData, 0, sizeof(recData));

       // //第四个传感器连接
       // SOCKET sclient20 = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP); //客户端套接字
       // if (sclient20 == INVALID_SOCKET)
       // {
       //     printf("invalid  socket31!");
       //     return 0;
       // }

       // printf("start connet20!!\n");
       // sockaddr_in serAddr20;
       // serAddr20.sin_family = AF_INET;
       // serAddr20.sin_port = htons(IP_PORT); //监听端口
       // inet_pton(AF_INET, IP_ADDR_20, (void*)&serAddr20.sin_addr.S_un.S_addr);
       // if (connect(sclient20, (sockaddr*)&serAddr20, sizeof(serAddr20)) == SOCKET_ERROR) //与指定IP地址和端口的服务端连接
       // {
       //     printf("connect sclient20 error !");
       //     closesocket(sclient20);
       //     return 0;
       // }
       // else
       // {
       //     cout << "connect sclient20 success !" << endl;
       // }

       // Sleep(1000);//延时一秒
       // //数据发送
       // send(sclient20, sendData20, sizeof(sendData20), 0);

       // //设置时间
       // //time_t in_time, out_time;
       // time(&in_time);
       // cout << "in time:" << time(&in_time) << endl;
       // Sleep(3000);
       // time(&out_time);
       // cout << "out time:" << time(&out_time) << endl;
       // cout << "stop time:" << out_time - in_time << endl;

       // //数据接收
       // ret = recv(sclient20, recData, 64, 0);
       // printf("the recv data is:\n");
       // for (size_t i = 0; i < ret; i++)
       // {
       //     printf("%6X", rx_data[i]);
       // }
       // current = (float)((rx_data[5] << 8) | rx_data[6]);
       // printf("\nCurrent is :%4f \n", current / 1000);
       // Sleep(1000);
       // cout << endl << "over" << endl;
       // closesocket(sclient20);

       // //链接服务器
       // scl = socket(AF_INET, SOCK_STREAM, 0); //客户端套接字IPPROTO_TCP
       // if (scl == INVALID_SOCKET)
       // {
       //     printf("invalid socket!");
       //     return 0;
       // }

       // Addr.sin_family = AF_INET;
       // Addr.sin_port = htons(6688); //监听端口
       // //Addr.sin_addr.s_addr = inet_addr("192.168.10.119");
       // inet_pton(AF_INET, "192.168.10.119 ", (void*)&Addr.sin_addr.S_un.S_addr);
       // if (connect(scl, (sockaddr*)&Addr, sizeof(Addr)) == SOCKET_ERROR) //与指定IP地址和端口的服务端连接
       // {
       //     printf("connect error !");
       //     closesocket(scl);
       //     return 0;
       // }
       // else
       // {
       //     cout << "============ connect success ===========!" << endl;
       // }
       // //char  text[] = "this is a test sclient20!!!\n";
       // tx = send(scl, text, sizeof(text), 0);  //数据发送
       // printf("tx = %d\n", tx);



       // //第五个传感器连接
       // SOCKET sclient23 = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP); //客户端套接字
       // if (sclient23 == INVALID_SOCKET)
       // {
       //     printf("invalid  socket23!");
       //     return 0;
       // }

       // printf("start connet23!!\n");
       // sockaddr_in serAddr23;
       // serAddr23.sin_family = AF_INET;
       // serAddr23.sin_port = htons(IP_PORT); //监听端口
       // inet_pton(AF_INET, IP_ADDR_23, (void*)&serAddr23.sin_addr.S_un.S_addr);
       // if (connect(sclient23, (sockaddr*)&serAddr23, sizeof(serAddr23)) == SOCKET_ERROR) //与指定IP地址和端口的服务端连接
       // {
       //     printf("connect sclient23 error !");
       //     closesocket(sclient23);
       //     return 0;
       // }
       // else
       // {
       //     cout << "connect sclient23 success !" << endl;
       // }

       // Sleep(1000);//延时一秒
       // //数据发送
       // send(sclient23, sendData23, sizeof(sendData23), 0);

       // //设置时间
       // //time_t in_time, out_time;
       // time(&in_time);
       // cout << "in time:" << time(&in_time) << endl;
       // Sleep(3000);
       // time(&out_time);
       // cout << "out time:" << time(&out_time) << endl;
       // cout << "stop time:" << out_time - in_time << endl;

       // //数据接收
       // ret = recv(sclient23, recData, 64, 0);
       // printf("the recv data is:\n");
       // for (size_t i = 0; i < ret; i++)
       // {
       //     printf("%6X", rx_data[i]);
       // }
       // current = (float)((rx_data[5] << 8) | rx_data[6]);
       // printf("\nCurrent is :%4f \n", current / 1000);
       // Sleep(1000);
       // cout << endl << "over" << endl;
       // closesocket(sclient23);

       // //链接服务器
       // scl = socket(AF_INET, SOCK_STREAM, 0); //客户端套接字IPPROTO_TCP
       // if (scl == INVALID_SOCKET)
       // {
       //     printf("invalid socket!");
       //     return 0;
       // }
 
       // Addr.sin_family = AF_INET;
       // Addr.sin_port = htons(6688); //监听端口
       // //Addr.sin_addr.s_addr = inet_addr("192.168.10.119");
       // inet_pton(AF_INET, "192.168.10.119 ", (void*)&Addr.sin_addr.S_un.S_addr);
       // if (connect(scl, (sockaddr*)&Addr, sizeof(Addr)) == SOCKET_ERROR) //与指定IP地址和端口的服务端连接
       // {
       //     printf("connect error !");
       //     closesocket(scl);
       //     return 0;
       // }
       // else
       // {
       //     cout << "============ connect success ===========!" << endl;
       // }
       //// char  text[] = "this is a test!!!\n";
       // tx = send(scl, text, sizeof(text), 0);  //数据发送
       // printf("tx = %d\n", tx);


       // //第六个传感器连接
       // SOCKET sclient29 = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP); //客户端套接字
       // if (sclient29 == INVALID_SOCKET)
       // {
       //     printf("invalid  socket29!");
       //     return 0;
       // }

       // printf("start connet29!!\n");
       // sockaddr_in serAddr29;
       // serAddr29.sin_family = AF_INET;
       // serAddr29.sin_port = htons(IP_PORT); //监听端口
       // inet_pton(AF_INET, IP_ADDR_31, (void*)&serAddr29.sin_addr.S_un.S_addr);
       // if (connect(sclient29, (sockaddr*)&serAddr29, sizeof(serAddr29)) == SOCKET_ERROR) //与指定IP地址和端口的服务端连接
       // {
       //     printf("connect sclient31 error !");
       //     closesocket(sclient29);
       //     return 0;
       // }
       // else
       // {
       //     cout << "connect sclient29 success !" << endl;
       // }

       // Sleep(1000);//延时一秒
       // //数据发送
       // send(sclient29, sendData29, sizeof(sendData29), 0);

       // //设置时间
       // //time_t in_time, out_time;
       // time(&in_time);
       // cout << "in time:" << time(&in_time) << endl;
       // Sleep(3000);
       // time(&out_time);
       // cout << "out time:" << time(&out_time) << endl;
       // cout << "stop time:" << out_time - in_time << endl;

       // //数据接收
       // ret = recv(sclient29, recData, 64, 0);
       // printf("the recv data is:\n");
       // for (size_t i = 0; i < ret; i++)
       // {
       //     printf("%6X", rx_data[i]);
       // }
       // current = (float)((rx_data[5] << 8) | rx_data[6]);
       // printf("\nCurrent is :%4f \n", current / 1000);
       // Sleep(1000);
       // cout << endl << "over" << endl;
       // closesocket(sclient29);

       // //链接服务器
       // scl = socket(AF_INET, SOCK_STREAM, 0); //客户端套接字IPPROTO_TCP
       // if (scl == INVALID_SOCKET)
       // {
       //     printf("invalid socket!");
       //     return 0;
       // }
      
       // Addr.sin_family = AF_INET;
       // Addr.sin_port = htons(6688); //监听端口
       // //Addr.sin_addr.s_addr = inet_addr("192.168.10.119");
       // inet_pton(AF_INET, "192.168.10.119 ", (void*)&Addr.sin_addr.S_un.S_addr);
       // if (connect(scl, (sockaddr*)&Addr, sizeof(Addr)) == SOCKET_ERROR) //与指定IP地址和端口的服务端连接
       // {
       //     printf("connect error !");
       //     closesocket(scl);
       //     return 0;
       // }
       // else
       // {
       //     cout << "============ connect success ===========!" << endl;
       // }
       //// char  text[] = "this is a test sclient29!!!\n";
       //tx = send(scl, text, sizeof(text), 0);  //数据发送
       // printf("tx = %d\n", tx);


       // //第七个传感器连接
       // SOCKET sclient30 = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP); //客户端套接字
       // if (sclient30 == INVALID_SOCKET)
       // {
       //     printf("invalid  socket31!");
       //     return 0;
       // }
       // printf("start connet30!!\n");
       // sockaddr_in serAddr30;
       // serAddr30.sin_family = AF_INET;
       // serAddr30.sin_port = htons(IP_PORT); //监听端口
       // inet_pton(AF_INET, IP_ADDR_30, (void*)&serAddr30.sin_addr.S_un.S_addr);
       // if (connect(sclient30, (sockaddr*)&serAddr30, sizeof(serAddr30)) == SOCKET_ERROR) //与指定IP地址和端口的服务端连接
       // {
       //     printf("connect sclient30 error !");
       //     closesocket(sclient30);
       //     return 0;
       // }
       // else
       // {
       //     cout << "connect sclient30 success !" << endl;
       // }
       // Sleep(1000);//延时一秒
       // //数据发送
       // send(sclient30, sendData30, sizeof(sendData30), 0);

       // //设置时间
       // //time_t in_time, out_time;
       // time(&in_time);
       // cout << "in time:" << time(&in_time) << endl;
       // Sleep(3000);
       // time(&out_time);
       // cout << "out time:" << time(&out_time) << endl;
       // cout << "stop time:" << out_time - in_time << endl;

       // //数据接收
       // ret = recv(sclient30, recData, 64, 0);
       // printf("the recv data is:\n");
       // for (size_t i = 0; i < ret; i++)
       // {
       //     printf("%6X", rx_data[i]);
       // }
       // current = (float)((rx_data[5] << 8) | rx_data[6]);
       // printf("\nCurrent is :%4f \n", current / 1000);
       // Sleep(1000);
       // cout << endl << "over" << endl;
       // closesocket(sclient30);

       // //链接服务器
       // scl = socket(AF_INET, SOCK_STREAM, 0); //客户端套接字IPPROTO_TCP
       // if (scl == INVALID_SOCKET)
       // {
       //     printf("invalid socket!");
       //     return 0;
       // }
      
       // Addr.sin_family = AF_INET;
       // Addr.sin_port = htons(6688); //监听端口
       // //Addr.sin_addr.s_addr = inet_addr("192.168.10.119");
       // inet_pton(AF_INET, "192.168.10.119 ", (void*)&Addr.sin_addr.S_un.S_addr);
       // if (connect(scl, (sockaddr*)&Addr, sizeof(Addr)) == SOCKET_ERROR) //与指定IP地址和端口的服务端连接
       // {
       //     printf("connect error !");
       //     closesocket(scl);
       //     return 0;
       // }
       // else
       // {
       //     cout << "============ connect success ===========!" << endl;
       // }
       // //char  text[] = "this is a test sclient30 !!!\n";
       // tx = send(scl, text, sizeof(text), 0);  //数据发送
       // printf("tx = %d\n", tx);


        //第八个传感器连接
        SOCKET sclient31 = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP); //客户端套接字
        if (sclient31 == INVALID_SOCKET)
        {
            printf("invalid  socket31!");
            return 0;
        }

        printf("start connet31!!\n");
        sockaddr_in serAddr31;
        serAddr31.sin_family = AF_INET;
        serAddr31.sin_port = htons(IP_PORT); //监听端口
        inet_pton(AF_INET, IP_ADDR_31, (void*)&serAddr31.sin_addr.S_un.S_addr);
        if (connect(sclient31, (sockaddr*)&serAddr31, sizeof(serAddr31)) == SOCKET_ERROR) //与指定IP地址和端口的服务端连接
        {
            printf("connect sclient31 error !");
            closesocket(sclient31);
            return 0;
        }
        else
        {
            cout << "connect sclient31 success !" << endl;
        }

        Sleep(1000);//延时一秒
        //数据发送
        send(sclient31, sendData31, sizeof(sendData31), 0);

       // //设置时间
       // //time_t in_time, out_time;
       // time(&in_time);
       // cout << "in time:" << time(&in_time) << endl;
       // Sleep(3000);
       // time(&out_time);
       // cout << "out time:" << time(&out_time) << endl;
       // cout << "stop time:" << out_time - in_time << endl;

        //数据接收
        ret = recv(sclient31, recData, 64, 0);
        printf("the recv data is:\n");
        for (size_t i = 0; i < ret; i++)
        {
            printf("%6X", rx_data[i]);
        }
        current = (float)((rx_data[5] << 8) | rx_data[6]);
        printf("\nCurrent is :%4f \n", current / 1000);
        Sleep(1000);
        cout << endl << "over" << endl;
        closesocket(sclient31);

        //链接服务器
         scl = socket(AF_INET, SOCK_STREAM, 0); //客户端套接字IPPROTO_TCP
        if (scl == INVALID_SOCKET)
        {
            printf("invalid socket!");
            return 0;
        }
     
        Addr.sin_family = AF_INET;
        Addr.sin_port = htons(6688); //监听端口
        //Addr.sin_addr.s_addr = inet_addr("192.168.10.119");
        inet_pton(AF_INET, "192.168.10.119 ", (void*)&Addr.sin_addr.S_un.S_addr);
        if (connect(scl, (sockaddr*)&Addr, sizeof(Addr)) == SOCKET_ERROR) //与指定IP地址和端口的服务端连接
        {
            printf("connect error !");
            closesocket(scl);
            return 0;
        }
        else
        {
            cout << "============ connect success ===========!" << endl;
        }
        //char  text[] = "this is a test sclient31!!!\n";
        tx = send(scl, text, sizeof(text), 0);  //数据发送
        printf("tx = %d\n", tx);


       // //第九个传感器连接
       // SOCKET sclient32 = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP); //客户端套接字
       // if (sclient32 == INVALID_SOCKET)
       // {
       //     printf("invalid  socket32!");
       //     return 0;
       // }

       // printf("start socket32!!\n");
       // sockaddr_in serAddr32;
       // serAddr32.sin_family = AF_INET;
       // serAddr32.sin_port = htons(IP_PORT); //监听端口
       // inet_pton(AF_INET, IP_ADDR_32, (void*)&serAddr32.sin_addr.S_un.S_addr);
       // if (connect(sclient32, (sockaddr*)&serAddr32, sizeof(serAddr32)) == SOCKET_ERROR) //与指定IP地址和端口的服务端连接
       // {
       //     printf("connect sclient32 error !");
       //     closesocket(sclient32);
       //     return 0;
       // }
       // else
       // {
       //     cout << "connect sclient32 success !" << endl;
       // }

       // Sleep(1000);//延时一秒
       // //数据发送
       // send(sclient32, sendData32, sizeof(sendData32), 0);

       // //设置时间
       // //time_t in_time, out_time;
       // time(&in_time);
       // cout << "in time:" << time(&in_time) << endl;
       // Sleep(3000);
       // time(&out_time);
       // cout << "out time:" << time(&out_time) << endl;
       // cout << "stop time:" << out_time - in_time << endl;

       // //数据接收
       // ret = recv(sclient32, recData, 64, 0);
       // printf("the recv data is:\n");
       // for (size_t i = 0; i < ret; i++)
       // {
       //     printf("%6X", rx_data[i]);
       // }
       // current = (float)((rx_data[5] << 8) | rx_data[6]);
       // printf("\nCurrent is :%4f \n", current / 1000);
       // Sleep(1000);
       // cout << endl << "over" << endl;
       // closesocket(sclient32);

       // //链接服务器
       //scl = socket(AF_INET, SOCK_STREAM, 0); //客户端套接字IPPROTO_TCP
       // if (scl == INVALID_SOCKET)
       // {
       //     printf("invalid socket32!");
       //     return 0;
       // }

       // Addr.sin_family = AF_INET;
       // Addr.sin_port = htons(6688); //监听端口
       // //Addr.sin_addr.s_addr = inet_addr("192.168.10.119");
       // inet_pton(AF_INET, "192.168.10.119 ", (void*)&Addr.sin_addr.S_un.S_addr);
       // if (connect(scl, (sockaddr*)&Addr, sizeof(Addr)) == SOCKET_ERROR) //与指定IP地址和端口的服务端连接
       // {
       //     printf("connect sclient32 error !");
       //     closesocket(scl);
       //     return 0;
       // }
       // else
       // {
       //     cout << "============ connect success ===========!" << endl;
       // }
       //// char  text[] = "this is a test sclient32!!!\n";
       // tx = send(scl, text, sizeof(text), 0);  //数据发送
       // printf("tx = %d\n", tx);


       // //第十个传感器连接
       // SOCKET sclient33 = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP); //客户端套接字
       // if (sclient33 == INVALID_SOCKET)
       // {
       //     printf("invalid  socket33!");
       //     return 0;
       // }

       // printf("start connet33!!\n");
       // sockaddr_in serAddr33;
       // serAddr33.sin_family = AF_INET;
       // serAddr33.sin_port = htons(IP_PORT); //监听端口
       // inet_pton(AF_INET, IP_ADDR_33, (void*)&serAddr33.sin_addr.S_un.S_addr);
       // if (connect(sclient33, (sockaddr*)&serAddr33, sizeof(serAddr33)) == SOCKET_ERROR) //与指定IP地址和端口的服务端连接
       // {
       //     printf("connect sclient33 error !");
       //     closesocket(sclient33);
       //     return 0;
       // }
       // else
       // {
       //     cout << "connect sclient33 success !" << endl;
       // }

       // Sleep(1000);//延时一秒
       // //数据发送
       // send(sclient33, sendData33, sizeof(sendData33), 0);

       // //设置时间
       // //time_t in_time, out_time;
       // time(&in_time);
       // cout << "in time:" << time(&in_time) << endl;
       // Sleep(3000);
       // time(&out_time);
       // cout << "out time:" << time(&out_time) << endl;
       // cout << "stop time:" << out_time - in_time << endl;

       // //数据接收
       // ret = recv(sclient33, recData, 64, 0);
       // printf("the recv data is:\n");
       // for (size_t i = 0; i < ret; i++)
       // {
       //     printf("%6X", rx_data[i]);
       // }
       //  current = (float)((rx_data[5] << 8) | rx_data[6]);
       // printf("\nCurrent is :%4f \n", current / 1000);
       // Sleep(1000);
       // cout << endl << "over" << endl;
       // closesocket(sclient31);

       // //链接服务器
       //  scl = socket(AF_INET, SOCK_STREAM, 0); //客户端套接字IPPROTO_TCP
       // if (scl == INVALID_SOCKET)
       // {
       //     printf("invalid socket!");
       //     return 0;
       // }
 
       // Addr.sin_family = AF_INET;
       // Addr.sin_port = htons(6688); //监听端口
       // //Addr.sin_addr.s_addr = inet_addr("192.168.10.119");
       // inet_pton(AF_INET, "192.168.10.119 ", (void*)&Addr.sin_addr.S_un.S_addr);
       // if (connect(scl, (sockaddr*)&Addr, sizeof(Addr)) == SOCKET_ERROR) //与指定IP地址和端口的服务端连接
       // {
       //     printf("connect error !");
       //     closesocket(scl);
       //     return 0;
       // }
       // else
       // {
       //     cout << "============ connect success ===========!" << endl;
       // }
       // //char  text[] = "this is a test sclient33!!!\n";
       // tx = send(scl, text, sizeof(text), 0);  //数据发送
       // printf("tx = %d\n", tx);


    }
    WSACleanup();
    return 0;

}