#ifndef MY_UART_H
#define MY_UART_H


#include <qsocketnotifier.h>
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

class uart : public QObject
{

public:
    explicit uart();
    ~uart();

public:
    void uart_open();
    void uart_send_msg(QString msg);
    void uart_close();

//private:
//    QString unicodeToString(QString str);
//    QString stringToUnicode(QString str);

private slots:
    void remoteDataIncoming();

private:
    QString m_receive;
    int m_fd;
    QSocketNotifier *m_notifier;

};

#endif // MY_UART_H
