#ifndef UART_H
#define UART_H


#include <qsocketnotifier.h>



class uart : public QObject
{

public:
    explicit uart();
    ~uart();

public:
    void uart_open();
    void uart_send_msg(QString msg);
    void uart_close();

//private:
//    QString unicodeToString(QString str);
//    QString stringToUnicode(QString str);

private slots:
    void remoteDataIncoming();

private:
    QString m_receive;
    int m_fd;
    QSocketNotifier *m_notifier;

};

#endif // UART_H
