#ifndef MY_RC522_H
#define MY_RC522_H


#include <QObject>
#include <QDebug>
#include <qtimer.h>
#include <qstringlist.h>

#include <stdint.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <linux/types.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <linux/fs.h>
#include <errno.h>
#include <string.h>
#include <termio.h>

#include <qsocketnotifier.h>
#include "spidev.h"
#include "spidev_test.h"


class rc522:public QObject
{

public:
    explicit rc522();
    ~rc522();
    void open();
    void close();

private:
    int rc522_init();
    int WriteRawRC(int addr, int data);
    unsigned char ReadRawRC(int addr);
    void SetBitMask(unsigned char reg,unsigned char mask);
    void ClearBitMask(unsigned char reg, unsigned char mask);

    void PcdAntennaOn();
    //static void print_usage(const char *prog);
    void parse_opts();
    char PcdComMF522(unsigned char Command, unsigned char *pInData,
                     unsigned char InLenByte, unsigned char *pOutData,
                     unsigned int  *pOutLenBit);

    char PcdRequest(unsigned char req_code, unsigned char *pTagType);
    char PcdAnticoll(unsigned char *pSnr);
//    void HandleConfigMenu(unsigned char inputvalue);
private:
    int m_fd;
    QSocketNotifier *m_notifier;

private slots:
    void on_card_read();

};

#endif // MY_RC522_H
