#include "rc522.h"
#include "ui_rc522.h"

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

#include <qtextedit.h>
#include <qprogressbar.h>
#include <qtimer.h>
#include <qapplication.h>
#include <qmessagebox.h>
#include <qstringlist.h>

#include "spidev.h"
#include "spidev_test.h"
#include <QFontDialog>

#define ARRAY_SIZE(a) (sizeof(a) / sizeof((a)[0]))


char type_rfid[6][15]={"MFOne-S50",
                       "MFOne-S70",
                       "MF-UltraLight",
                       "MF-Pro",
                       "MF Desire",
                       "Unknown"
                      };

const char *device = "/dev/rc522";

static uint8_t mode;
static uint8_t bits = 8;
static uint32_t speed = 400 * 1000;//500000;
static uint16_t delay;



unsigned char UID[5], Temp[4];



int rc522::WriteRawRC(int addr, int data)
{
        int ret;
        unsigned char  TxBuf[2];

        //bit7:MSB=0,bit6~1:addr,bit0:RFU=0
        TxBuf[0] = ((unsigned char)addr << 1)&0x7E;
        //TxBuf[0] &= 0x7E;

        TxBuf[1] = (unsigned char)data;

        ret = write(m_fd, TxBuf, 2);
        if (ret < 0)
                printf("spi:SPI Write error\n");

        usleep(10);

        return ret;
}

unsigned char rc522::ReadRawRC(int addr)
{
        int ret;
        unsigned char  ReData;
        unsigned char  Address;

        Address  = (unsigned char)addr << 1;
        Address |= (1 << 7);
        Address &= ~(1 << 0);

        ret = write(m_fd, &Address, 1);
        if (ret < 0)
                printf("spi:SPI Write error\n");

        usleep(100);

        ret = read(m_fd, &ReData, 1);
        if (ret < 0)
                printf("spi:SPI Read error\n");

        return ReData;
}

void rc522::SetBitMask(unsigned char reg,unsigned char mask)
{
        char tmp = 0x0;

        tmp = ReadRawRC(reg) | mask;

        WriteRawRC(reg,tmp | mask);
}

void rc522::ClearBitMask(unsigned char reg, unsigned char mask)
{
        char tmp = 0x0;

        tmp = ReadRawRC(reg)&(~mask);

        WriteRawRC(reg, tmp);  // clear bit mask
}

int rc522::rc522_init()
{
        int fd= 0;

        fd = ::open(device, O_RDWR|O_NONBLOCK);


            if (fd < 0)
                return -1;
        //reset


        return fd;
}

void rc522::PcdAntennaOn()
{
        unsigned char i;

        WriteRawRC(TxASKReg, 0x40);
        usleep(20);

        i = ReadRawRC(TxControlReg);
        if(!(i&0x03))
                SetBitMask(TxControlReg, 0x03);

        i = ReadRawRC(TxASKReg);
}

//static void rc522::print_usage(const char *prog)
//{
//        printf("Usage: %s [-DsbdlHOLC3]\n", prog);
//        puts("  -D --device   device to use (default /dev/spidev1.1)\n"
//             "  -s --speed    max speed (Hz)\n"
//             "  -d --delay    delay (usec)\n"
//             "  -b --bpw      bits per word \n"
//             "  -l --loop     loopback\n"
//             "  -H --cpha     clock phase\n"
//             "  -O --cpol     clock polarity\n"
//             "  -L --lsb      least significant bit first\n"
//             "  -C --cs-high  chip select active high\n"
//             "  -3 --3wire    SI/SO signals shared\n");
//        exit(1);
//}

