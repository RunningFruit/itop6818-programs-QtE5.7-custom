#ifndef MY_RS485_H
#define MY_RS485_H

#include <qsocketnotifier.h>


class rs485
{
public:
    explicit rs485();
    ~rs485();

public:
    void openSerialPort();
    void sendMsg( QString text);
    void close();
    //QString unicodeToString(QString str);
    //QString stringToUnicode(QString str);

private:   
    void remoteDataIncoming();

private:
    int m_fd,fd2;
    QSocketNotifier *m_notifier;

};

#endif // MY_RS485_H
