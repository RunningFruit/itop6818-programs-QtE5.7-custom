#ifndef RC522_H
#define RC522_H


#include <qsocketnotifier.h>

class rc522
{

public:
    explicit rc522();
    ~rc522();

private:

    int WriteRawRC(int addr, int data);
    unsigned char ReadRawRC(int addr);
    void SetBitMask(unsigned char reg,unsigned char mask);
    void ClearBitMask(unsigned char reg, unsigned char mask);
    int rc522_init();
    void PcdAntennaOn();
    //static void print_usage(const char *prog);
    void parse_opts();
    char PcdComMF522(unsigned char Command, unsigned char *pInData,
                     unsigned char InLenByte, unsigned char *pOutData,
                     unsigned int  *pOutLenBit);

    char PcdRequest(unsigned char req_code, unsigned char *pTagType);
    char PcdAnticoll(unsigned char *pSnr);
    void HandleConfigMenu(unsigned char inputvalue);
private:
    int m_fd;
    QSocketNotifier *m_notifier;

private slots:
    void on_id_Edit_read();

};

#endif // RC522_H
