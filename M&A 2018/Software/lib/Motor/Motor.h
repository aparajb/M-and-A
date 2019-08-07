#ifndef MOTOR_H_
#define MOTOR_H_

#include <Arduino.h>

class Motor {
public:
	Motor() {}
	Motor(int dirOne, int dirTwo, int pwm, int angle);
	void motorSetup();
	void move(double speed);
	void brake();
private:
	int dirOnePin;
	int dirTwoPin;
	int pwmPin;
	int motorAngle;
};

#endif
