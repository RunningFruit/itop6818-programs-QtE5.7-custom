#include "watchdog.h"


watchdog::watchdog()
{
    fd = 0;
    times = 0;
    s='V';
}

watchdog::~watchdog()
{
    ::close(fd);
    qDebug()<<("watchdog deleted")<<endl;
}

void watchdog::timerEvent(QTimerEvent *)
{
    int dummy;
    QString str;

    times++;

    if(is_keep_feeding)
        ::ioctl(fd,WDIOC_KEEPALIVE,&dummy);

    str.sprintf("%d",times);

    qDebug()<<("times:")<<times<<endl;
}

void watchdog::keep_feeding()
{
    qDebug()<<("try to open watchdog ...")<<endl;

    fd = ::open("/dev/watchdog",O_WRONLY);
    if(fd < 0)
    {
        qDebug()<<("error, open watchdog failure");
        //exit(-1);
        return;
    }
    qDebug()<<("open watchdog ok")<<endl;

    write(fd,(char *)&s,sizeof(s));
    is_keep_feeding = true;
    qDebug()<<("Keep feeding the watchdog, system will not restart.")<<endl;

    times = 0;
    timer.start(1000,this);
}

void watchdog::stop_feeding(){
    qDebug()<<("try to stop feeding ...")<<endl;

    is_keep_feeding = false;
    qDebug()<<("System will restart in 1 minute without feed dog.")<<endl;

    timer.stop();
    ::close(fd);

    qDebug()<<("stop feeding end")<<endl;
}
