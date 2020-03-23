#ifndef TIMER_EVENT_H
#define TIMER_EVENT_H

#include <QTimerEvent>
#include <QObject>

class timerevent: public QObject
{

public:
    explicit timerevent();
    ~timerevent();
protected:
    void timerEvent(QTimerEvent *event);
public:
    int startTimer(int time);
private:
    void timerUpdate();
private:
    int id1,id2,id3;

};

#endif // TIMER_EVENT_H
