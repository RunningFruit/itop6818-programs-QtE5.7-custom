#include "datareceive.h"


DataReceive::DataReceive(QObject *parent):QObject(parent)
{

    uuid = getUUID();
    m_connect_url = QString("%1%2%3")
            .arg(URL_WEBSOCKET)
            .arg("/itop6818-")
            .arg(uuid);


    qDebug()<<("websocket path:");
    qDebug()<<m_connect_url<<endl;

    postUtil = new HttpPostUtil();
    downfileUtil = new HttpDownFileUtil();
    jsonUtil = new JsonUtil();

    m_led = new led();
    m_buzzer = new buzzer();
    m_relay = new relay();
    m_rtc = new rtc();
    m_watchdog = new watchdog();
    m_rc522 = new rc522();
    m_uart = new uart();
    m_rs485 = new rs485();
    m_3timer = new MyTimer();
    m_can = new cantest();
    //m_imgcompare = new imgcompare();

    m_tcpserver = new TcpServer();
    m_tcpclient = new TcpClient();


    dataRecvWS = Q_NULLPTR;
    connectStatus = false;
    m_timer = new QTimer();
}

DataReceive::~DataReceive(){

}

QString DataReceive::getUUID(){

    try
    {
        const int N = 100;
        int ret = 0;
        FILE *fp;
        char buf[N];
        buf[N-1]='\0';

        if((fp = fopen("/sys/devices/platform/cpu/uuid", "rt"))==NULL){
            //perror("fopen");
            qDebug()<<"/sys/devices/platform/cpu/uuid 文件不存在"<<endl;
            return QString("").toStdString().data();

        }
        if(ret = fread( buf, 1, sizeof(buf), fp)<0){
            //perror("fread");
            qDebug()<<"读取不到 cpu uuid"<<endl;
            return QString("").toStdString().data();
        }
        fclose(fp);

        qDebug()<<("cpu uuid :");
        QString uuid = QString(QLatin1String(buf)).toStdString().data();
        int endIndex = uuid.lastIndexOf("\n");
        uuid = uuid.mid(0, endIndex);
        qDebug()<<uuid<<endl;

        return uuid;
    }
    catch (exception& e)
    {
        qDebug()<<"cat uuid fail";
        return QString("").toStdString().data();
    }
}
/**
 * @breaf 创建WebSocket连接
 */
