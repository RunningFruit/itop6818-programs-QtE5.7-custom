#ifndef RS485_H
#define RS485_H

#include <QDialog>
#include <qsocketnotifier.h>

namespace Ui {
class rs485;
}

class rs485 : public QDialog
{
    Q_OBJECT

public:
    explicit rs485(QWidget *parent = 0);
    ~rs485();

private:
        int openSerialPort();
        QString unicodeToString(QString str);
        QString stringToUnicode(QString str);
private slots:

        void on_m_sendButton_clicked();
        void remoteDataIncoming();

private:
        int m_fd,fd2;
        QSocketNotifier *m_notifier;

private:
    Ui::rs485 *ui;
};

#endif // RS485_H
