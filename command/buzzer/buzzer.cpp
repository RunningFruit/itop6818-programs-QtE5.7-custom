
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

}
buzzer::~buzzer(){

}

void buzzer::buzzer_open(){
    fb=open("/dev/buzzer_ctl",0);
    if(fb<0)
    {
        perror("open device buzzer failed!");
//        exit(1);
    }
}

void buzzer::buzzer_toggle()
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

void buzzer::buzzer_close()
{
    close(fb);
}
