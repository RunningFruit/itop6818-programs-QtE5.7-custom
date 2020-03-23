QT += core
QT -= gui

QT += network websockets

CONFIG += c++11

TARGET = hardware
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app


SOURCES += main.cpp \
        websocket/datareceive.cpp \
        ad/ad.cpp \
        buzzer/buzzer.cpp \
#        can/can.cpp \
        led/led.cpp \
        rc522/rc522.cpp \
        relay/relay.cpp \
        rs485/rs485.cpp \
        rtc/rtc.cpp \
        tcp/tcp.cpp \
        timerevent/timerevent.cpp \
        uart/uart.cpp \
        watchdog/watchdog.cpp

HEADERS  += websocket/datareceive.h \
        ad/ad.h \
        buzzer/buzzer.h \
#        can/can.h \
        led/led.h \
        rc522/rc522.h \
        relay/relay.h \
        rs485/rs485.h \
        rtc/rtc.h \
        tcp/tcp.h \
        timerevent/timerevent.h \
        uart/uart.h \
        watchdog/watchdog.h

