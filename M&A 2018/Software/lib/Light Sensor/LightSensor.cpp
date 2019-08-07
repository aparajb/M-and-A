#include "LightSensor.h"

LightSensor::LightSensor() {}

LightSensor::LightSensor(int in) {
    inPin = in;
    thresholdValue = LS_DEFAULT_THRESHOLD;
}

void LightSensor::lightSensorSetup() {
    pinMode(inPin, INPUT);
    int calibrateTotal = 0;
    for (int i = 0; i < LS_CALIBRATE_COUNT; i++) {
        read();
        calibrateTotal += readValue;
    }
    setThreshold((int)round(calibrateTotal / LS_CALIBRATE_COUNT) + LS_BUFFER);
}

void LightSensor::read() {
    readValue = analogRead(inPin);
}

void LightSensor::setThreshold(int thresh) {
    thresholdValue = thresh;
}

bool LightSensor::onWhite() {
    read();
    return (readValue > thresholdValue);
}

int LightSensor::getReadValue() {
    return readValue;
}
