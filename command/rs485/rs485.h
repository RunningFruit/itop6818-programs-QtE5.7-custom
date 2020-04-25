#ifndef MY_RS485_H
#define MY_RS485_H

#include <qsocketnotifier.h>
#include <QObject>
#include <QDebug>

#include <qtimer.h>
#include <qstringlist.h>

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <linux/fs.h>
#include <errno.h>
#include <string.h>
#include <termio.h>
#include <unistd.h>
#include <cstdlib>

class rs485 : QObject
{
public:
    explicit rs485();
    ~rs485();

public:
    void openSerialPort();
    void sendMsg( QString text);
    void close();


private:   
    void remoteDataIncoming();

private:
    int m_fd,fd2;
    QSocketNotifier *m_notifier;

};

#endif // MY_RS485_H
