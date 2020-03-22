#-------------------------------------------------
#
# Project created by QtCreator 2016-07-26T19:19:55
#
#-------------------------------------------------

QT       += core gui
QT       += network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = hardware
TEMPLATE = app


SOURCES += main.cpp\
        ad/ad.cpp \
        buzzer/buzzer.cpp \
        can/can.cpp \
        led/led.cpp \
        rc522/rc522.cpp \
        relay/relay.cpp \
        rs485/rs485.cpp \
        rtc/rtc.cpp \
        tcp/tcp.cpp \
        timerevent/timerevent.cpp \
        uart/uart.cpp \
        watchdog/watchdog.cpp

HEADERS  += ad/ad.h \
        buzzer/buzzer.h \
        can/can.h \
        led/led.h \
        rc522/rc522.h \
        relay/relay.h \
        rs485/rs485.h \
        rtc/rtc.h \
        tcp/tcp.h \
        timerevent/timerevent.h \
        uart/uart.h \
        watchdog/watchdog.h

