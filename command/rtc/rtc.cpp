#include "rtc.h"



rtc::rtc()
{

}

rtc::~rtc()
{
}

void rtc::getTime(){

    char buf[128];

    memset(buf,0,128);

    QDate d = QDate::currentDate();
    QTime t = QTime::currentTime();


    sprintf(buf,"date -s '%4d-%02d-%02d %02d:%02d:%02d'",
            d.year(),
            d.month(),
            d.day(),
            t.hour(),
            t.minute(),
            t.second());

    system(buf);
    system("hwclock -w");
}
