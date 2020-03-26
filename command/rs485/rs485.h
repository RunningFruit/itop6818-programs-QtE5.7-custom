#ifndef MY_RS485_H
#define MY_RS485_H

#include <qsocketnotifier.h>
#include <QObject>


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
