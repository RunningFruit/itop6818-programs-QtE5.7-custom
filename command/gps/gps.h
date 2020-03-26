#ifndef MY_GPS_H
#define MY_GPS_H

#include <QObject>

class gps: public QObject
{
public:
    explicit gps();
    ~gps();

public:
    void open_device();
    int set_com_config(int fd, int baud_rate, int data_bits, char parity, int stop_bits);
    //打开串口函数
    int open_port(char* com_port);
    void print_info(void);
    void GPS_resolve_GPRMC(char data);
    void read_data(int fd);

};

#endif // MY_GPS_H
