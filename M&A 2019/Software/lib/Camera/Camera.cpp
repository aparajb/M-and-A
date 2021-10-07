#include "Camera.h"

Camera::Camera() {}

void Camera::init() {
    Serial1.begin(CAMERA_BAUD);
}

void Camera::update(float heading, bool attackBlue) {
    if(Serial1.available() >= CAMERA_PACKET_NUM) {
        uint8_t firstByte = Serial1.read();
        uint8_t secondByte = Serial1.peek();
        if(firstByte == COMS_SYNC_BYTE && secondByte == COMS_SYNC_BYTE) {
            Serial1.read();
            int8_t yellowX = Serial1.read() - CENTRE_X;
            int8_t yellowY = Serial1.read() - CENTRE_Y;
            int8_t blueX = Serial1.read() - CENTRE_X;
            int8_t blueY = Serial1.read() - CENTRE_Y;
            int8_t orangeX = Serial1.read() - CENTRE_X;
            int8_t orangeY = Serial1.read() - CENTRE_Y;
            yellowGoal = Vect(yellowX, yellowY, false);
            yellowGoal.setPolar(goalPixeltoCM(yellowGoal.mag), floatMod(yellowGoal.arg - 90, 360.0));
            blueGoal = Vect(blueX, blueY, false);
            blueGoal.setPolar(goalPixeltoCM(blueGoal.mag), floatMod(blueGoal.arg - 90, 360.0));
            ball = Vect(orangeX, orangeY, false);
            ball.setPolar(ballPixeltoCM(ball.mag), floatMod(ball.arg - 90, 360.0));
            if((blueGoal.exists() && yellowGoal.exists() && blueGoal.mag < yellowGoal.mag) || (blueGoal.exists() && !yellowGoal.exists())) {
                robot = attackBlue ? Vect(ATTACK_X, ATTACK_Y, false) : Vect(DEFEND_X, DEFEND_Y, false);
                robot -= blueGoal;
            } else if(yellowGoal.exists()) {
                robot = attackBlue ? Vect(DEFEND_X, DEFEND_Y, false) : Vect(ATTACK_X, ATTACK_Y, false);
                robot -= yellowGoal;
            } else {
                robot = Vect();
            }
            Serial.print(robot.mag); Serial.print("\t");
            Serial.println(robot.arg);
        }
    }
}

float Camera::ballPixeltoCM(float dist) {
    return (dist != 0) ? 2.2796 * powf(10, -13) * expf(0.0552695 * (dist + 488.046)) + 8.06324 : 0;
}

float Camera::goalPixeltoCM(float dist) {
    return (dist != 0) ? 0.0162932 * expf(0.0594836 * (dist + 17.5461)) + 3.66889 : 0;
}