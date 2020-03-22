#ifndef TIMER_EVENT_H
#define TIMER_EVENT_H

#include <QWidget>

namespace Ui {
    class Widget;
}

class timerevent : public QWidget
{
    Q_OBJECT

public:
    explicit timerevent(QWidget *parent = 0);
    ~timerevent();
protected:
    void timerEvent(QTimerEvent *event);
private slots:
    void timerUpdate();
private:
    Ui::Widget *ui;
    int id1,id2,id3;

};

#endif // TIMER_EVENT_H
