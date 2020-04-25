#ifndef MY_BUZZER_H
#define MY_BUZZER_H

#include <QObject>
#include <QDebug>

#include <sys/types.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <sys/ioctl.h>
#include <stdio.h>

#include <unistd.h>
#include <cstdlib>

class buzzer
{
public:
    explicit buzzer();
    ~buzzer();

public:
    void buzzer_open();
    void buzzer_close();

};

#endif // MY_BUZZER_H
