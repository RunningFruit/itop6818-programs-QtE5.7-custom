#ifndef BUZZER_H
#define BUZZER_H


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

#endif // BUZZER_H
