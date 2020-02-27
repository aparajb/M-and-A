#ifndef LSMULTIPLEXER_H
#define LSMULTIPLEXER_H

#include <Common.h>

class LSMultiplexer {
public:
    LSMultiplexer();
    void init();
    void update(float heading);
    Movement calculateOutAvoidance(float heading, Movement originalVal);
    float fieldLineAngle = -1;
    float fieldLineSize = -1;
    float lineDir;
    float lineSize;
    bool onField = true;
private:
    void read(uint8_t LSIndex);
    bool onWhite[LS_NUM] = {false};
    uint8_t control[5] = {LS_BINARY_0, LS_BINARY_1, LS_BINARY_2, LS_BINARY_3, LS_BINARY_4};
    uint8_t controlOutput = LS_OUTPUT;
    uint8_t pins[LS_NUM] = {LS_PIN_0, LS_PIN_1, LS_PIN_2, LS_PIN_3, LS_PIN_4, LS_PIN_5, LS_PIN_6, LS_PIN_7, LS_PIN_8, LS_PIN_9, LS_PIN_10, LS_PIN_11, LS_PIN_12, LS_PIN_13, LS_PIN_14, LS_PIN_15, LS_PIN_16, LS_PIN_17, LS_PIN_18, LS_PIN_19, LS_PIN_20, LS_PIN_21, LS_PIN_22, LS_PIN_23, LS_PIN_24, LS_PIN_25, LS_PIN_26, LS_PIN_27, LS_PIN_28, LS_PIN_29, LS_PIN_30, LS_PIN_31};
    uint16_t thresholdValue[LS_NUM] = {0};
    uint16_t readValue[LS_NUM] = {0};
};

# endif // LSMULTIPLEXER_H