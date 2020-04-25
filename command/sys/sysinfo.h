#ifndef MY_SYSINFO_H
#define MY_SYSINFO_H


#include <QObject>
#include <QDebug>

#include <stdio.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <unistd.h>

class sysinfo:public QObject
{
public:
    explicit sysinfo();
    ~sysinfo();
    void getInfo();

};

#endif // MY_SYSINFO_H
