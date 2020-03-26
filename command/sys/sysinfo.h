#ifndef MY_SYSINFO_H
#define MY_SYSINFO_H


#include <QObject>


class sysinfo:public QObject
{
public:
    explicit sysinfo();
    ~sysinfo();
    void getInfo();

};

#endif // MY_SYSINFO_H
