#ifndef NETWORKTCP_H
#define NETWORKTCP_H

#include <QMainWindow>
#include <QtNetwork/QTcpServer>
#include <QtNetwork/QTcpSocket>
#include <map>
#include <iostream>
#include <QMessageBox>
using namespace std;

namespace Ui {
    class NetworkTcp;
}

class NetworkTcp : public QMainWindow
{
    Q_OBJECT

public:
    explicit NetworkTcp(QWidget *parent = 0);
    ~NetworkTcp();

    QTcpServer *m_pTcpServer;
    QTcpSocket *m_pTcpSocket;
    map<int,QTcpSocket*> map_TcpSocket;

       QTcpSocket *pTcpSocketServer;
       QTcpSocket *pTcpSocketClient;

    bool isServer;

private:
    Ui::NetworkTcp *ui;

private slots:
    void slotStartServer();
    void slotConnectServer();
    void slotSendMesg();
    void slotNewConnect();
    void slotReadMesg();
};

#endif // NETWORKTCP_H
