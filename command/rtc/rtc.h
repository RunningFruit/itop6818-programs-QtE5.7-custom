#ifndef MY_RTC_H
#define MY_RTC_H

#include <QBasicTimer>
#include <QTimerEvent>
#include <QObject>


class rtc:public QObject
{
public:
    explicit rtc();
    ~rtc();
public:
    void getTime();

};

#endif // MY_RTC_H
