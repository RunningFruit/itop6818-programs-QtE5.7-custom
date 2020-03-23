#include <QCoreApplication>
#include "websocket/datareceive.h"
#include "sys/sysinfo.h"
#include "db/dbutil.h"


int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

//    sysinfo *info = new sysinfo();

    dbutil *util = new dbutil();

//    DataReceive *dr = new DataReceive();
//    dr->createDataRecvWS();

    return a.exec();
}
