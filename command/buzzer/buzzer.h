#ifndef MY_BUZZER_H
#define MY_BUZZER_H


class buzzer
{
public:
    explicit buzzer();
    ~buzzer();

public:
    void buzzer_open();
    void buzzer_toggle();
    void buzzer_close();

};

#endif // MY_BUZZER_H
