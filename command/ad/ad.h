#ifndef MY_AD_H
#define MY_AD_H

#include <QObject>
#include <QDebug>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <linux/fs.h>
#include <errno.h>
#include <string.h>

class ad: public QObject
{
public:
    explicit ad();
    ~ad();

public:
    void open();

};

#endif // MY_AD_H
