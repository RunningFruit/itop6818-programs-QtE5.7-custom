#ifndef MY_RELAY_H
#define MY_RELAY_H

#include <QObject>
#include <QDebug>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <sys/ioctl.h>
#include <stdio.h>
#include <QVariant>
#include <unistd.h>

class relay {

public:
    explicit relay();
    ~relay();

public:
    void relay_open();
    void relay_close();
};

#endif // MY_RELAY_H


