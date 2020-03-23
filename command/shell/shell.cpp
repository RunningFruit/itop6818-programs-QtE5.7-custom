#include "shell.h"

#include <QProcess>

shell::shell(){

}

shell::~shell(){

}

QString shell::cmd(QString strCmd){
    QProcess p;
    p.start("bash", QStringList() <<"-c" << strCmd);
    p.waitForFinished();
    QString strResult = p.readAllStandardOutput();
    return strResult;
}
