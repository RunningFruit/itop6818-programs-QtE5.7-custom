#include "tcp.h"
#include "ui_tcp.h"

tcp::tcp(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::tcp)
{
    ui->setupUi(this);
    isServer= true;     //默认服务端
    this->connect(ui->pushButton_StartServer,SIGNAL(clicked()),this,SLOT(slotStartServer()));
    this->connect(ui->pushButton_ConnectServer,SIGNAL(clicked()),this,SLOT(slotConnectServer()));
    this->connect(ui->pushButton_Send,SIGNAL(clicked()),this,SLOT(slotSendMesg()));
}


tcp::~tcp()
{
    delete ui;
}

void tcp::slotStartServer()  //启动服务器
{
    isServer = true;
    ui->pushButton_ConnectServer->setEnabled(false);
    ui->lineEdit_IP->setEnabled(false);
    ui->lineEdit_NetPort->setEnabled(false);
    m_pTcpServer = new QTcpServer();
    m_pTcpServer->listen(QHostAddress::Any,19999);
    this->connect(m_pTcpServer,SIGNAL(newConnection()),this,SLOT(slotNewConnect()));
}

void tcp::slotNewConnect()
{
//    QTcpSocket *pTcpSocket;
    pTcpSocketServer =  m_pTcpServer->nextPendingConnection();
//    pTcpSocketTemp = pTcpSocket;
//    int sockfd = pTcpSocketTemp->socketDescriptor();
//    map_TcpSocket.insert(make_pair(sockfd,pTcpSocket));
    this->connect(pTcpSocketServer,SIGNAL(readyRead()),this,SLOT(slotReadMesg()));
}

void tcp::slotReadMesg() //读取信息
{
//    int sockfd = pTcpSocketTemp->socketDescriptor();
    if(isServer == true)
    {
        QByteArray qba= pTcpSocketServer->readAll(); //读取

        QString ss=QVariant(qba).toString();
        QHostAddress ip = pTcpSocketServer->peerAddress();
        QString qStrSendInfo = ip.toString()+" : "+ss;
        ui->textEdit_Info->append(qStrSendInfo);

    }
    else if(isServer == false)
    {
        QByteArray qba= pTcpSocketClient->readAll(); //读取
        QString ss=QVariant(qba).toString();
        QHostAddress ip = pTcpSocketClient->peerAddress();
        QString qStrSendInfo = ip.toString()+" : "+ss;
        ui->textEdit_Info->append(qStrSendInfo);

    }
}

void tcp::slotConnectServer()    //连接服务器
{
    if(ui->lineEdit_IP->text().isEmpty() ||ui->lineEdit_NetPort->text().isEmpty())
    {
        QMessageBox::warning(this,tr("Warning"),tr("Please input IP OR NetPort!"));
        return;
    }

    isServer = false;
    ui->pushButton_StartServer->setEnabled(false);
    pTcpSocketClient = new QTcpSocket(this);
    pTcpSocketClient->abort();
    QString qStrIP = ui->lineEdit_IP->text();
    quint16 netport = ui->lineEdit_NetPort->text().toInt();
    pTcpSocketClient->connectToHost(qStrIP,netport);

    connect(pTcpSocketClient,SIGNAL(readyRead()),this,SLOT(slotReadMesg()));

}

void tcp::slotSendMesg() //发送消息
{
    QString strMesg= ui->lineEdit_sendmsg->text();
    ui->lineEdit_sendmsg->clear();
    if(isServer == true)
    {

         pTcpSocketServer->write(strMesg.toStdString().c_str(),strlen(strMesg.toStdString().c_str()));
    }

    else if(isServer == false)
    {
         pTcpSocketClient->write(strMesg.toStdString().c_str(),strlen(strMesg.toStdString().c_str()));
    }

}
