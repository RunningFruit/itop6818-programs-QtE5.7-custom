#ifndef RELAYTEST_H
#define RELAYTEST_H

#include <QMainWindow>

namespace Ui {
class relaytest;
}

class relaytest : public QMainWindow
{
    Q_OBJECT

public:
    explicit relaytest(QWidget *parent = 0);
    ~relaytest();

private slots:

    void on_RELAY_Button_clicked();

private:
    Ui::relaytest *ui;

};

#endif // RELAYTEST_H


