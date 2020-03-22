#ifndef LEDTEST_H
#define LEDTEST_H

#include <QMainWindow>

namespace Ui {
class ledtest;
}

class ledtest : public QMainWindow
{
    Q_OBJECT

public:
    explicit ledtest(QWidget *parent = 0);
    ~ledtest();

//add by myself
protected:
    void changeEvent(QEvent *e);

public slots:
    void LED_Toggle();


private:
    Ui::ledtest *ui;
};

#endif // LEDTEST_H
