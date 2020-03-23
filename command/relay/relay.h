#ifndef RELAY_H
#define RELAY_H


class relay {

public:
    explicit relay();
    ~relay();

public:
    void relay_open();
    void relay_toggle();
    void relay_close();
};

#endif // RELAY_H


