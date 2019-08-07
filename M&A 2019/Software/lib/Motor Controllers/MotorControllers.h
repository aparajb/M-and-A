#ifndef MOTOR_CONTROLLERS_H
#define MOTOR_CONTROLLERS_H

#include <Arduino.h>
#include <Common.h>

class MotorControllers {
	public:
		MotorControllers() {}
		void init();
		void update(Movement movement);
	private:
		void move(float speed, uint8_t index);
		uint8_t inOne[MOTOR_NUM] = {INONE_0, INONE_1, INONE_2, INONE_3};
        uint8_t inTwo[MOTOR_NUM] = {INTWO_0, INTWO_1, INTWO_2, INTWO_3};
        uint8_t pwm[MOTOR_NUM] = {PWM_0, PWM_1, PWM_2, PWM_3};
		uint16_t motorAngle[MOTOR_NUM] = {MOTOR_ANGLE_0, MOTOR_ANGLE_1, MOTOR_ANGLE_2, MOTOR_ANGLE_3};
		float currentAngle;
		float currentRotate;
		float currentSpeed;
		float values[MOTOR_NUM] = {0};
};

#endif // MOTOR_CONTROLLERS_H