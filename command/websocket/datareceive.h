﻿#ifndef DATARECEIVE_H
#define DATARECEIVE_H

#include <QtCore/QObject>
#include <QWebSocket>
#include <QString>
#include <QTimer>
#include <QDebug>
#include <unistd.h>

#include "common/common.h"
#include "led/led.h"
#include "buzzer/buzzer.h"
#include "relay/relay.h"
#include "rtc/rtc.h"
#include "watchdog/watchdog.h"
#include "rc522/rc522.h"
#include "rs485/rs485.h"
#include "uart/uart.h"
#include "shell/shell.h"
#include "sys/sysinfo.h"
#include "db/dbutil.h"
#include "timer/MyTimer.h"
#include "utils/JsonUtil.h"
#include "utils/HttpPostUtil.h"
#include "utils/HttpDownFileUtil.h"


class DataReceive : public QObject
{
    Q_OBJECT
public:
    DataReceive(QObject *parent=0);
    ~DataReceive();

public slots:
    void createDataRecvWS();    /*-<创建websocket连接 */

private:
    QString m_connect_url;
    QWebSocket *dataRecvWS;     /*-<websocket类 */
    bool connectStatus;         /*-<websocket连接状态，连接成功：true；断开：false */
    void reconnect();           /*-<周期重连函数 */
    QTimer *m_timer;            /*-<周期重连Timer */


private:
    HttpPostUtil *postUtil;
    HttpDownFileUtil *downfileUtil;
    JsonUtil *jsonUtil;
    void deviceCmd(QString device,QString cmd,QString msg);
    led *light;
    buzzer *buz;
    relay *rlay;
    rtc *m_rtc;
    watchdog *m_watchdog;
    rc522 *m_rc522;
    uart *m_uart;
    rs485 *m_rs485;
    MyTimer *m_3timer;
    shell *m_shell;


private slots:
    void onConnected();                 /*-<socket建立成功后，触发该函数 */
    void onTextReceived(QString msg);   /*-<收到Sev端的数据时，触发该函数 */
    void onDisConnected();              /*-<socket连接断开后，触发该函数 */
};

#endif // DATARECEIVE_H

