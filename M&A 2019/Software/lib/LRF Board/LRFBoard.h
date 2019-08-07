#ifndef LRFBOARD_H
#define LRFBOARD_H

#include <Common.h>

class LRFBoard {
public:
    LRFBoard();
    void init();
    void update();
    uint16_t front = 0;
    uint16_t back = 0;
    uint16_t left = 0;
    uint16_t right = 0;
};

#endif // LRFBOARD_H