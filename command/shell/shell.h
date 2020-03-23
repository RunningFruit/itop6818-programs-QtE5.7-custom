#ifndef SHELL_H
#define SHELL_H

#include <QObject>

class shell: public QObject
{
public:
    explicit shell();
    ~shell();

public:
    QString cmd(QString strCmd);

};

#endif // SHELL_H
