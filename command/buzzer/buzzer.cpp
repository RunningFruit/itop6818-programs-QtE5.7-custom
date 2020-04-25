
#include "buzzer.h"


static int fb;
volatile int BUZZER=0;

buzzer::buzzer() {

}
buzzer::~buzzer(){

}

void buzzer::buzzer_open(){

    qDebug()<<("try to open buzzer ...")<<endl;

    fb=open("/dev/buzzer_ctl",0);
    if(fb<0)
    {
        //perror("open device buzzer failed!");
        qDebug()<<"open buzzer failed!"<<endl;
        exit(1);
    }
    qDebug()<< ("open buzzer ok")<<endl;

    BUZZER = 1;
    int BuzzerOnOffTimes=3;

    while(BuzzerOnOffTimes--)
    {
        if(!BUZZER){
            buzzer_close();
            break;
        }
        qDebug()<<"ioctl buzzer "<<BuzzerOnOffTimes<<" times"<<endl;
        ioctl(fb,1,0);	//parameter 2 is cmd ,cmd = 1 buzzer on
        sleep(1);
        ioctl(fb,0,0);
        sleep(1);
    }
}


void buzzer::buzzer_close()
{
    BUZZER=0;
    qDebug()<<"try to close buzzer ..."<<endl;
    ioctl(fb,0,0);
    sleep(1);
    close(fb);
    qDebug()<<"buzzer closed"<<endl;
}
