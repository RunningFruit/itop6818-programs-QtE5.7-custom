#ifndef NETWORKTCP_H
#define NETWORKTCP_H


#include <QtNetwork/QTcpServer>
#include <QtNetwork/QTcpSocket>
#include <map>
#include <iostream>

using namespace std;


class tcp:public QObject
{

public:
    explicit tcp();
    ~tcp();

    QTcpServer *m_pTcpServer;
    QTcpSocket *m_pTcpSocket;
    map<int,QTcpSocket*> map_TcpSocket;

    QTcpSocket *pTcpSocketServer;
    QTcpSocket *pTcpSocketClient;

    bool isServer;

    QString IP;
    QString NetPort;
    QString StrSendInfo;
    QString sendmsg;

private :
    void slotStartServer();
    void slotConnectServer();
    void slotSendMesg();
    void slotNewConnect();
    void slotReadMesg();
};

#endif // NETWORKTCP_H
