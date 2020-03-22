#ifndef BUZZERTEST_H
#define BUZZERTEST_H

#include <QMainWindow>

namespace Ui {
class buzzertest;
}

class buzzertest : public QMainWindow
{
    Q_OBJECT

public:
    explicit buzzertest(QWidget *parent = 0);
    ~buzzertest();
    //add by myself
protected:
     void changeEvent(QEvent *e);

public slots:
     void BUZZER_Toggle();

private:
    Ui::buzzertest *ui;
};

#endif // BUZZERTEST_H
