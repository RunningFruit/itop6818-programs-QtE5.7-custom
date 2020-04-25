#ifndef TCPCLIENT_H
#define TCPCLIENT_H


#include <QtNetwork>
#include <QObject>
#include <QString>
#include <QTcpSocket>
#include <QHostAddress>
#include <iostream>
using namespace std;


class TcpClient: public QObject
{
    Q_OBJECT
public:
    TcpClient(QObject* parent = 0);
    ~TcpClient();
    void start(QString address, quint16 port);

public:
    void open();
    void close();

public slots:
    void startTransfer();

private:
    QTcpSocket client;

};

#endif // TCPCLIENT_H
