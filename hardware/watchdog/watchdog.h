#ifndef WATCHDOG_H
#define WATCHDOG_H

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

private:
    void on_pushButton_clicked();

private:
    bool IS_KEEPALIVE=false;
    bool is_open_watchdog;
    int times;
    QBasicTimer timer;
    int fd;
    char s;
};

#endif // WATCHDOG_H
