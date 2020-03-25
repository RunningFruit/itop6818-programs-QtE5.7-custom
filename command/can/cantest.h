#ifndef CANTEST_H
#define CANTEST_H

#include <qsocketnotifier.h>



class cantest
{

public:
    explicit cantest();
    ~cantest();

private slots:
    void on_m_receive_destroyed();

    void sendMsg(QString text);
private:
    int openSerialPort();

private:
    QString m_receive="";
    int m_fd,fd2;
    QSocketNotifier *m_notifier;

};

#endif // CANTEST_H
