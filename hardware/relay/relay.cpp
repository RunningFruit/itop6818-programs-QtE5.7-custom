#include "relaytest.h"
#include "ui_relaytest.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <sys/ioctl.h>
#include <stdio.h>
#include <QVariant>

static int fb;
volatile int RELAY=0;

relaytest::relaytest(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::relaytest)
{
    ui->setupUi(this);


    fb=open("/dev/relay_ctl",0);

    if(fb<0)
    {
        perror("open device buzzer failed!");
        exit(1);

    }
    connect(ui->RELAY_Button,SIGNAL(toggled(bool)),this,SLOT(on_RELAY_Button_clicked()));

}

relaytest::~relaytest()
{
    delete ui;
}



void relaytest::on_RELAY_Button_clicked()
{
    RELAY=~RELAY;
    if(RELAY)
    {
        ioctl(fb,1,1);
        printf ("ok");
    }
    else
    {
        ioctl(fb,0,0);
        printf ("ok");
    }
}
