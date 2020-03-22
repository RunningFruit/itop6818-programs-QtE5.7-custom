#ifndef UARTTEST_H
#define UARTTEST_H

#include <QDialog>
#include <qsocketnotifier.h>

namespace Ui {
class uarttest;
}

class uarttest : public QDialog
{
    Q_OBJECT

public:
    explicit uarttest(QWidget *parent = 0);
    ~uarttest();

private:
        int openSerialPort();
        QString unicodeToString(QString str);

        QString stringToUnicode(QString str);

private slots:
        void on_m_sendButton_clicked();
        void remoteDataIncoming();

private:
        int m_fd;
        QSocketNotifier *m_notifier;

private:
    Ui::uarttest *ui;
};

#endif // UARTTEST_H
