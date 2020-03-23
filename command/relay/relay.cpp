#include "relay.h"


#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <sys/ioctl.h>
#include <stdio.h>
#include <QVariant>
#include <unistd.h>

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
    fb=open("/dev/relay_ctl",0);

    if(fb<0)
    {
        perror("open device relay failed!");
        //        exit(1);
    }
}

void relay::relay_toggle()
{
    RELAY=~RELAY;
    if(RELAY)
    {
        ioctl(fb,1,1);
        printf ("ok");
    }
    else
    {
        ioctl(fb,0,0);
        printf ("ok");
    }
}


void relay::relay_close()
{
    ::close(fb);
}

