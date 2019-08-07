#ifndef BATTERY_INDICATOR_H_
#define BATTERY_INDICATOR_H_

#include <Common.h>

class BatteryIndicator {
public:
    BatteryIndicator() {};
    void init();
    void update();
    bool lowBattery();
private:
    int p;
    float batteryVoltage;
    int lowBatCount = 0;
};

#endif