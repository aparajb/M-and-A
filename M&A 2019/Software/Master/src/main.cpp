#include <MPU.h>
#include <Camera.h>
#include <LSMultiplexer.h>
#include <MotorControllers.h>
#include <PID.h>

MPU imu;
Camera camera;
LSMultiplexer lightSensors;
MotorControllers motors;
PID distancePID(DISTANCE_KP, DISTANCE_KI, DISTANCE_KD, DISTANCE_MAX_SPEED);
PID centreDistancePID(CENTRE_DISTANCE_KP, CENTRE_DISTANCE_KI, CENTRE_DISTANCE_KD, CENTRE_DISTANCE_MAX_SPEED);
PID sidewaysPID(SIDEWAYS_KP, SIDEWAYS_KI, SIDEWAYS_KD, SIDEWAYS_MAX_SPEED);
PID centreSidewaysPID(CENTRE_SIDEWAYS_KP, CENTRE_SIDEWAYS_KI, CENTRE_SIDEWAYS_KD, CENTRE_SIDEWAYS_MAX_SPEED);
PID headingPID(HEADING_KP, HEADING_KI, HEADING_KD, HEADING_MAX_CORRECTION);
PID attackGoalTrackPID(ATTACK_GOAL_TRACK_KP, ATTACK_GOAL_TRACK_KI, ATTACK_GOAL_TRACK_KD, ATTACK_GOAL_TRACK_MAX_CORRECTION);
PID defendGoalTrackPID(DEFEND_GOAL_TRACK_KP, DEFEND_GOAL_TRACK_KI, DEFEND_GOAL_TRACK_KD, DEFEND_GOAL_TRACK_MAX_CORRECTION);

Movement calculateMove(float vertical, float horizontal) {
    Movement sendVal;
    sendVal.direction = floatMod(RADIANS_TO_DEGREES * atan2f(horizontal, vertical), 360);
    if(camera.robot.exists() && camera.ball.exists()) {
        Vect goal = Vect(DEFEND_X, DEFEND_Y, false) - camera.robot;
        float diff = floatMod(450 - imu.heading, 360.0) - floatMod(goal.arg + 180, 360.0);
        if(diff > 180) {
            diff -= 360;
        } else if(diff < -180) {
            diff += 360;
        }
        // correction = defendTrack.update(diff, 0);
        // Vect goal = Vect(DEFEND_X, DEFEND_Y, false) - camera.robot;
        sendVal.correction = -defendGoalTrackPID.update(diff, 0);
        // sendVal.correction = -defendGoalTrackPID.update(camera.defendingGoalAngle, 180);
    } else {
        sendVal.correction = headingPID.update((imu.heading > 180 ? imu.heading - 360 : imu.heading), 0);
    }
    sendVal.speed = sqrtf(vertical * vertical + horizontal * horizontal);
    return sendVal;
}

Movement calculateAttackMovement() {
    Movement sendVal;
    if(camera.ball.exists()) {
        float dir = camera.ball.arg > 270 ? camera.ball.arg - 450 : camera.ball.arg - 90;
        float ballAngleDifference = findSign(dir) * fmin(90, 0.04 * expf(0.15 * abs(dir)));
        float distMulti = max(0, -0.04 * camera.ball.mag + 2);
        float angleAdd = distMulti * ballAngleDifference;
        sendVal.direction = floatMod(450 - camera.ball.arg - angleAdd, 360.0);
        sendVal.correction = headingPID.update((imu.heading > 180 ? imu.heading - 360 : imu.heading), 0);
        if(camera.ball.mag < 30 && angleIsInside(70, 110, camera.ball.arg)) {
            sendVal.speed = ORBIT_FAST_SPEED;
        } else {
            sendVal.speed = ORBIT_SLOW_SPEED + (ORBIT_MEDIUM_SPEED - ORBIT_SLOW_SPEED) * (1.0 - abs(angleAdd) / 90.0);
        }
        return sendVal;
    // } else if(camera.robot.exists) {
    //     return calculateMove(centreDistancePID.update(-40 - cam.robot.jcamera.defendingGoalDistance, ATTACK_IDLE_DISTANCE), 0);
    }
    return calculateMove(0, 0);
}

Movement calculateDefenseMovement() {
    if(camera.ball.exists()) {
    //     if(camera.ball.mag < 30) {
    //         if(angleIsInside(70, 110, camera.ball.arg)) {
    //             if(camera.robot.exists() && camera.robot.j < -30) {
    //                 // return calculateAttackMovement();
    //             }
    //         }
    //     }
        if(angleIsInside(0, 180, camera.ball.arg)) {
            Vect temp = Vect(DEFEND_X, DEFEND_Y, false) - camera.robot;
            // float distance = camera.robot.exists() ? -60 - camera.robot.j : 0;
            return calculateMove(centreDistancePID.update(temp.mag, 40), sidewaysPID.update(90 - camera.ball.arg, 0));
        }
    //     return calculateAttackMovement();
    } else if(camera.robot.exists()) {
        Vect temp = Vect(DEFEND_X, DEFEND_Y, false) - camera.robot;
        return calculateMove(centreDistancePID.update(temp.mag, 40), -camera.robot.i);
    }
    return calculateMove(0, 0);
}

void setup() {
    delay(500);
    imu.init();
    camera.init();
    lightSensors.init();
    motors.init();
}

void loop() {
    imu.update();
    camera.update(imu.heading, true);
    lightSensors.update(imu.heading);
    Movement finalMovement = lightSensors.calculateOutAvoidance(imu.heading, calculateDefenseMovement());
    motors.update(finalMovement);
}