#include "Camera.h"

Camera::Camera() {}

void Camera::init() {
    Serial1.begin(CAMERA_BAUD);
}

void Camera::update() {
    if(Serial1.available() >= 8) {
        uint8_t firstByte = Serial1.read();
        uint8_t secondByte = Serial1.peek();
        if(firstByte == 234 && secondByte == 234) {
            Serial1.read();
            Serial1.read();
            Serial1.read();
            Serial1.read();
            Serial1.read();
            Serial1.read();
            Serial1.read();
            // uint8_t highByte = Serial1.read();
            // uint8_t lowByte = Serial1.read();
            // attackingGoalAngle = highByte << 8 | lowByte;
            // attackingGoalVisible = (attackingGoalAngle != 65535);
            // attackingGoalDistance = Serial1.read();
            // highByte = Serial1.read();
            // lowByte = Serial1.read();
            // defendingGoalDistance = Serial1.read();
            // defendingGoalAngle = highByte << 8 | lowByte;
            // defendingGoalVisible = (defendingGoalAngle != 65535);
            Serial.println(1000 / (millis() - previousTime));
            previousTime = millis();
        }
    }
}