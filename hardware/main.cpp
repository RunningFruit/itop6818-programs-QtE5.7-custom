#include "mainwindow.h"
#include <QApplication>
#include "websocket/datareceive.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    //http://localhost:8086/push/user1?message=hello
    DataReceive *m_dataReceive = new DataReceive();
    m_dataReceive->createDataRecvWS();

    return a.exec();
}
