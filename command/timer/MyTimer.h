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

public:
    void timerStart();

public slots:
    void timerClose();

private slots:
    void timerUpdate();

private:
    int id1,id2,id3;

};

#endif // MY_TIMER_H
