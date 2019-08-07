#ifndef PID_H
#define PID_H

#include <Arduino.h>

class PID
{
public:
    PID(double p, double i, double d, double absoluteMax = 0.0);
    double kp;
    double ki;
    double kd;
    double update(double input, double setpoint, double modulus = 0.0);
private:
    unsigned long lastTime;
    double lastError = 0;
    double absMax;
    double integral;
    double last;
};

#endif
