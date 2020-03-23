
#include "ad.h"

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

ad::ad(){
}

ad::~ad(){
}

void ad::open()
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
        printf("\n%d\n",value);
    }
    fclose(fd);
}
