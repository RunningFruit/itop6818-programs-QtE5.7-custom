#ifndef MY_TIMER_H
#define MY_TIMER_H

#include <QTimerEvent>
#include <QObject>

class MyTimer: public QObject
{

public:
    explicit MyTimer();
    ~MyTimer();
protected:
    virtual void timerEvent(QTimerEvent *event);

private slots:
    void timerUpdate();
    void timerClose();
private:
    int id1,id2,id3;

};

#endif // MY_TIMER_H
