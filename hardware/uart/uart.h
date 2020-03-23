#ifndef UART_H
#define UART_H


#include <qsocketnotifier.h>



class uart : public QObject
{

public:
    explicit uart();
    ~uart();

private:
    int openSerialPort();
    QString unicodeToString(QString str);
    QString stringToUnicode(QString str);

private:
    void on_m_sendButton_clicked();
    void remoteDataIncoming();

private:
    QString m_receive;
    QString m_send;
    int m_fd;
    QSocketNotifier *m_notifier;

};

#endif // UART_H
