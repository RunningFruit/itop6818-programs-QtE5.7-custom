#ifndef MY_TIMER_H
#define MY_TIMER_H

#include <QObject>
#include <QDebug>
#include <QTimer>
#include <QTimerEvent>


class MyTimer : public QObject
{

public:
    MyTimer(QObject* parent = NULL);
    ~MyTimer();

public:
    void timer_open();
    void timer_close();

public slots:
    void handleTimeout();  //超时处理函数
private:
    QTimer *m_pTimer;
};


#endif // MY_TIMER_H
