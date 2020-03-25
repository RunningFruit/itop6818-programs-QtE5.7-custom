#ifndef MY_WATCHDOG_H
#define MY_WATCHDOG_H

#include <QBasicTimer>
#include <QTimerEvent>
#include <QObject>

class watchdog:public QObject
{
    
public:
    explicit watchdog();
    ~watchdog();
    
protected:
    void timerEvent(QTimerEvent *);

public:
    void keep_feeding();
    void stop_feeding();

private:
    bool is_keep_feeding=false;
    int times;
    QBasicTimer timer;
    int fd;
    char s;
};

#endif // MY_WATCHDOG_H
