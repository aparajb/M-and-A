#ifndef MOTORS_H_
#define MOTORS_H_

#include <Motor.h>
#include <Arduino.h>
#include <Common.h>

class Motors {
public:
	Motors();
	void motorsSetup();
	void brake();
	void updateDirection(double angle, double rotate, double speed);
	void moveDirection(double angle, double rotate, double speed);
private:
	Motor motor[MOTOR_NUM];
	int inOne[MOTOR_NUM] = {INONE_1, INONE_2, INONE_3};
	int inTwo[MOTOR_NUM] = {INTWO_1, INTWO_2, INTWO_3};
	int PWM[MOTOR_NUM] = {PWM_1, PWM_2, PWM_3};
	int motorAngles[MOTOR_NUM] = {MOTOR_ANGLE_0, MOTOR_ANGLE_1, MOTOR_ANGLE_2};
	double currentAngle = 0;
	double currentRotate = 0;
	double currentSpeed = 0;
	int values[MOTOR_NUM] = {0};
};


#endif
