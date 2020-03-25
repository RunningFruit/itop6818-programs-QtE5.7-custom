#ifndef MY_AD_H
#define MY_AD_H

#include <QObject>

class ad: public QObject
{
public:
    explicit ad();
    ~ad();

protected:
    void open();

};

#endif // MY_AD_H
