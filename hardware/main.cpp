#include "ad/ad.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    ad w;

    return a.exec();
}
