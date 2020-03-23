#include "rtc.h"

#include <QDate>
#include <QTime>
#include <stdio.h>

rtc::rtc()
{

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

rtc::~rtc()
{
}
void rtc::close()
{
    exit(0);
}
