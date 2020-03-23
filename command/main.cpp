#include <QCoreApplication>

#include "websocket/datareceive.h"


int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    //localhost:8086/device/led/on/itop6818-8323329
    DataReceive *dr = new DataReceive();
    dr->createDataRecvWS();

    return a.exec();
}
