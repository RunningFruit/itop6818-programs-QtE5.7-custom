
#include "buzzer.h"

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <sys/ioctl.h>
#include <stdio.h>

#include <unistd.h>
#include <cstdlib>

static int fb;
volatile int BUZZER=0;

buzzer::buzzer() {
    fb=open("/dev/buzzer_ctl",0);
    if(fb<0)
    {
        perror("open device buzzer failed!");
        exit(1);
    }
}
buzzer::~buzzer(){

}

void buzzer::BUZZER_Toggle()
{
    BUZZER=~BUZZER;
    if(BUZZER==0)
    {
        ioctl(fb,1,0);
    }
    else
    {
        ioctl(fb,0,0);
    }
}
