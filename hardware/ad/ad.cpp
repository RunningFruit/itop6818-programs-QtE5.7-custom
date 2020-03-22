#include "adtest.h"
#include "ui_adtest.h"


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

adtest::adtest(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::adtest)
{
    ui->setupUi(this);

    startTimer(500);
}

void adtest::timerEvent(QTimerEvent *)
{

    FILE *fd = fopen("/sys/bus/iio/devices/iio\:device0/in_voltage0_raw","rt");
    if(fd == NULL){
        printf("open filed\n");
        return;
    }
    printf("open success!");
    char buffer[30] = "";
    int len = fread(buffer,1,sizeof buffer - 1,fd);
    if(len > 0)
    {
        buffer[len] = '\0';
        int value = -1;
        sscanf(buffer,"%d",&value);
        m_label->display(value);
    }
    fclose(fd);
}

adtest::~adtest()
{
    delete ui;
}
