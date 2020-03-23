#ifndef RTC_H
#define RTC_H

#include <QMainWindow>
#include <QBasicTimer>
#include <QTimerEvent>



class rtc
{
public:
    explicit rtc();
    ~rtc();
protected:
    void close();

};

#endif // RTC_H
