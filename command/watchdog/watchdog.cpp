#include "watchdog.h"


#include <unistd.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <linux/types.h>
#include <linux/watchdog.h>
#include <QDebug>


watchdog::watchdog()
{
    fd = 0;
    times = 0;
    s='V';
}

watchdog::~watchdog()
{
    ::close(fd);
}

void watchdog::timerEvent(QTimerEvent *)
{
    int dummy;
    QString str;

    times++;

    if(is_keep_feeding)
        ::ioctl(fd,WDIOC_KEEPALIVE,&dummy);

    str.sprintf("%d",times);
}

void watchdog::keep_feeding()
{

    fd = ::open("/dev/watchdog",O_WRONLY);
    if(fd < 0)
    {
        qDebug()<<("error , open watchdog failure");
        //exit(-1);
        return;
    }

    write(fd,(char *)&s,sizeof(s));

    is_keep_feeding = true;
    times = 0;
    timer.start(1000,this);
}

void watchdog::stop_feeding(){
    is_keep_feeding = false;
    timer.stop();
    ::close(fd);
}
