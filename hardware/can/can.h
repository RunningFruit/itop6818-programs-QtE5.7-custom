#ifndef CANTEST_H
#define CANTEST_H


#include <QDialog>
#include <qsocketnotifier.h>

namespace Ui {
class cantest;
}

class cantest : public QDialog
{
    Q_OBJECT

public:
    explicit cantest(QWidget *parent = 0);
    ~cantest();

private slots:
    void on_m_receive_destroyed();

    void on_m_sendbutton_clicked();
private:
        int openSerialPort();

private:

        int m_fd,fd2;
        QSocketNotifier *m_notifier;

private:
    Ui::cantest *ui;
};

#endif // CANTEST_H
