#ifndef MY_RTC_H
#define MY_RTC_H

#include <QBasicTimer>
#include <QTimerEvent>
#include <QObject>

#include <QDate>
#include <QTime>
#include <stdio.h>

class rtc:public QObject
{
public:
    explicit rtc();
    ~rtc();
public:
    void getTime();

};

#endif // MY_RTC_H
