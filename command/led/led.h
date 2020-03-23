#ifndef LED_H
#define LED_H


class led
{

public:
    explicit led();
    ~led();

public:
    void led_open();
    void led_toggle();
    void led_close();
};

#endif // LED_H