void rc522::parse_opts()
{
        while (1) {
                static const struct option lopts[] = {
                        { "device",  1, 0, 'D' },
                        { "speed",   1, 0, 's' },
                        { "delay",   1, 0, 'd' },
                        { "bpw",     1, 0, 'b' },
                        { "loop",    0, 0, 'l' },
                        { "cpha",    0, 0, 'H' },
                        { "cpol",    0, 0, 'O' },
                        { "lsb",     0, 0, 'L' },
                        { "cs-high", 0, 0, 'C' },
                        { "3wire",   0, 0, '3' },
                        { "no-cs",   0, 0, 'N' },
                        { "ready",   0, 0, 'R' },
                        { NULL, 0, 0, 0 },
                };
                int c;

                c = getopt_long(NULL, NULL, "D:s:d:b:lHOLC3NR", lopts, NULL);

                if (c == -1)
                        break;

                switch (c) {
                case 'D':
                        device = optarg;
                        break;
                case 's':
                        speed = atoi(optarg);
                        break;
                case 'd':
                        delay = atoi(optarg);
                        break;
                case 'b':
                        bits = atoi(optarg);
                        break;
                case 'l':
                        mode |= SPI_LOOP;
                        break;
                case 'H':
                        mode |= SPI_CPHA;
                        break;
                case 'O':
                        mode |= SPI_CPOL;
                        break;
                case 'L':
                        mode |= SPI_LSB_FIRST;
                        break;
                case 'C':
                        mode |= SPI_CS_HIGH;
                        break;
                case '3':
                        mode |= SPI_3WIRE;
                        break;
                case 'N':
                        mode |= SPI_NO_CS;
                        break;
                case 'R':
                        mode |= SPI_READY;
                        break;
                default:
                        break;
                }
        }
}
char rc522::PcdComMF522(unsigned char Command, unsigned char *pInData,
                                                unsigned char InLenByte, unsigned char *pOutData,
                                                unsigned int  *pOutLenBit)

{
        char status = MI_ERR;
        unsigned char irqEn  = 0x00;
        unsigned char waitFor = 0x00;
        unsigned char lastBits;
        unsigned char n;
        unsigned int  i;

        switch (Command)
        {
                case PCD_AUTHENT:
                        irqEn   = 0x12;
                          waitFor = 0x10;
                          break;
                case PCD_TRANSCEIVE:
                        irqEn   = 0x77;
                        waitFor = 0x30;
                        break;
                default:
                        break;
        }

        WriteRawRC(ComIEnReg, irqEn|0x80);
        ClearBitMask(ComIrqReg, 0x80);
        WriteRawRC(CommandReg, PCD_IDLE);
        SetBitMask(FIFOLevelReg, 0x80);

        for(i=0; i<InLenByte; i++)
                        WriteRawRC(FIFODataReg, pInData[i]);
        WriteRawRC(CommandReg, Command);
        if(Command == PCD_TRANSCEIVE)
                SetBitMask(BitFramingReg,0x80);

        i = 6000;
        do
        {
                n = ReadRawRC(ComIrqReg);
                i--;
        }
        while((i!=0)&&!(n&0x01)&&!(n&waitFor));

        ClearBitMask(BitFramingReg, 0x80);

        if(i!=0)
        {
                if(!(ReadRawRC(ErrorReg) & 0x1B))
                {
                        status = MI_OK;
                        if (n&irqEn&0x01)
                                status = MI_NOTAGERR;
                        if(Command == PCD_TRANSCEIVE)
                        {
                                n = ReadRawRC(FIFOLevelReg);

                                lastBits = ReadRawRC(ControlReg) & 0x07;
                                if(lastBits)
                                        *pOutLenBit = (n-1)*8 + lastBits;
                                else
                                        *pOutLenBit = n*8;
                                if(n == 0)
                                        n = 1;
                                if(n>MAXRLEN)
                                        n = MAXRLEN;

                                for (i=0; i<n; i++)
                                        pOutData[i] = ReadRawRC(FIFODataReg);
                        }
                }
                else
                {
                        status = MI_ERR;
                }
        }

        SetBitMask(ControlReg, 0x80);// stop timer now
        WriteRawRC(CommandReg, PCD_IDLE);

        return status;
}

