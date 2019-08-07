#include "BatteryIndicator.h"

void BatteryIndicator::init() {
    pinMode(BATTERY_INDICATOR_PIN, INPUT);
}

void BatteryIndicator::update() {
    int value = analogRead(BATTERY_INDICATOR_PIN);
    batteryVoltage = constrain(value / (float)VOLTAGE_DIVIDER, LOW_BATTERY_VOLTAGE, 12.6);
}

bool BatteryIndicator::lowBattery() {
    update();
    if(lowBatCount > 100) {
        return true;
    }
    if(batteryVoltage <= LOW_BATTERY_VOLTAGE) {
        lowBatCount += 1;
    } else {
        lowBatCount = 0;
    }
    return false;
}