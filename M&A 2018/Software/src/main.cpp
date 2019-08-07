#include <PixyI2C.h>
#include <tsops.h>
#include <LightSensors.h>
#include <IMU.h>
#include <Motors.h>
#include <PID.h>
#include <Arduino.h>
#include <I2C.h>
#include <SparkFun_VL53L1X_Arduino_Library.h>
#include <Timer.h>
// #include <Bluetooth.h>

PixyI2C pixy;
Tsops tsops;
LightSensors lights;
Motors motors;
IMU IMU;
PID headingPID(HEADING_KP, HEADING_KI, HEADING_KD, HEADING_MAX_CORRECTION);
PID goalTrackPID(CAMERA_KP, CAMERA_KI, CAMERA_KD, CAMERA_MAX_CORRECTION);
PID goalTrackWeakPID(CAMERA_WEAK_KP, CAMERA_WEAK_KI, CAMERA_WEAK_KD, CAMERA_WEAK_MAX_CORRECTION);
PID goalTrackDefendPID(CAMERA_DEFEND_KP, CAMERA_DEFEND_KI, CAMERA_DEFEND_KD, CAMERA_DEFEND_MAX_CORRECTION);
PID centreDistancePID(CENTRE_DISTANCE_KP, CENTRE_DISTANCE_KI, CENTRE_DISTANCE_KD);
PID defendSidewaysPID(DEFEND_SIDEWAYS_KP, DEFEND_SIDEWAYS_KI, DEFEND_SIDEWAYS_KD, DEFEND_SIDEWAYS_MAX_SPEED);
PID centreSidewaysPID(CENTRE_SIDEWAYS_KP, CENTRE_SIDEWAYS_KI, CENTRE_SIDEWAYS_KD);
Timer LEDTimer(((bool)DEFAULT_ROLE ? LED_BLINK_TIME_ATTACK : LED_BLINK_TIME_DEFEND));
Timer pixyTimer(PIXY_READ_RATE);
Timer switchTimer(BT_SWITCH_TIMER);
VL53L1X lrf;
// Bluetooth bluetooth(DEFAULT_ROLE);

DirSpeed finalMovement;
bool onField = true;
double fieldLineAngle = -1;
int fieldLineSize;
double goalAngle = 0;
bool goalVisible = false;
bool ledOn = false;
double lrfValue;
bool attacking = DEFAULT_ROLE;

void calculateOutAvoidance(DirSpeed move) {
    bool noLine = (lights.getLineDir() == -1);
    double lineDirection = noLine ? -1 : angleMap(lights.getLineDir() + IMU.getIMUHeading(), 360);
    if(onField) {
        if(!noLine) {
            fieldLineAngle = lineDirection;
            fieldLineSize = 1;
            onField = false;
        }
    } else {
        if(fieldLineSize == 3) {
            if(!noLine) {
                fieldLineAngle = angleMap(lineDirection + 180, 360);
                fieldLineSize = 2;
            }
        } else {
            if(noLine) {
                if(fieldLineSize == 1) {
                    onField = true;
                    fieldLineAngle = -1;
                    fieldLineSize = 0;
                } else {
                    fieldLineSize = 3;
                }
            } else {
                if(smallestAngleBetween(lineDirection, fieldLineAngle) <= 90) {
                    fieldLineAngle = lineDirection;
                    fieldLineSize = 1;
                } else {
                    fieldLineAngle = angleMap(lineDirection + 180, 360);
                    fieldLineSize = 2;
                }
            }
        }
    }
    if(!noLine) {
        finalMovement.direction = angleMap(fieldLineAngle + 180 - IMU.getIMUHeading(), 360);
        if(fieldLineSize == 1 && abs(finalMovement.direction - fieldLineAngle) < 60) {
            finalMovement.speed = 0;
        } else if(fieldLineSize == 2) {
            finalMovement.speed = abs(finalMovement.direction - fieldLineAngle) < 60 ? AVOID_SLOW_SPEED : AVOID_FAST_SPEED;
        }
    } else {
        if(fieldLineSize == 3) {
            finalMovement.direction = angleMap(fieldLineAngle + 180 - IMU.getIMUHeading(), 360);
            finalMovement.speed = abs(finalMovement.direction - fieldLineAngle) < 60 ? AVOID_SLOW_SPEED : AVOID_FAST_SPEED;
        }
    }
}