char rc522::PcdRequest(unsigned char req_code, unsigned char *pTagType)
{
        char status;
        unsigned int  unLen;
        unsigned char ucComMF522Buf[MAXRLEN];

        ClearBitMask(Status2Reg, 0x08);
        WriteRawRC(BitFramingReg, 0x07);
        SetBitMask(TxControlReg, 0x03);

        ucComMF522Buf[0] = req_code;

        status = PcdComMF522(PCD_TRANSCEIVE, ucComMF522Buf,
                                                1, ucComMF522Buf, &unLen);

        if ((status == MI_OK) && (unLen == 0x10))
        {
                *pTagType     = ucComMF522Buf[0];
                *(pTagType+1) = ucComMF522Buf[1];
        }
        else
        {
                status = MI_ERR;
        }

        return status;
}

char rc522::PcdAnticoll(unsigned char *pSnr)
{
        char status;
        unsigned char i, snr_check = 0;
        unsigned int  unLen;
        unsigned char ucComMF522Buf[MAXRLEN];

        ClearBitMask(Status2Reg, 0x08);
        WriteRawRC(BitFramingReg, 0x00);
        ClearBitMask(CollReg, 0x80);

        ucComMF522Buf[0] = PICC_ANTICOLL1;
        ucComMF522Buf[1] = 0x20;

        status = PcdComMF522(PCD_TRANSCEIVE, ucComMF522Buf,2, ucComMF522Buf, &unLen);

        if(status == MI_OK)
        {
                for (i=0; i<4; i++)
                {
                        *(pSnr+i)  = ucComMF522Buf[i];
                        snr_check ^= ucComMF522Buf[i];
                }
                if (snr_check != ucComMF522Buf[i])
                {
                        status = MI_ERR;
                }
        }
        SetBitMask(CollReg,0x80);

        return status;
}





rc522::rc522(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::rc522)
{


    char version = 0;
    parse_opts();
    ui->setupUi(this);

    m_fd =rc522_init();
    if (m_fd < 0)
            printf ("open success");
    WriteRawRC(CommandReg, PCD_RESETPHASE);
    usleep(10);
    WriteRawRC(ModeReg, 0x3D);
    WriteRawRC(TReloadRegL, 30);
    WriteRawRC(TReloadRegH, 0);
    WriteRawRC(TModeReg, 0x8D);
    WriteRawRC(TPrescalerReg, 0x3E);

    version = ReadRawRC(VersionReg);
    printf("Chip Version: 0x%x\n", version);
    usleep(50000);
    PcdAntennaOn();


    m_notifier = new QSocketNotifier(m_fd, QSocketNotifier::Read, this);
    connect (m_notifier, SIGNAL(activated(int)), this, SLOT(on_id_Edit_read()));

}

rc522::~rc522()
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

void rc522::on_id_Edit_read()
{
    int j;
    char c[50];
    ui->id_Edit->setText("");
    if(PcdRequest(0x52,Temp) == MI_OK)
    {
        if(Temp[0]==0x04 && Temp[1]==0x00)
                j=0;
        else if(Temp[0]==0x02 && Temp[1]==0x00)
                j=1;
        else if(Temp[0]==0x44 && Temp[1]==0x00)
                j=2;
        else if(Temp[0]==0x08 && Temp[1]==0x00)
                j=3;
        else if(Temp[0]==0x44 && Temp[1]==0x03)
                j=4;
        else
                j=5;

            if(PcdAnticoll(UID) == MI_OK)
            {
                sprintf(c,"%s:%x%x%x%x",type_rfid[j],UID[0],UID[1],UID[2],UID[3]);

                ui->id_Edit->setText(c);

                PcdRequest(0x52,Temp);//clear

            }
            else
            {
                sprintf(c,"%s,but no serial num read",type_rfid[j]);
                ui->id_Edit->setText(c);
            }
    }
    else
    {
            ui->id_Edit->setText("No Card!");
    }
}
