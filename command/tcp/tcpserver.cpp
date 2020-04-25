#include "tcpserver.h"
#include <QHostAddress>
#include <iostream>

using namespace std;

TcpServer::TcpServer(QObject* parent): QObject(parent)
{
}

TcpServer::~TcpServer()
{
    cout<<"closing..."<<endl;
    //关闭服务器
    server.close();
}
void TcpServer::close(){
    cout<<"closing..."<<endl;
    //关闭服务器
    server.close();
}

void TcpServer::open()
{
    //将newConnection()与acceptConnection()连结
    connect(&server, SIGNAL(newConnection()),this,SLOT(acceptConnection()));
    cout<<"listening..."<<endl;

    //在服务端IP地址172.18.218.2的端口8888监听
    //QHostAddress addr("172.18.218.2");
    //server.listen(addr, 8888);

    //在任意网络接口监听8888
    server.listen(QHostAddress::Any,8888);

    cout<<"listen..."<<endl;
    //显示状态
    cout<<"try to connect..."<<endl;
}


void TcpServer::acceptConnection()
{
    //返回等待的连接
    cout<<"connecting..."<<endl;
    client = server.nextPendingConnection();
    //将readyRead()与startRead()连结
    connect(client, SIGNAL(readyRead()),this, SLOT(startRead()));
}

void TcpServer::startRead()
{
    char buffer[1024] = {0};
    //读入数据
    cout<<"reading..."<<endl;
    client->read(buffer, client->bytesAvailable());
    cout<<"outputing..."<<endl;
    //显示数据
    cout << buffer << endl;
    //关闭客户端
    client->close();
}


