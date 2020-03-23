#include "watchdog.h"


#include <unistd.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <linux/types.h>
#include <linux/watchdog.h>


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


    if(IS_KEEPALIVE)
        ::ioctl(fd,WDIOC_KEEPALIVE,&dummy);

    str.sprintf("%d",times);
}

void watchdog::on_pushButton_clicked()
{
    if(is_open_watchdog)
    {
        is_open_watchdog=false;
        IS_KEEPALIVE = true;

        fd = ::open("/dev/watchdog",O_WRONLY);
        if(fd < 0)
        {
            printf("error , open watchdog failure");
            exit(-1);
        }

        write(fd,(char *)&s,sizeof(s));

        times = 0;
        timer.start(1000,this);
    }
    else
    {
        is_open_watchdog = true;

        IS_KEEPALIVE = true;
        timer.stop();
        ::close(fd);
    }
}
