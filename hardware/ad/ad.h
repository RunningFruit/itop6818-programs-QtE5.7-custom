#ifndef ADTEST_H
#define ADTEST_H

#include <QWidget>

#include<qlcdnumber.h>

namespace Ui {
class adtest;
}

class adtest : public QWidget
{
    Q_OBJECT

public:
    explicit adtest(QWidget *parent = 0);
    ~adtest();

protected:
    void timerEvent(QTimerEvent *);

private:
    Ui::adtest *ui;
    QLCDNumber* m_label;
};

#endif // ADTEST_H
