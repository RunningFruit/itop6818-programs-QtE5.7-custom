#include "MyTimer.h"

#define TIMER_TIMEOUT	(5*1000)

MyTimer::MyTimer(QObject *parent)
    :QObject(parent)
{

}

MyTimer::~MyTimer()
{
    if(m_pTimer->isActive()){
        m_pTimer->stop();
    }
}
void MyTimer::timer_close()
{
    if(m_pTimer->isActive()){
        m_pTimer->stop();
    }
}

void MyTimer::timer_open()
{
    m_pTimer = new QTimer(this);
    connect(m_pTimer, SIGNAL(timeout()), this, SLOT(handleTimeout()));
    m_pTimer->start(TIMER_TIMEOUT);
}


void MyTimer::handleTimeout()
{
    qDebug()<<"Enter timeout processing function"<<endl;
}
