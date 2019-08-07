#include "MotorControllers.h"

void MotorControllers::init() {
	for(uint8_t i = 0; i < MOTOR_NUM; i++) {
        pinMode(inOne[i], OUTPUT);
        pinMode(inTwo[i], OUTPUT);
        pinMode(pwm[i], OUTPUT);
        digitalWrite(inOne[i], HIGH);
        digitalWrite(inTwo[i], HIGH);
        analogWrite(pwm[i], 0);
        // analogWriteFrequency(pwm[i], PWM_FREQUENCY);
	}
}

void MotorControllers::move(float speed, uint8_t index) {
	bool dirOneWrite = true;
	bool dirTwoWrite = true;
	uint8_t pwmWrite = 0;
	if(speed * 2.55 != 0) {
		pwmWrite = min(abs(speed * 2.55), 255);
		dirOneWrite = speed > 0;
		dirTwoWrite = !dirOneWrite;
	}
	digitalWrite(inOne[index], dirOneWrite);
	digitalWrite(inTwo[index], dirTwoWrite);
    analogWrite(pwm[index], pwmWrite);
}

void MotorControllers::update(Movement movement) {
    if(movement.direction != currentAngle || movement.correction != currentRotate || movement.speed != currentSpeed) {
        float values[MOTOR_NUM] = {movement.correction, movement.correction, movement.correction, movement.correction};
		if(movement.speed != 0) {
            for(uint8_t i = 0; i < MOTOR_NUM; i++) {
                values[i] = cos(DEGREES_TO_RADIANS * (motorAngle[i] + 90 - movement.direction));
            }
            float highestValue = max(max(max(abs(values[0]), abs(values[1])), abs(values[2])), abs(values[3]));
            for(uint8_t i = 0; i < MOTOR_NUM; i++) {
                values[i] = values[i] * movement.speed / highestValue + movement.correction;
            }
		    highestValue = max(max(max(abs(values[0]), abs(values[1])), abs(values[2])), abs(values[3]));
		    for(uint8_t i = 0; i < MOTOR_NUM; i++) {
			    values[i] *= movement.speed / highestValue;
		    }
        }
        for(uint8_t i = 0; i < MOTOR_NUM; i++) {
            move(values[i], i);
        }
        currentAngle = movement.direction;
        currentRotate = movement.correction;
    	currentSpeed = movement.speed;
    }
}