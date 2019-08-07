#include "Motor.h"

Motor::Motor(int dirOne, int dirTwo, int pwm, int angle) {
	dirOnePin = dirOne;
	dirTwoPin = dirTwo;
	pwmPin = pwm;
	motorAngle = angle;
}

void Motor::motorSetup() {
	pinMode(dirOnePin, OUTPUT);
	pinMode(dirTwoPin, OUTPUT);
	pinMode(pwmPin, OUTPUT);
	analogWriteFrequency(pwmPin, 940);
}

void Motor::move(double speed) {
	int dirOneWrite = 0;
	int dirTwoWrite = 0;
	int pwmWrite;
	if(speed != 0) {
		pwmWrite = min(abs(speed), 255);
		dirOneWrite = speed > 0 ? 1:0;
		dirTwoWrite = 1 - dirOneWrite;
	}
	digitalWrite(dirOnePin, dirOneWrite);
	digitalWrite(dirTwoPin, dirTwoWrite);
	analogWrite(pwmPin, pwmWrite);
}

void Motor::brake() {
	digitalWrite(dirOnePin, HIGH);
	digitalWrite(dirTwoPin, HIGH);
	digitalWrite(pwmPin, HIGH);
}
