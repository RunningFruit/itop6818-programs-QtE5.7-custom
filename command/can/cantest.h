#ifndef MY_CANTEST_H
#define MY_CANTEST_H

#include <qsocketnotifier.h>
#include <QObject>



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
    int m_fd,fd2;
    QSocketNotifier *m_notifier;

};

#endif // MY_CANTEST_H
