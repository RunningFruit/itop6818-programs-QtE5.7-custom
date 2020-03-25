#ifndef MY_SHELL_H
#define MY_SHELL_H

#include <QObject>

class shell: public QObject
{
public:
    explicit shell();
    ~shell();

public:
    QString cmd(QString strCmd);

};

#endif // MY_SHELL_H
