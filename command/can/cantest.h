#ifndef MY_CANTEST_H
#define MY_CANTEST_H

#include <qsocketnotifier.h>
#include <QObject>
#include <QDebug>
#include <qtimer.h>

#include <qstringlist.h>
#include <iostream>
#include <stdio.h>
#include <string>
#include <unistd.h>
#include <stdlib.h>
#include <net/if.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <linux/can.h>
#include <linux/can/raw.h>

#include <sys/types.h>
#include <sys/stat.h>

#include <linux/fs.h>
#include <errno.h>

#include <termio.h>
#include <ctype.h>



class cantest:public QObject
{

public:
    explicit cantest();
    ~cantest();

private slots:
    void remoteDataIncoming();

public:
    void openSerialPort();
    void sendMsg(QString text);
    void close();

private:
    QString m_receive="";
    int m_fd;
    QSocketNotifier *m_notifier;

};

#endif // MY_CANTEST_H
