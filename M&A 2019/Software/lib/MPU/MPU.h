#ifndef MPU_H
#define MPU_H

#include <I2C.h>
#include <Common.h>

class MPU {
public:
    MPU() {};
    void init();
    void update();
    float heading;
private:
    Vector3D readGyroscope();
    void calibrate();
    float convertRawGyro(int raw);
    long previousTimeGyro;
    long previousDrift;
    float calibrationGyro;
    float drift = 0;
};

#endif
