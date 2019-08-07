#include "PID.h"

PID::PID(float p, float i, float d, float absoluteMax) {
    kp = p;
    ki = i;
    kd = d;
    absMax = absoluteMax;
    lastTime = micros();
}

float PID::update(float input, float setpoint, float modulus) {
    float derivative;
    float error = setpoint - input;
    unsigned long currentTime = micros();
    float elapsedTime = (currentTime - lastTime) / 1000000.0;
    lastTime = currentTime;
    integral += elapsedTime * error;
    if(modulus != 0.0) {
        float difference = (error - lastError);
        if(difference < -modulus) {
            difference += modulus;
        } else if(difference > modulus) {
            difference -= modulus;
        }
        derivative = -difference / elapsedTime;
    } else {
        derivative = -(error - lastError) / elapsedTime;
    }
    lastError = error;
    float correction = kp * error + ki * integral - kd * derivative;
    return absMax == 0 ? correction : constrain(correction, -absMax, absMax);
}