void calculateOrbit() {
    double ballAngleDifference = findSign(angleMap(tsops.getBallDir(), 180)) * fmin(90, 0.4 * pow(MATH_E, 0.15 * smallestAngleBetween(tsops.getBallDir(), 0)));
    double strengthFactor = constrain(tsops.getAvgStr() / BALL_CLOSE_STRENGTH, 0, 1);
    double distanceMultiplier = constrain((0.02 * strengthFactor * pow(MATH_E, 4.5 * strengthFactor)), 0, 1);
    double angleAddition = ballAngleDifference * distanceMultiplier;
    finalMovement.direction = angleMap(tsops.getBallDir() + angleAddition, 360);
    finalMovement.speed = ORBIT_SLOW_SPEED + (ORBIT_FAST_SPEED - ORBIT_SLOW_SPEED) * (1.0 - abs(angleAddition) / 90.0);
}

void calculateAttackingGoalAngle() {
    if(pixyTimer.timeHasPassed()) {
        int blocks = pixy.getBlocks();
        int goalIndex = -1;
        goalVisible = false;
        if(blocks != 0) {
            for(int i = 0; i < blocks; i++) {
                if(pixy.blocks[i].x > 160) {
                    goalVisible = true;
                    goalIndex = goalIndex == -1 ? i : goalIndex;
                }
            }
            goalAngle = ((PIXY_FRAME_HEIGHT / 2.0) - pixy.blocks[goalIndex].y) * MAX_ANGLING / (PIXY_FRAME_HEIGHT / 2.0);
        }
    }
    // goalVisible = false;
}

void calculateDefendingGoalAngle() {
    if(pixyTimer.timeHasPassed()) {
        int blocks = pixy.getBlocks();
        int goalIndex = -1;
        goalVisible = false;
        if(blocks != 0) {
            for(int i = 0; i < blocks; i++) {
                if(pixy.blocks[i].x < 160) {
                    goalVisible = true;
                    goalIndex = goalIndex == -1 ? i : goalIndex;
                }
            }
            goalAngle = -((PIXY_FRAME_HEIGHT / 2.0) - pixy.blocks[goalIndex].y) * MAX_ANGLING / (PIXY_FRAME_HEIGHT / 2.0);
        }
    }
    // goalVisible = false;
}

void calculateAttack() {
    calculateAttackingGoalAngle();
    double correction = IMU.getIMUHeading() > 180 ? angleMap((IMU.getIMUHeading() - 360), 180) : IMU.getIMUHeading();
    if(abs(angleMap(tsops.getBallDir() - 360, 180)) < 45) {
        correction = goalVisible ? -goalTrackPID.update(angleMap(correction + goalAngle, 180), 0) : -headingPID.update(angleMap(correction, 180), 0);
    } else {
        correction =  goalVisible ? -goalTrackWeakPID.update(angleMap(correction + goalAngle, 180), 0) : -headingPID.update(angleMap(correction, 180), 0);
    }
    calculateOrbit();
    calculateOutAvoidance(finalMovement);
    if(!tsops.getBallVisible()) {
        if(fieldLineAngle == -1) {
            finalMovement.speed = 0;
        }
    }
    motors.updateDirection(finalMovement.direction, correction, finalMovement.speed);
}

