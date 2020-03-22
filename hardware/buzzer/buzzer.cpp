#include "buzzertest.h"
#include "ui_buzzertest.h"

//add by myself
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <sys/ioctl.h>
#include <stdio.h>

//#include <QDirectPainter>

static int fb;
volatile int BUZZER=0;

buzzertest::buzzertest(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::buzzertest)
{
    ui->setupUi(this);

    connect(ui->checkBox_Buzzer,SIGNAL(toggled(bool)),this,SLOT(BUZZER_Toggle()));

    fb=open("/dev/buzzer_ctl",0);
    if(fb<0)
    {
        perror("open device buzzer failed!");
        exit(1);

    }

}

buzzertest::~buzzertest()
{
    delete ui;
}
void buzzertest::changeEvent(QEvent *e)
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

void buzzertest::BUZZER_Toggle()
{
    BUZZER=~BUZZER;
    if(BUZZER==0)
    {
        ioctl(fb,1,0);
    }
    else
    {
        ioctl(fb,0,0);
    }
}
