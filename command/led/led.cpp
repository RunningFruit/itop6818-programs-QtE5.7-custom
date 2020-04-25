#include "led.h"


static int fb;
volatile int LED=0;


led::led()
{
}

led::~led()
{
}

void led::led_open()
{
    qDebug()<< ("try to open led ...")<<endl;
    fb=open("/dev/leds_ctl",0);
    if(fb<0)
    {
        //perror("open device led failed!");
        qDebug()<<("open led failed!")<<endl;
        exit(1);
    }
    qDebug()<< ("open led ok")<<endl;

    LED=1;
    int OnOffTimes=3;

    while(OnOffTimes--)
    {
        if(!LED){
            led_close();
            break;
        }
        qDebug()<<("ioctl led ")<<OnOffTimes<<" times"<<endl;
        ioctl(fb,1,0);
        sleep(1);
        ioctl(fb,0,0);
        sleep(1);
    }
}

void led::led_close()
{
    LED = 0;
    qDebug()<< ("try to close led...")<<endl;
    ioctl(fb,0,0);
    sleep(1);
    close(fb);
    qDebug()<< ("led close ok")<<endl;
}
