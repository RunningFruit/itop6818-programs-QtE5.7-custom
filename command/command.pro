

QT += core
QT -= gui

QT += network websockets
QT += sql

CONFIG += c++11

TARGET = command
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app


CONFIG += static


SOURCES += main.cpp \
        websocket/datareceive.cpp \
        ad/ad.cpp \
        buzzer/buzzer.cpp \
        can/cantest.cpp \
        led/led.cpp \
        rc522/rc522.cpp \
        relay/relay.cpp \
        rs485/rs485.cpp \
        rtc/rtc.cpp \
        tcp/tcp.cpp \
        timer/MyTimer.cpp \
        uart/uart.cpp \
        watchdog/watchdog.cpp \
        sys/sysinfo.cpp \
        db/dbutil.cpp \
        utils/JsonUtil.cpp \
        utils/HttpUtil.cpp \
        utils/HttpGetUtil.cpp \
        utils/HttpPostUtil.cpp \
        utils/HttpDownFileUtil.cpp \
        shell/shell.cpp \
        gps/gps.cpp


HEADERS  += common/common.h \
        websocket/datareceive.h \
        ad/ad.h \
        buzzer/buzzer.h \
        can/cantest.h \
        led/led.h \
        rc522/rc522.h \
        relay/relay.h \
        rs485/rs485.h \
        rtc/rtc.h \
        tcp/tcp.h \
        timer/MyTimer.h \
        uart/uart.h \
        watchdog/watchdog.h \
        db/dbutil.h \
        utils/JsonUtil.h \
        utils/HttpUtil.h \
        utils/HttpGetUtil.h \
        utils/HttpPostUtil.h \
        utils/HttpDownFileUtil.h \
        shell/shell.h \
        gps/gps.h

#LIBS+=/usr/local/arm/arm-2014.05/arm-none-linux-gnueabi/libc/usr/lib/*
