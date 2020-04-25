#ifndef MY_TCPSERVER_H
#define MY_TCPSERVER_H

#include <QtNetwork>
#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>

class TcpServer: public QObject
{
Q_OBJECT
public:
    TcpServer(QObject * parent = 0);
    ~TcpServer();
    void open();
    void close();

public slots:
    void acceptConnection();
    void startRead();

private:
    QTcpServer server;
    QTcpSocket* client;
};

#endif // MY_TCPSERVER_H
