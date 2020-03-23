#include "tcp.h"

tcp::tcp()
{
    isServer= true;     //默认服务端
}

tcp::~tcp()
{
}

void tcp::slotStartServer()  //启动服务器
{
    isServer = true;

    m_pTcpServer = new QTcpServer();
    m_pTcpServer->listen(QHostAddress::Any,19999);
}

void tcp::slotNewConnect()
{
    pTcpSocketServer =  m_pTcpServer->nextPendingConnection();
}

void tcp::slotReadMesg() //读取信息
{
    if(isServer == true)
    {
        QByteArray qba= pTcpSocketServer->readAll(); //读取

        QString ss=QVariant(qba).toString();
        QHostAddress ip = pTcpSocketServer->peerAddress();
        QString qStrSendInfo = ip.toString()+" : "+ss;


        StrSendInfo+=qStrSendInfo;

    }
    else if(isServer == false)
    {
        QByteArray qba= pTcpSocketClient->readAll(); //读取
        QString ss=QVariant(qba).toString();
        QHostAddress ip = pTcpSocketClient->peerAddress();
        QString qStrSendInfo = ip.toString()+" : "+ss;

        StrSendInfo+=qStrSendInfo;
    }
}

void tcp::slotConnectServer()    //连接服务器
{
    if(IP.isEmpty() ||NetPort.isEmpty())
    {
        printf("Warning , Please input IP OR NetPort!");
        return;
    }

    isServer = false;


    pTcpSocketClient = new QTcpSocket(this);

    pTcpSocketClient->abort();
    QString qStrIP = IP;
    quint16 netport = NetPort.toInt();
    pTcpSocketClient->connectToHost(qStrIP,netport);

}

void tcp::slotSendMesg() //发送消息
{
    QString strMesg= sendmsg;
    sendmsg="";
    if(isServer == true)
    {
        pTcpSocketServer->write(strMesg.toStdString().c_str(),strlen(strMesg.toStdString().c_str()));
    }

    else if(isServer == false)
    {
        pTcpSocketClient->write(strMesg.toStdString().c_str(),strlen(strMesg.toStdString().c_str()));
    }

}
