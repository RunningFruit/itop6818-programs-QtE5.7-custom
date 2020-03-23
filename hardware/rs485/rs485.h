#ifndef RS485_H
#define RS485_H

#include <qsocketnotifier.h>


class rs485
{
public:
    explicit rs485();
    ~rs485();

private:
    int openSerialPort();
    QString unicodeToString(QString str);
    QString stringToUnicode(QString str);

private:
    void sendMsg( QString text);
    void remoteDataIncoming();

private:
    int m_fd,fd2;
    QSocketNotifier *m_notifier;

};

#endif // RS485_H
