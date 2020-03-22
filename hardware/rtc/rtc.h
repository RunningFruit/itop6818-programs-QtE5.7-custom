#ifndef RTC_H
#define RTC_H

#include <QMainWindow>
#include <QBasicTimer>
#include <QTimerEvent>

namespace Ui {
class rtc;
}

class rtc : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit rtc(QWidget *parent = 0);
    ~rtc();
protected:
   void timerEvent(QTimerEvent *event);
   void moveEvent(QMoveEvent *);
   void resizeEvent(QResizeEvent *);
   void closeEvent(QCloseEvent *);
private slots:
    void on_set_clicked();

private:
    Ui::QMainWindow *ui;
    QBasicTimer timer;
};

#endif // RTC_H
