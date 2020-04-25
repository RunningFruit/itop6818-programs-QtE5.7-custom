#include "cantest.h"



cantest::cantest(){

}

cantest::~cantest()
{
    if (m_notifier) {
        delete m_notifier;
        m_notifier = 0;
    }

    if (m_fd >= 0) {
        ::close(m_fd);
        m_fd = -1;
    }
}

void cantest::openSerialPort()
{
    int s;
    struct sockaddr_can addr;
    struct ifreq ifr;

    if ((s = socket(PF_CAN, SOCK_RAW, CAN_RAW)) < 0)
    {
//        perror("Create socket failed");
        qDebug()<<"can 创建socket失败!";
        exit(-3);
    }

    /* set up can interface */
    strcpy(ifr.ifr_name, "can0");
    //qDebug()<<("can port is %s\n",ifr.ifr_name);
    /* assign can device */
    ioctl(s, SIOCGIFINDEX, &ifr);
    addr.can_family = AF_CAN;
    addr.can_ifindex = ifr.ifr_ifindex;
    /* bind can device */
    if(bind(s, (struct sockaddr *)&addr, sizeof(addr)) < 0)
    {
        //perror("Bind can device failed\n");
        qDebug()<<"绑定 can 设备失败!";
        exit(-2);
    }


    m_fd=s;

    if (m_fd < 0) {
//        qDebug()<<"Error"<<"Fail to open serial port!";
        qDebug()<<"can 打开串口失败!";
        return ;
    }

    qDebug()<<"can created!"<<endl;

    m_notifier = new QSocketNotifier(m_fd, QSocketNotifier::Read, this);
    connect (m_notifier, SIGNAL(activated(int)), this, SLOT(remoteDataIncoming()));
}

void cantest::close(){
    qDebug()<<"尝试关闭can!"<<endl;
    if (m_notifier) {
        delete m_notifier;
        m_notifier = 0;
    }

    if (m_fd >= 0) {
        ::close(m_fd);
        m_fd = -1;
    }
}


struct can_frame frame;
void cantest::remoteDataIncoming()
{
    int i;
    struct can_filter rfilter[1];
    /* set filter for only receiving packet with can id 0x1F */
    rfilter[0].can_id = 0x1F;
    rfilter[0].can_mask = CAN_SFF_MASK;
    if(setsockopt(m_fd, SOL_CAN_RAW, CAN_RAW_FILTER, &rfilter, sizeof(rfilter)) < 0)
    {
        //perror("set receiving filter error\n");
        qDebug()<< ("设置接收滤波器错误")<<endl;
        exit(-3);
    }
    /* keep reading */

    if(read(m_fd, &frame, sizeof(frame)) <= 0 ){
        perror("read");
        qDebug()<<("Error")<<("Receive error!")<<endl;
        return;
    }

    for(i=0;i<8;i++){
        if(frame.data[i]!=NULL){
            m_receive.append(frame.data[i]);
        }
    }

    qDebug()<< (frame.data)<<endl;
    qDebug()<< ("can 接收")<<endl;

}



void cantest::sendMsg(QString text)
{
    int i,j;
    //unsigned char *c;
    //struct can_filter rfilter[1];
    /* configure can_id and can data length */
    frame.can_id = 0x1F;
    frame.can_dlc = 8;
    qDebug()<<("can 发送")<<endl;

    if (text.isEmpty()) {
        return ;
    }
    for(j=0;j<text.length(); ){
        memset(frame.data,0,sizeof(frame.data));
        for(i=0;i<8;i++){

            frame.data[i] = ((text.data()+j))->unicode();
            if(frame.data[i]!=NULL){
                j++;
            }
            else
                break;
        }
        write(m_fd,&frame,sizeof(frame));
        qDebug()<< (frame.data)<<endl;
    }

}

