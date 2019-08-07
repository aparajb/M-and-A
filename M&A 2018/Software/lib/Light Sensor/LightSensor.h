#ifndef LIGHTSENSOR_H
#define LIGHTSENSOR_H

#include <Arduino.h>
#include <Common.h>

class LightSensor {
public:
    LightSensor();
    LightSensor(int in);
	void lightSensorSetup();
    void setThreshold(int thresh);
    void read();
    bool onWhite();
    int getReadValue();
private:
    int readValue;
    int inPin;
    int thresholdValue;
};

#endif