void calculateDefenseMovement() {
    double distanceMovement;
    double sidewaysMovement;
    bool surge = (lrfValue < 600);
    if(goalVisible) {
        if(tsops.getBallVisible()) {
            if(angleIsInside(270, 90, tsops.getBallDir())) {
                if(tsops.getAvgStr() > DEFEND_CHARGE_STRENGTH && angleIsInside(335, 25, tsops.getBallDir()) && surge) {
                    // attacking = true;
                    // LEDTimer.updateTimerDuration(LED_BLINK_TIME_ATTACK);
                    calculateOrbit();
                } else {
                    distanceMovement =  -centreDistancePID.update(lrfValue, DEFEND_GOAL_DISTANCE);
                    sidewaysMovement = abs(angleMap(tsops.getBallDir() - 360, 180)) > DEFEND_SMALL_ANGLE ? defendSidewaysPID.update(angleMap(tsops.getBallDir() - 360, 180), 0) : 0;
                    finalMovement.direction = angleMap(RADIANS_TO_DEGREES * atan2(sidewaysMovement, distanceMovement), 360);
                    finalMovement.speed = sqrt(distanceMovement * distanceMovement + sidewaysMovement * sidewaysMovement);
                }
            } else {
                calculateOrbit();
            }
        } else {
            distanceMovement =  -centreDistancePID.update(lrfValue, DEFEND_GOAL_DISTANCE);
            sidewaysMovement = centreSidewaysPID.update(angleMap(IMU.getIMUHeading() - 360, 180), 0);
            finalMovement.direction = angleMap(RADIANS_TO_DEGREES * atan2(sidewaysMovement, distanceMovement), 360);
            finalMovement.speed = distanceMovement;
        }
    } else if(tsops.getBallVisible()) {
        if(angleIsInside(270, 90, tsops.getBallDir())) {
            distanceMovement = angleIsInside(345, 15, IMU.getIMUHeading()) ? -centreDistancePID.update(lrfValue, DEFEND_BLOCK_DISTANCE) : 0;
            sidewaysMovement = defendSidewaysPID.update(angleMap(tsops.getBallDir() - 360, 180), 0);
            finalMovement.direction = angleMap(RADIANS_TO_DEGREES * atan2(sidewaysMovement, distanceMovement), 360);
            finalMovement.speed = sqrt(distanceMovement * distanceMovement + sidewaysMovement * sidewaysMovement);
        } else {
            calculateOrbit();
        }
    } else {
        distanceMovement = -centreDistancePID.update(lrfValue, DEFEND_BLOCK_DISTANCE);
        finalMovement.direction = angleMap(RADIANS_TO_DEGREES * atan2(0, distanceMovement), 360);
        finalMovement.speed = distanceMovement;
    }
}

void calculateDefense() {
    calculateDefendingGoalAngle();
    double correction = IMU.getIMUHeading() > 180 ? angleMap((IMU.getIMUHeading() - 360), 180) : IMU.getIMUHeading();
    correction = goalVisible ? -goalTrackDefendPID.update(angleMap(correction + goalAngle, 180), 0) : -headingPID.update(angleMap(correction, 180), 0);
    lrfValue = lrf.getDistance();
    if(goalVisible) {
        if(abs(correction + goalAngle) > 150) {
            if(lrfValue < DEFEND_BLOCK_DISTANCE) {
                lrfValue = DEFEND_GOAL_DISTANCE;
            }
        }
    }
    calculateDefenseMovement();
    calculateOutAvoidance(finalMovement);
    motors.updateDirection(finalMovement.direction, correction, finalMovement.speed);
}

void move() {
    if(attacking) {
        calculateAttack();
    } else {
        calculateDefense();
    }
}

// void decideRole() {
//     if(isConnected) {
//         if(!attacking) {
//             if(angleIsInside(270, 90, bluetooth.otherData.ballDir)) {
//                 if(tsops.getAvgStr() > bluetooth.otherData.ballStr) {
//                     if(switchTimer.timeHasPassed()) {
//                         attacking = true;
//                         LEDTimer.updateTimerDuration(LED_BLINK_TIME_ATTACK);
//                     }
//                 }
//             }
//         } else if(bluetooth.otherData.role) {
//             if(switchTimer.timeHasPassed()) {
//                 attacking = false;
//                 LEDTimer.updateTimerDuration(LED_BLINK_TIME_DEFEND);
//             }
//         }
//     } else {
//         attacking = false;
//     }
// }

void setup() {
    pinMode(LED_PIN, OUTPUT);
    digitalWrite(LED_PIN, HIGH);
    Serial.begin(9600);
    // delay(3000);
    initWire();
    IMU.IMUSetup();
    IMU.calibrate();
    IMU.findDrift();
    tsops.tsopsSetup();
    lights.lightSensorsSetup();
    IMU.driftPrevious = millis();
    motors.motorsSetup();
    motors.brake();
    pixy.init();
    #if !DEFAULT_ROLE
        lrf.begin();
        lrf.setDistanceMode(2);
    #endif
    digitalWrite(LED_PIN, LOW);
}

void loop() {
    Serial.println(0);
    tsops.read();
    Serial.println(1);
    lights.updateLineLocation();
    Serial.println(2);
    IMU.updateGyro();
    Serial.println(3);
    // decideRole();
    move();
    Serial.println(4);
    if(LEDTimer.timeHasPassed()) {
        digitalWrite(LED_PIN, ledOn);
        ledOn = !ledOn;
    }
    // BluetoothData sendData = {tsops.getBallDir(), tsops.getAvgStr(), attacking};
    // bluetooth.update(sendData);
}
