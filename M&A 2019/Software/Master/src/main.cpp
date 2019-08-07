#include <MPU.h>
#include <BluetoothModule.h>
#include <Camera.h>
#include <LSMultiplexer.h>
#include <MotorControllers.h>
#include <PID.h>
#include <TSSPs.h>

MPU imu;
BluetoothModule bluetooth;
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
TSSPs tssps;

Movement calculateMove(float vertical, float horizontal) {
    Movement sendVal;
    sendVal.direction = floatMod(RADIANS_TO_DEGREES * atan2f(horizontal, vertical), 360);
    if(camera.defendingGoalVisible && !bluetooth.thisData.role && tssps.ballVisible) {
        sendVal.correction = -defendGoalTrackPID.update(camera.defendingGoalAngle, 180);
    } else {
        sendVal.correction = headingPID.update((imu.heading > 180 ? imu.heading - 360 : imu.heading), 0);
    }
    sendVal.speed = sqrtf(vertical * vertical + horizontal * horizontal);
    return sendVal;
}

Movement calculateAttackMovement() {
    Movement sendVal;
    if(tssps.ballVisible) {
        sendVal.direction = floatMod(tssps.ballDir + tssps.calculateAngleAddition(), 360);
        if(camera.attackingGoalVisible && bluetooth.thisData.role) {
            sendVal.correction = -attackGoalTrackPID.update((camera.attackingGoalAngle > 180 ? camera.attackingGoalAngle - 360 : camera.attackingGoalAngle), 0);
        } else {
            sendVal.correction = headingPID.update((imu.heading > 180 ? imu.heading - 360 : imu.heading), 0);
        }
        if(tssps.ballStr > DEFEND_CHARGE_STRENGTH && angleIsInside(0, 5, tssps.ballDir)) {
            sendVal.speed = ORBIT_FAST_SPEED;
        } else {
            sendVal.speed = ORBIT_SLOW_SPEED + (ORBIT_MEDIUM_SPEED - ORBIT_SLOW_SPEED) * (1.0 - abs(tssps.angleAddition) / 90.0);
        }
        return sendVal;
    } else if(camera.defendingGoalVisible) {
        return calculateMove(centreDistancePID.update(camera.defendingGoalDistance, ATTACK_IDLE_DISTANCE), 0);
    }
    return calculateMove(0, 0);
}

Movement calculateDefenseMovement() {
    if(tssps.ballVisible) {
        if(tssps.ballStr > DEFEND_CHARGE_STRENGTH) {
            if(angleIsInside(345, 15, tssps.ballDir)) {
                if(bluetooth.isConnected) {
                    bluetooth.isSwitching = true;
                }
                if(camera.defendingGoalVisible && camera.defendingGoalDistance < SURGE_DISTANCE) {
                    return calculateAttackMovement();
                }
            }
        }
        if(angleIsInside(270, 90, tssps.ballDir)) {
            float sideways = tssps.ballDir > 180 ? tssps.ballDir - 360 : tssps.ballDir;
            float distance = camera.defendingGoalVisible ? camera.defendingGoalDistance : DEFEND_GOAL_DISTANCE;
            return calculateMove(distancePID.update(distance, DEFEND_GOAL_DISTANCE), sidewaysPID.update(sideways, 0));
        }
        return calculateAttackMovement();
    } else if(camera.defendingGoalVisible) {
        return calculateMove(centreDistancePID.update(camera.defendingGoalDistance, DEFEND_GOAL_DISTANCE), 0);
    }
    return calculateMove(0, 0);
}

void updateMovement() {
    bluetooth.thisData.role = true;
    Movement finalMovement = bluetooth.thisData.role ? lightSensors.calculateOutAvoidance(imu.heading, calculateAttackMovement()) : lightSensors.calculateOutAvoidance(imu.heading, calculateDefenseMovement());
    motors.update(finalMovement);
}

void setup() {
    delay(500);
    imu.init();
    camera.init();
    bluetooth.init();
    lightSensors.init();
    motors.init();
    tssps.init();
}

void loop() {
    imu.update();
    camera.update();
    lightSensors.update(imu.heading);
    tssps.update();
    updateMovement();
    bluetooth.update(tssps.ballDir, tssps.ballStr);
}