void DataReceive::createDataRecvWS(){


    if(dataRecvWS == Q_NULLPTR){
        dataRecvWS = new QWebSocket();
        qDebug()<<"create websocket!"<<endl;
        connect(dataRecvWS, &QWebSocket::disconnected, this, &DataReceive::onDisConnected, Qt::AutoConnection);
        connect(dataRecvWS, &QWebSocket::textMessageReceived, this, &DataReceive::onTextReceived, Qt::AutoConnection);
        connect(dataRecvWS, &QWebSocket::connected, this, &DataReceive::onConnected, Qt::AutoConnection);
        connect(m_timer, &QTimer::timeout, this, &DataReceive::reconnect, Qt::AutoConnection);

        qDebug()<<"dataRecvWS->open "<<m_connect_url<<endl;
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


    //postBaseMsg();

    //downfileUtil->downloadFromUrl("https://timgsa.baidu.com/timg?image&quality=80&size=b9999_10000&sec=1584984114727&di=0d0f5e988b4da68d49eb4bd1dbdb0a52&imgtype=0&src=http%3A%2F%2Fatt.xmnn.cn%2Fbbs%2Fforum%2F201310%2F08%2F120516oqdxu9iliugmqsgm.jpg");
}

/**
 * @breaf 判断连接状态
 * @note  当连接成功后，触发该函数
 */
void DataReceive::postBaseMsg(){

    //    QJsonObject obj;
    //    obj.insert("msg","hello");
    //    QString postUrl = QString(URL_HTTP).append("/device").append("/sayHello");

    QJsonObject obj;
    obj.insert("ip",dataRecvWS->peerAddress().toString());
    obj.insert("mac",uuid);
    obj.insert("longitude","1");
    obj.insert("latitude","2");
    obj.insert("location","3");
    QString postUrl = QString(IP_HTTP).append("/mainControl");
    postUtil->post(postUrl,jsonUtil->jsonToString(obj));
    qDebug()<<"发送post请求:";
    qDebug()<<obj;
    qDebug()<<postUrl<<endl;
}

/**
 * @breaf 数据处理函数
 * @param msg，数据信息
 * @note  当收到服务端发送的数据时，触发该函数
 */
void DataReceive::onTextReceived(QString msg){
    qDebug()<<"---------------- onTextReceived -----------------";
    qDebug()<<msg;
    qDebug()<<"---------------- onTextReceived -----------------"<<endl;

    QJsonObject obj = jsonUtil->stringToJson(msg);

    if(obj.contains("device") ){
        QString device = obj["device"].toString();
        QString cmd = obj["cmd"].toString();

        QString msg="";
        if(obj.contains("msg")){
            msg = obj["msg"].toString();
        }
        deviceCmd(device,cmd,msg);
    }else{
        //qDebug()<<obj<<endl;
    }
}


//
void DataReceive::deviceCmd(QString device,QString cmd,QString msg){
    if(device == "led"){

        if(cmd == "on"){
            m_led->led_open();
        }else if(cmd == "off"){
            m_led->led_close();
        }else {
            m_led->led_close();
        }

    }else if(device == "buzzer"){
        if(cmd == "on"){
            m_buzzer->buzzer_open();
        }else if(cmd == "off"){
            m_buzzer->buzzer_close();
        }else{
            m_buzzer->buzzer_close();
        }
    }
    else if(device == "relay"){
        if(cmd == "on"){
            m_relay->relay_open();
        }else{
            m_relay->relay_close();
        }
    }

    else if(device == "watchdog"){
        if(cmd == "on"){
            m_watchdog->keep_feeding();
        }else if(cmd == "feed"){
            m_watchdog->keep_feeding();
        }else{
            m_watchdog->stop_feeding();
        }
    }
    else if(device == "rc522"){
        if(cmd == "open"){
            m_rc522->open();
        }else {
            m_rc522->close();
        }
    }
    else if(device == "uart"){
        if(cmd == "on"){
            m_uart->uart_open();
            m_uart->uart_send_msg(msg);
        }else if(cmd == "off"){
            m_uart->uart_close();
        }
    }  else if(device == "rs485"){
        if(cmd == "on"){
            m_rs485->openSerialPort();
            m_rs485->sendMsg(msg);
        }else if(cmd == "off"){
            m_rs485->close();
        }
    }else if(device == "timer"){
        if(cmd == "on"){
            m_3timer->timer_open();
        }else{
            m_3timer->timer_close();
        }
    }else if(device == "rtc"){
        if(cmd == "on"){
            m_rtc->getTime();
        }
    }else if(device == "shell"){
        if(cmd == "on"){
            m_shell->cmd(msg);
        }
    }else if(device == "can"){
        if(cmd == "on"){
            m_can->openSerialPort();
            m_can->sendMsg(msg);
        }else if(cmd == "off"){
            m_can->close();
        }
    }else if(device == "gps"){
        if(cmd == "on"){
            m_gps->open_device();
        }else{
            m_gps->close_device();
        }
    }else if(device == "tcpserver"){
        if(cmd == "on"){
            m_tcpserver->open();
        }else{
            m_tcpserver->close();
        }
    } else if(device == "tcpclient"){
        if(cmd == "on"){
            m_tcpclient->open();
        }else{
            m_tcpclient->close();
        }
    } else if(device == "opencv"){
        //if(cmd == "on"){
        //    m_imgcompare->compareImg("","");
        //}else if(cmd == "off"){
        //}else{
        //}
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
    qDebug()<<m_connect_url;
    dataRecvWS->abort();
    dataRecvWS->open(QUrl(m_connect_url));

}
