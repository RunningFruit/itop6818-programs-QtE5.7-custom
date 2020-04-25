#ifndef MY_GPS_H
#define MY_GPS_H

#include <QObject>
#include <QDebug>

#include <stdio.h>      /*标准输入输出定义*/
#include <stdlib.h>     /*标准函数库定义*/
#include <unistd.h>     /*Unix 标准函数定义*/
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>
#include <string.h>
#include <fcntl.h>
#include <termios.h>

class gps: public QObject
{
public:
    explicit gps();
    ~gps();

private:
    int m_fd;

public:
    void open_device();
    void close_device();
    int set_com_config(int fd, int baud_rate, int data_bits, char parity, int stop_bits);
    //打开串口函数
    int open_port(char* com_port);
    void print_info(void);
    void GPS_resolve_GPRMC(char data);
    void read_data();

};

#endif // MY_GPS_H
