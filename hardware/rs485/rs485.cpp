#include "rs485.h"
#include "ui_rs485.h"

#include <qtextedit.h>
#include <qprogressbar.h>
#include <qtimer.h>
#include <qapplication.h>
#include <qmessagebox.h>
#include <qstringlist.h>

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <linux/fs.h>
#include <errno.h>
#include <string.h>
#include <termio.h>

rs485::rs485(QWidget *parent) :
        QDialog(parent),
        ui(new Ui::rs485)
{
        ui->setupUi(this);
        m_fd = openSerialPort();
        fd2 = ::open("/dev/max485_ctl_pin",0);
        if(fd2 < 0)
                printf("on_m_sendButton_clicked Open max485_ctl faild\n");
        if (m_fd < 0) {
            QMessageBox::warning(this, tr("Error"), tr("Fail to open serial port!"));
            return ;
        }

        m_notifier = new QSocketNotifier(m_fd, QSocketNotifier::Read, this);
        connect (m_notifier, SIGNAL(activated(int)), this, SLOT(remoteDataIncoming()));

}
rs485::~rs485()
{
        delete ui;
        if (m_notifier) {
            delete m_notifier;
            m_notifier = 0;
        }

        if (m_fd >= 0) {
            ::close(m_fd);
            m_fd = -1;
        }
}

int set_opt(int fd,int nSpeed, int nBits, char nEvent, int nStop)
{
    struct termios newtio,oldtio;
    if  ( tcgetattr( fd,&oldtio)  !=  0) {
        perror("SetupSerial 1");
        return -1;
    }
    bzero( &newtio, sizeof( newtio ) );
    newtio.c_cflag  |=  CLOCAL | CREAD;
    newtio.c_cflag &= ~CSIZE;

    switch( nBits )
    {
    case 7:
        newtio.c_cflag |= CS7;
        break;
    case 8:
        newtio.c_cflag |= CS8;
        break;
    }

    switch( nEvent )
    {
    case 'O':
        newtio.c_cflag |= PARENB;
        newtio.c_cflag |= PARODD;
        newtio.c_iflag |= (INPCK | ISTRIP);
        break;
    case 'E':
        newtio.c_iflag |= (INPCK | ISTRIP);
        newtio.c_cflag |= PARENB;
        newtio.c_cflag &= ~PARODD;
        break;
    case 'N':
        newtio.c_cflag &= ~PARENB;
        break;
    }

    switch( nSpeed )
    {
    case 1200:
        cfsetispeed(&newtio, B1200);
        cfsetospeed(&newtio, B1200);
        break;
    case 2400:
        cfsetispeed(&newtio, B2400);
        cfsetospeed(&newtio, B2400);
        break;
    case 4800:
        cfsetispeed(&newtio, B4800);
        cfsetospeed(&newtio, B4800);
        break;
    case 9600:
        cfsetispeed(&newtio, B9600);
        cfsetospeed(&newtio, B9600);
        break;
    case 115200:
        cfsetispeed(&newtio, B115200);
        cfsetospeed(&newtio, B115200);
        break;
    case 460800:
        cfsetispeed(&newtio, B460800);
        cfsetospeed(&newtio, B460800);
        break;
    default:
        cfsetispeed(&newtio, B9600);
        cfsetospeed(&newtio, B9600);
        break;
    }
    if( nStop == 1 )
        newtio.c_cflag &=  ~CSTOPB;
    else if ( nStop == 2 )
    newtio.c_cflag |=  CSTOPB;
    newtio.c_cc[VTIME]  = 0;
    newtio.c_cc[VMIN] = 0;
    tcflush(fd,TCIFLUSH);
    if((tcsetattr(fd,TCSANOW,&newtio))!=0)
    {
        perror("com set error");
        return -1;
    }

    return 0;
}

int rs485::openSerialPort()
{
    int fd=-1;

    const char *tty = "/dev/ttySAC11";
    fd = ::open(tty, O_RDWR|O_NONBLOCK);
    if(fd <0 )
          printf("open ttySAC1 failed\n");
    else
       {
          printf("open ttySAC1 success\n");
          set_opt(fd, 9600, 8, 'N', 1);
       }
    return fd;
}
void rs485::on_m_sendButton_clicked()
{
        int ret;

        ret = ioctl(fd2, 1, 0);
        QString text( ui->m_send->toPlainText());
        if (text.isEmpty()) {
                return ;
         }
        write(m_fd, (text.data()),2*text.length());
        usleep(2*(16*text.length()+2)*100);//100=1000000/B9600
        ret = ioctl(fd2, 0, 0);
}

void rs485::remoteDataIncoming()
{
        int ret=-1;
        char c;

        if(fd2 < 0)
                printf("remoteDataIncoming Open max485_ctl faild\n");
        ret = ioctl(fd2, 0, 0);
        printf("ret is %d\n",ret);
        if (read(m_fd, &c, sizeof c) != 1) {
            QMessageBox::warning(this, tr("Error"), tr("Receive error!"));
            return;
            }
        if(c!=NULL)
            ui->m_receive->setText(ui->m_receive->toPlainText()+c);
}
