#include "can.h"

#include <iostream>
#include <qtextedit.h>
#include <qprogressbar.h>
#include <qtimer.h>
#include <qapplication.h>

#include <qstringlist.h>
#include <stdio.h>
#include <string>
#include <unistd.h>
#include <stdlib.h>
#include <net/if.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <linux/can.h>
#include <linux/can/raw.h>

#include <sys/types.h>
#include <sys/stat.h>

#include <linux/fs.h>
#include <errno.h>

#include <termio.h>
#include <ctype.h>


can::can()
{
    m_fd=openSerialPort();

    if (m_fd < 0) {
        printf("Error, Fail to open serial port!");
        return ;
    }
}

can::~can()
{

    if (m_fd >= 0) {
        ::close(m_fd);
        m_fd = -1;
    }
}
int can::openSerialPort()
{
    int s;
    struct sockaddr_can addr;
    struct ifreq ifr;

    if ((s = socket(PF_CAN, SOCK_RAW, CAN_RAW)) < 0)
    {
        perror("Create socket failed");
        exit(-1);
    }

    /* set up can interface */
    strcpy(ifr.ifr_name, "can0");
    //printf("can port is %s\n",ifr.ifr_name);
    /* assign can device */
    ioctl(s, SIOCGIFINDEX, &ifr);
    addr.can_family = AF_CAN;
    addr.can_ifindex = ifr.ifr_ifindex;
    /* bind can device */
    if(bind(s, (struct sockaddr *)&addr, sizeof(addr)) < 0)
    {
        perror("Bind can device failed\n");
        exit(-2);
    }
    return s;

}


struct can_frame frame;
void can::on_m_receive_destroyed()
{
    int i;
    struct can_filter rfilter[1];
    /* set filter for only receiving packet with can id 0x1F */
    rfilter[0].can_id = 0x1F;
    rfilter[0].can_mask = CAN_SFF_MASK;
    if(setsockopt(m_fd, SOL_CAN_RAW, CAN_RAW_FILTER, &rfilter, sizeof(rfilter)) < 0)
    {
        perror("set receiving filter error\n");
        exit(-3);
    }
    /* keep reading */

    if(read(m_fd, &frame, sizeof(frame)) <= 0 ){
        perror("read");
        printf ("Error,Receive error!");
        return;
    }

    for(i=0;i<8;i++){
        if(frame.data[i]!=NULL){
            //ui->m_receive->setText(ui->m_receive->toPlainText()+frame.data[i]);
        }
    }

    printf ("%s\n",frame.data);
    printf ("receive");

}



void can::on_m_sendbutton_clicked()
{
    int i,j;

    frame.can_id = 0x1F;
    frame.can_dlc = 8;
    printf("send");
    //QString text( ui->m_send->toPlainText());
    QString text("");
    if (text.isEmpty()) {
        return ;
    }
    for(j=0;j<text.length(); ){
        memset(frame.data,0,sizeof(frame.data));
        for(i=0;i<8;i++){
            //frame.data[i]=(text.data()+j)->toAscii();
            frame.data[i]=NULL;
            if(frame.data[i]!=NULL){
                j++;
            }
            else
                break;
        }
        write(m_fd,&frame,sizeof(frame));
        printf ("%s\n",frame.data);

    }

}

