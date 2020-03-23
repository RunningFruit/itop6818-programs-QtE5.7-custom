#include "datareceive.h"



DataReceive::DataReceive(QObject *parent):QObject(parent)
{
    int hosid;
    if(-1==(hosid=gethostid()))
    {
        qDebug()<<"gethostid err\n";
        //        exit(0);
    }
    //    qDebug()<<"hosid is :"<<hosid<<"\n";

    m_connect_url = QString("%1%2%3")
            .arg(URL_WEBSOCKET)
            .arg("/itop6818-")
            .arg(hosid);

    printf("connect_url is :%s\n",m_connect_url.toStdString().data());

    postUtil = new HttpPostUtil();
    downfileUtil = new HttpDownFileUtil();
    jsonUtil = new JsonUtil();

    light = new led();
    buz = new buzzer();
    rlay = new relay();
    m_rtc = new rtc();
    m_watchdog = new watchdog();
    m_rc522 = new rc522();
    m_uart = new uart();
    m_rs485 = new rs485();
    m_3timer = new MyTimer();

    dataRecvWS = Q_NULLPTR;
    connectStatus = false;
    m_timer = new QTimer();
}

DataReceive::~DataReceive(){

}

/**
 * @breaf 创建WebSocket连接
 */
void DataReceive::createDataRecvWS(){


    if(dataRecvWS == Q_NULLPTR){
        dataRecvWS = new QWebSocket();
        qDebug()<<"create websocket!";
        connect(dataRecvWS, &QWebSocket::disconnected, this, &DataReceive::onDisConnected, Qt::AutoConnection);
        connect(dataRecvWS, &QWebSocket::textMessageReceived, this, &DataReceive::onTextReceived, Qt::AutoConnection);
        connect(dataRecvWS, &QWebSocket::connected, this, &DataReceive::onConnected, Qt::AutoConnection);
        connect(m_timer, &QTimer::timeout, this, &DataReceive::reconnect, Qt::AutoConnection);

        dataRecvWS->open(QUrl(m_connect_url));
    }
}

/**
 * @breaf 判断连接状态
 * @note  当连接成功后，触发该函数
 */
void DataReceive::onConnected(){
    qDebug()<<"DataReveive websocket is already connect!";
    connectStatus = true;
    m_timer->stop();
    qDebug()<<"Address："<<dataRecvWS->peerAddress();


    QJsonObject obj;
    obj.insert("msg","hello");

    QString postUrl = QString(URL_HTTP).append("/device").append("/sayHello");
    postUtil->post(postUrl,jsonUtil->jsonToString(obj));

    downfileUtil->downloadFromUrl("https://timgsa.baidu.com/timg?image&quality=80&size=b9999_10000&sec=1584984114727&di=0d0f5e988b4da68d49eb4bd1dbdb0a52&imgtype=0&src=http%3A%2F%2Fatt.xmnn.cn%2Fbbs%2Fforum%2F201310%2F08%2F120516oqdxu9iliugmqsgm.jpg");

}

/**
 * @breaf 数据处理函数
 * @param msg，数据信息
 * @note  当收到服务端发送的数据时，触发该函数
 */
void DataReceive::onTextReceived(QString msg){
    qDebug()<<"----------------data-----------------";
    qDebug()<<msg;


    QJsonObject obj = jsonUtil->stringToJson(msg);

    if(obj.contains("device") ){
        QString device = obj["device"].toString();
        QString cmd = obj["cmd"].toString();

        deviceCmd(device,cmd);
    }else{
        qDebug()<<"error";
    }
}


//
void DataReceive::deviceCmd(QString device,QString cmd){
    if(device == "led"){

        if(cmd == "on"){
            light->led_open();
        }else if(cmd == "off"){
            light->led_toggle();
        }else if(cmd == "close"){
            light->led_close();
        }else{
            light->led_close();
        }

    }else if(device == "buzzer"){
        if(cmd == "on"){
            buz->buzzer_open();
        }else if(cmd == "off"){
            buz->buzzer_toggle();
        }else if(cmd == "close"){
            buz->buzzer_close();
        }else{
            buz->buzzer_close();
        }
    }
    else if(device == "relay"){
        if(cmd == "on"){
            rlay->relay_open();
        }else if(cmd == "off"){
            rlay->relay_toggle();
        }else if(cmd == "close"){
            rlay->relay_close();
        }else{
            rlay->relay_close();
        }
    }
    else if(device == "rtc"){
        if(cmd == "on"){
            m_rtc->getTime();
        }
    }
    else if(device == "watchdog"){
        if(cmd == "on"){
            m_watchdog->keep_feeding();
        }else{
            m_watchdog->stop_feeding();
        }
    }
    else if(device == "rc522"){
        /*
        if(cmd == "write"){
            m_rc522->write();
        }else  if(cmd == "read"){
            m_rc522->read();
        }
        */
    }
    else if(device == "uart"){
        if(cmd == "on"){
            m_uart->uart_open();
            m_uart->uart_send_msg("hello,uart");
        }else if(cmd == "off"){
            m_uart->uart_close();
        }
    }  else if(device == "rs485"){
        if(cmd == "on"){
            m_rs485->openSerialPort();
            m_rs485->sendMsg("hello,uart");
        }else if(cmd == "off"){
            m_rs485->close();
        }
    }else if(device == "timer"){
        if(cmd == "on"){
            m_3timer->timerStart();
        }else{
            m_3timer->timerClose();
        }
    }
    qDebug()<<cmd;
}

/**
 * @breaf 连接断开
 * @note  当连接断开时，触发该函数
 */
void DataReceive::onDisConnected(){
    qDebug()<<"DataReceive websocket is disconnected!!!";
    connectStatus = false;
    m_timer->start(3000);/*-<当连接失败时，触发重连计时器，设置计数周期为3秒 */
}

/**
 * @breaf 周期重连函数
 * @note  连接建立成功时，调用该函数
 */
void DataReceive::reconnect(){

    qDebug()<<m_connect_url;

    qDebug()<<"try to reconnect!";
    dataRecvWS->abort();
    dataRecvWS->open(QUrl(m_connect_url));

}
