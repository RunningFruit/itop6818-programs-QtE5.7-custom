#include "tcpclient.h"


TcpClient::TcpClient(QObject* parent): QObject(parent)
{
    //建立connected()函数与startTransfer()函数的连结
    connect(&client, SIGNAL(connected()),this, SLOT(startTransfer()));
}

TcpClient::~TcpClient()
{
    //关闭客户端
    client.close();
}
void TcpClient::close()
{
    //关闭客户端
    client.close();
}

void TcpClient::open()
{
    //开始建立TCP连接，发送数据
    //本机环回通信
    start("127.0.0.1", 8888);
    //服务端/客户端通信，填入服务端IP地址与端口号
    //client.start("172.18.216.230", 8888);
}

void TcpClient::start(QString address, quint16 port)
{
    //显示状态
    cout<<"client begins to connect..."<<endl;
    //The QHostAddress class provides an IP address.
    //This class holds an IPv4 or IPv6 address in a platform- and protocol-independent manner.
    //创建QHostAddress类的对象
    QHostAddress addr(address);
    //跟服务端连接
    //Attempts to make a connection to hostName on the given port.
    client.connectToHost(addr, port);
}

void TcpClient::startTransfer()
{
    //qint64 QIODevice::write ( const char * data, qint64 maxSize )
    //Writes at most maxSize bytes of data from data to the device.
    //Returns the number of bytes that were actually written, or -1 if an error occurred.
    //写入数据到设备
    client.write("hello qt!", 9);
}

