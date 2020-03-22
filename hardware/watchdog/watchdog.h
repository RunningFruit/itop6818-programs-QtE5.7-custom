#ifndef WATCHDOG_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QBasicTimer>

namespace Ui {
class watchdog;
}

class watchdog : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit watchdog(QWidget *parent = 0);
    ~watchdog();
    
protected:
    void timerEvent(QTimerEvent *);
    void moveEvent(QMoveEvent *);
    void resizeEvent(QResizeEvent *);
    void closeEvent(QCloseEvent *);
private slots:
    void on_pushButton_clicked();

private:
    Ui::watchdog *ui;
    QBasicTimer timer;
    int fd;
    int times;
    char s;
};

#endif // WATCHDOG_H
