#ifndef CAN_H
#define CAN_H


#include <QDialog>
#include <qsocketnotifier.h>

class can
{

public:
    explicit can();
    ~can();

private slots:
    void on_m_receive_destroyed();

    void on_m_sendbutton_clicked();
private:
    int openSerialPort();

private:    
    int m_fd,fd2;
    QSocketNotifier *m_notifier;
};

#endif // CAN_H
