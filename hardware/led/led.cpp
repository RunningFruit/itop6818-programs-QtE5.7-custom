#include "ledtest.h"
#include "ui_ledtest.h"

//add by myself
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <sys/ioctl.h>
#include <stdio.h>

//#include <QDirectPainter>

static int fb;
volatile int LED=0;



ledtest::ledtest(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ledtest)
{
    ui->setupUi(this);

    //int screenWidth=QDirectPainter::screenWidth();
    //int screenHeight=QDirectPainter::screenHeight();
    //this->resize(screenWidth,screenHeight);

    connect(ui->checkBox_LED,SIGNAL(toggled(bool)),this,SLOT(LED_Toggle()));


    fb=open("/dev/leds_ctl",0);
    if(fb<0)
    {
        perror("open device led failed!");
        exit(1);

    }

}

ledtest::~ledtest()
{
    delete ui;
}

void ledtest::changeEvent(QEvent *e)
{
    QMainWindow::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);

        break;
    default:
        break;
    }

}

void ledtest::LED_Toggle()
{
    LED=~LED;
    if(LED==0)
    {
        ioctl(fb,1,0);
    }
    else
    {
        ioctl(fb,0,0);
    }
}
