#include "uart.h"



uart::uart()
{

}


void uart::uart_close(){
    qDebug()<<( "try close uart ...")<<endl;
    if (m_notifier) {
        delete m_notifier;
        m_notifier = 0;
    }

    if (m_fd >= 0) {
        ::close(m_fd);
        m_fd = -1;
    }
    qDebug()<<( "uart closed ")<<endl;
}

uart::~uart()
{
    qDebug()<<( "try delete uart ...")<<endl;
    if (m_notifier) {
        delete m_notifier;
        m_notifier = 0;
    }

    if (m_fd >= 0) {
        ::close(m_fd);
        m_fd = -1;
    }

    qDebug()<<( "uart deleted ")<<endl;
}

void uart::uart_open()
{
    qDebug()<<("try open serial port on /dev/ttySAC1 ...")<<endl;

    int fd = -1;
    const char *devName = "/dev/ttySAC1";
    fd = ::open(devName, O_RDWR|O_NONBLOCK);
    if (fd < 0) {
        fd = -1;
    }
    termios serialAttr;
    memset(&serialAttr, 0, sizeof serialAttr);
    serialAttr.c_iflag = IGNPAR;
    serialAttr.c_cflag = B115200 | HUPCL | CS8 | CREAD | CLOCAL;
    serialAttr.c_cc[VMIN] = 1;
    if (tcsetattr(fd, TCSANOW, &serialAttr) != 0) {
        fd = -1;
    }

    m_fd = fd;

    if (m_fd < 0) {
        qDebug()<<("Error,Fail to open serial port!");
        return ;
    }
    qDebug()<<("open serial port on /dev/ttySAC1 ok!")<<endl;

    m_notifier = new QSocketNotifier(m_fd, QSocketNotifier::Read, this);
    connect (m_notifier, SIGNAL(activated(int)), this, SLOT(remoteDataIncoming()));

}

void uart::uart_send_msg(QString msg)
{
    if (msg.isEmpty()) {
        return ;
    }
    ::write(m_fd, msg.data(), 2*msg.length());// 经实验  得读取到的长度乘2才能收得全
}

void uart::remoteDataIncoming()
{
    char c;
    if (read(m_fd, &c, sizeof c) != 1) {
        qDebug()<<("Error , Receive error!");
        return;
    }
    m_receive = (m_receive+c);
}
