#include "watchdog.h"
#include "ui_watchdog.h"
#include <unistd.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <linux/types.h>
#include <linux/watchdog.h>
#include <QMessageBox>

watchdog::watchdog(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::watchdog)
{
    ui->setupUi(this);

    fd = 0;
    times = 0;
    s='V';
}

watchdog::~watchdog()
{
    delete ui;
    ::close(fd);
}

void watchdog::timerEvent(QTimerEvent *)
{
    int dummy;
    QString str;

    times++;

    if(ui->checkBox->isChecked())
        ::ioctl(fd,WDIOC_KEEPALIVE,&dummy);

    ui->times->setText(str.sprintf("%d",times));
}

void watchdog::on_pushButton_clicked()
{
    if(ui->pushButton->text() == QString("open watchdog"))
    {
        ui->pushButton->setText("close watchdog");
        ui->checkBox->setDisabled(true);

        if(ui->checkBox->isChecked())
        {
            ui->label_2->setText("Keep feeding the watchdog, system will not restart.");
        }
        else
        {
            ui->label_2->setText("System will restart in 1 minute without feed dog.");
        }

        fd = ::open("/dev/watchdog",O_WRONLY);
        if(fd < 0)
        {
            QMessageBox::about(this,"error","open watchdog failure");
            exit(-1);
        }


        write(fd,(char *)&s,sizeof(s));

        times = 0;
        ui->times->setText("0");
        timer.start(1000,this);
    }
    else
    {
        ui->pushButton->setText("open watchdog");
        ui->checkBox->setEnabled(true);
        timer.stop();
        ::close(fd);
    }
}

void watchdog::moveEvent(QMoveEvent *)
{
    this->move(QPoint(0,0));
}

void watchdog::resizeEvent(QResizeEvent *)
{
    this->showMaximized();
}

void watchdog::closeEvent(QCloseEvent *)
{
   destroy();
    exit(0);
}

