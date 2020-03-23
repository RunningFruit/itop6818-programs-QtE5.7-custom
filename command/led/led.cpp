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
//        exit(1);
    }
}

void led::led_toggle()
{
    LED=~LED;
    if(LED==0)
    {
        ioctl(fb,1,0);
    }
    else
    {
        ioctl(fb,0,0);
    }
}

void led::led_close()
{
   close(fb);
}
