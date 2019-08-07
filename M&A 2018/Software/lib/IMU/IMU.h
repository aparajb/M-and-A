#ifndef IMU_H
#define IMU_H

#include <I2C.h>
#include <Common.h>

struct Vector3D {
    double x;
    double y;
    double z;
};

class IMU {
public:
    IMU() {};
    Vector3D readAccelerometer();
    Vector3D readGyroscope();
    Vector3D readMagnetometer();
    void IMUSetup();
    void updateGyro();
    void calibrate();
    void findDrift();
    void negateDrift();
    double getIMUHeading();
    long driftPrevious;
private:
    double heading = 0;
    double calibration;
    double drift;
    long previousTime;
    double convertRawAcceleration(int raw) {
        double a = (raw * 2.0) / 32768.0;
        return a;
    }
    double convertRawGyro(int raw) {
        double g = (raw * 500.0) / 32768.0;
        return g;
    }
};

#endif
