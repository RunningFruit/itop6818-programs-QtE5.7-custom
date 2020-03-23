#ifndef RTC_H
#define RTC_H

#include <QBasicTimer>
#include <QTimerEvent>
#include <QObject>


class rtc:public QObject
{
public:
    explicit rtc();
    ~rtc();
protected:
    void close();

};

#endif // RTC_H
