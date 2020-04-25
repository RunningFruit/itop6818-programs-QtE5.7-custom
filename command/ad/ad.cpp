#include "ad.h"


ad::ad(){
}

ad::~ad(){
}

void ad::open()
{

    FILE *fd = fopen("/sys/bus/iio/devices/iio\:device0/in_voltage0_raw","rt");
    if(fd == NULL){
        qDebug()<<("ad open filed")<<endl;
        return;
    }
    qDebug()<<("ad open success!")<<endl;
    char buffer[30] = "";
    int len = fread(buffer,1,sizeof buffer - 1,fd);
    if(len > 0)
    {
        buffer[len] = '\0';
        int value = -1;
        sscanf(buffer,"%d",&value);
        qDebug()<<endl;
        qDebug()<<value<<endl;
    }
    fclose(fd);
}
