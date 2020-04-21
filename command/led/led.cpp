#include "led.h"


#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <sys/ioctl.h>
#include <stdio.h>
#include <stdio.h>
#include <unistd.h>
#include <cstdlib>


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
    fb=open("/dev/leds_ctl",0);
    if(fb<0)
    {
        perror("open device led failed!");
        exit(1);
    }

    LED=1;
    int OnOffTimes=3;

    while(OnOffTimes--)
    {
        printf("ioctl led %d times\n",OnOffTimes);
        ioctl(fb,1,0);
        sleep(1);
        ioctl(fb,0,0);
        sleep(1);
    }
}

void led::led_close()
{
    ioctl(fb,0,0);
    sleep(1);
    close(fb);
    printf ("led close ok");
}
