#include "relay.h"


static int fb;
volatile int RELAY=0;

relay::relay()
{
}

relay::~relay()
{
}

void relay::relay_open()
{
    qDebug()<< ("try to open relay ...")<<endl;
    fb=open("/dev/relay_ctl",0);

    if(fb<0)
    {
        //perror("open device relay failed!");
        qDebug()<< ("open relay failed!")<<endl;
        exit(1);
    }
    qDebug()<< ("open relay ok")<<endl;

    RELAY = 1;

    ioctl(fb,1,1);
}


void relay::relay_close()
{
    RELAY = 0;
    qDebug()<< ("try to close relay")<<endl;
    ioctl(fb,0,0);
    close(fb);
    qDebug()<< ("relay close ok")<<endl;
}

