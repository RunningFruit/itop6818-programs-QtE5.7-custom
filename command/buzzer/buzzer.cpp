
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
        exit(1);
    }


    int BuzzerOnOffTimes=3;

    while(BuzzerOnOffTimes--)
    {
        printf("ioctl buzzer %d times\n",BuzzerOnOffTimes);
        ioctl(fb,1,0);	//parameter 2 is cmd ,cmd = 1 buzzer on
        sleep(1);
        ioctl(fb,0,0);
        sleep(1);
    }
}


void buzzer::buzzer_close()
{
    ioctl(fb,0,0);
    sleep(1);
    close(fb);
}
