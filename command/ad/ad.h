#ifndef AD_H
#define AD_H

#include <QObject>

class ad: public QObject
{
public:
    explicit ad();
    ~ad();

protected:
    void open();

};

#endif // AD_H
