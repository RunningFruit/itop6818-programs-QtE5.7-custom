#ifndef MY_LED_H
#define MY_LED_H

#include <QObject>
#include <QDebug>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <sys/ioctl.h>
#include <stdio.h>
#include <stdio.h>
#include <unistd.h>
#include <cstdlib>


class led
{

public:
    explicit led();
    ~led();

public:
    void led_open();
    void led_close();
};

#endif // MY_LED_H
