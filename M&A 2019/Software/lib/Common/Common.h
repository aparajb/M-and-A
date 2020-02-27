#ifndef COMMON_H_
#define COMMON_H_

#include <math.h>
#include <Arduino.h>
#include <Pins.h>
#include <EEPROM.h>

#define VOLTAGE_DIVIDER 75
#define LOW_BATTERY_VOLTAGE 11.1

#define DEGREES_TO_RADIANS 0.017453292519943295769236907684886
#define RADIANS_TO_DEGREES 57.295779513082320876798154814105

#define TSSP_NUM 24
#define TSSP_READ_NUM 256
#define TSSP_INTERVAL_ANGLE 11.25
#define BALL_CLOSE_STRENGTH 140

#define TSSP_X_0 0
#define TSSP_X_1 (sqrtf(6) - sqrtf(2)) / 4
#define TSSP_X_2 0.5
#define TSSP_X_3 sqrtf(2) / 2
#define TSSP_X_4 sqrtf(3) / 2
#define TSSP_X_5 (sqrtf(6) + sqrtf(2)) / 4
#define TSSP_X_6 1
#define TSSP_X_7 (sqrtf(6) + sqrtf(2)) / 4
#define TSSP_X_8 sqrtf(3) / 2
#define TSSP_X_9 sqrtf(2) / 2
#define TSSP_X_10 0.5
#define TSSP_X_11 (sqrtf(6) - sqrtf(2)) / 4
#define TSSP_X_12 0
#define TSSP_X_13 -(sqrtf(6) - sqrtf(2)) / 4
#define TSSP_X_14 -0.5
#define TSSP_X_15 -sqrtf(2) / 2
#define TSSP_X_16 -sqrtf(3) / 2
#define TSSP_X_17 -(sqrtf(6) + sqrtf(2)) / 4
#define TSSP_X_18 -1
#define TSSP_X_19 -(sqrtf(6) + sqrtf(2)) / 4
#define TSSP_X_20 -sqrtf(3) / 2
#define TSSP_X_21 -sqrtf(2) / 2
#define TSSP_X_22 -0.5
#define TSSP_X_23 (sqrtf(6) - sqrtf(2)) / 4

#define TSSP_Y_0 1
#define TSSP_Y_1 (sqrtf(6) + sqrtf(2)) / 4
#define TSSP_Y_2 sqrtf(3) / 2
#define TSSP_Y_3 sqrtf(2) / 2
#define TSSP_Y_4 0.5
#define TSSP_Y_5 (sqrtf(6) - sqrtf(2)) / 4
#define TSSP_Y_6 0
#define TSSP_Y_7 -(sqrtf(6) - sqrtf(2)) / 4
#define TSSP_Y_8 -0.5
#define TSSP_Y_9 -sqrtf(2) / 2
#define TSSP_Y_10 -sqrtf(3) / 2
#define TSSP_Y_11 -(sqrtf(6) + sqrtf(2)) / 4
#define TSSP_Y_12 -1
#define TSSP_Y_13 -(sqrtf(6) + sqrtf(2)) / 4
#define TSSP_Y_14 -sqrtf(3) / 2
#define TSSP_Y_15 -sqrtf(2) / 2
#define TSSP_Y_16 -0.5
#define TSSP_Y_17 -(sqrtf(6) - sqrtf(2)) / 4
#define TSSP_Y_18 0
#define TSSP_Y_19 (sqrtf(6) - sqrtf(2)) / 4
#define TSSP_Y_20 0.5
#define TSSP_Y_21 sqrtf(2) / 2
#define TSSP_Y_22 sqrtf(3) / 2
#define TSSP_Y_23 (sqrtf(6) + sqrtf(2)) / 4

#define ROBOT_A_TSSP_ADDITION_0 0
#define ROBOT_A_TSSP_ADDITION_1 0
#define ROBOT_A_TSSP_ADDITION_2 0
#define ROBOT_A_TSSP_ADDITION_3 0
#define ROBOT_A_TSSP_ADDITION_4 0
#define ROBOT_A_TSSP_ADDITION_5 0
#define ROBOT_A_TSSP_ADDITION_6 0
#define ROBOT_A_TSSP_ADDITION_7 0
#define ROBOT_A_TSSP_ADDITION_8 0
#define ROBOT_A_TSSP_ADDITION_9 0
#define ROBOT_A_TSSP_ADDITION_10 0
#define ROBOT_A_TSSP_ADDITION_11 0
#define ROBOT_A_TSSP_ADDITION_12 0
#define ROBOT_A_TSSP_ADDITION_13 0
#define ROBOT_A_TSSP_ADDITION_14 0
#define ROBOT_A_TSSP_ADDITION_15 0
#define ROBOT_A_TSSP_ADDITION_16 0
#define ROBOT_A_TSSP_ADDITION_17 0
#define ROBOT_A_TSSP_ADDITION_18 0
#define ROBOT_A_TSSP_ADDITION_19 0
#define ROBOT_A_TSSP_ADDITION_20 10
#define ROBOT_A_TSSP_ADDITION_21 15
#define ROBOT_A_TSSP_ADDITION_22 20
#define ROBOT_A_TSSP_ADDITION_23 20
#define ROBOT_B_TSSP_ADDITION_0 20
#define ROBOT_B_TSSP_ADDITION_1 0
#define ROBOT_B_TSSP_ADDITION_2 0
#define ROBOT_B_TSSP_ADDITION_3 0
#define ROBOT_B_TSSP_ADDITION_4 0
#define ROBOT_B_TSSP_ADDITION_5 0
#define ROBOT_B_TSSP_ADDITION_6 0
#define ROBOT_B_TSSP_ADDITION_7 0
#define ROBOT_B_TSSP_ADDITION_8 0
#define ROBOT_B_TSSP_ADDITION_9 0
#define ROBOT_B_TSSP_ADDITION_10 0
#define ROBOT_B_TSSP_ADDITION_11 0
#define ROBOT_B_TSSP_ADDITION_12 0
#define ROBOT_B_TSSP_ADDITION_13 0
#define ROBOT_B_TSSP_ADDITION_14 0
#define ROBOT_B_TSSP_ADDITION_15 0
#define ROBOT_B_TSSP_ADDITION_16 0
#define ROBOT_B_TSSP_ADDITION_17 0
#define ROBOT_B_TSSP_ADDITION_18 0
#define ROBOT_B_TSSP_ADDITION_19 0
#define ROBOT_B_TSSP_ADDITION_20 10
#define ROBOT_B_TSSP_ADDITION_21 10
#define ROBOT_B_TSSP_ADDITION_22 15
#define ROBOT_B_TSSP_ADDITION_23 20

#define MOTOR_NUM 4
#define ORBIT_FAST_SPEED 50
#define ORBIT_MEDIUM_SPEED 40
#define ORBIT_SLOW_SPEED 30
#define AVOID_FAST_SPEED 100
#define AVOID_SLOW_SPEED 100
#define PWM_FREQUENCY 40000
#define ORBIT_SLOW_RANGE 700

#define HEADING_KP 0.5
#define HEADING_KI 0
#define HEADING_KD 0.05
#define HEADING_MAX_CORRECTION 100
#define DEFEND_GOAL_TRACK_KP 3
#define DEFEND_GOAL_TRACK_KI 0
#define DEFEND_GOAL_TRACK_KD 2
#define DEFEND_GOAL_TRACK_MAX_CORRECTION 100
#define ATTACK_GOAL_TRACK_KP 1
#define ATTACK_GOAL_TRACK_KI 0
#define ATTACK_GOAL_TRACK_KD 0.25
#define ATTACK_GOAL_TRACK_MAX_CORRECTION 100
#define SIDEWAYS_KP -2
#define SIDEWAYS_KI 0
#define SIDEWAYS_KD 0
#define SIDEWAYS_MAX_SPEED 100
#define CENTRE_DISTANCE_KP 1
#define CENTRE_DISTANCE_KI 0
#define CENTRE_DISTANCE_KD 0
#define CENTRE_DISTANCE_MAX_SPEED 30
#define DISTANCE_KP 3
#define DISTANCE_KI 0
#define DISTANCE_KD 0
#define DISTANCE_MAX_SPEED 100
#define CENTRE_SIDEWAYS_KP 0.1
#define CENTRE_SIDEWAYS_KI 0
#define CENTRE_SIDEWAYS_KD 0
#define CENTRE_SIDEWAYS_MAX_SPEED 30

#define CAMERA_BAUD 115200
#define CAMERA_PACKET_NUM 8
#define CAMERA_START_BYTE 255

#define LS_NUM 32
#define LS_CALIBRATE_COUNT 10
#define LS_DEFAULT_THRESHOLD 150
#define LS_BUFFER 300
#define LS_INTERVAL_ANGLE 11.25
#define LS_BIG_SIZE 0.75
#define LS_MEDIUM_SIZE 0.5
#define LS_SMALL_SIZE 0.25
#define LS_AVOID_FAST 100
#define LS_AVOID_MEDIUM 40
#define LS_AVOID_ANGLE 45

#define CAMERA_VIEW_WIDTH 160
#define CAMERA_VIEW_HEIGHT 120

#define SURGE_DISTANCE 50
#define DEFEND_CHARGE_STRENGTH 180
#define DEFEND_NORMAL_DISTANCE 450
#define ATTACK_NORMAL_DISTANCE 550
#define DEFEND_GOAL_DISTANCE 50
#define ATTACK_IDLE_DISTANCE 40

#define BT_PACKAGE_NUM 6
#define BT_START_BYTE 255
#define BT_CONNECTED_TIMER 1000
#define BT_SEND_TIMER 10
#define BT_SWITCH_TIMER 4000
#define SWITCH_STRENGTH_CONST 40

#define LRF_NUM 4

#define MPU_CALIBRATION_COUNT 20
#define MPU_CALIBRATION_TIME 50
#define MPU9250_ADDRESS 0x68
#define MAG_ADDRESS 0x0C
#define GYRO_FULL_SCALE_250_DPS 0x00
#define GYRO_FULL_SCALE_500_DPS 0x08
#define GYRO_FULL_SCALE_1000_DPS 0x10
#define GYRO_FULL_SCALE_2000_DPS 0x18
#define ACC_FULL_SCALE_2_G 0x00
#define ACC_FULL_SCALE_4_G 0x08
#define ACC_FULL_SCALE_8_G 0x10
#define ACC_FULL_SCALE_16_G 0x18

#define ARRAYSHIFTDOWN(a, lower, upper){          \
	if (upper == (sizeof(a)/sizeof(a[0])) - 1){   \
		for (int q = upper - 1; q >= lower; q--){ \
			*(a + q + 1) = *(a + q); }            \
	} else{                                       \
		for (int q = upper; q >= lower; q--){     \
			*(a + q + 1) = *(a + q); }}}

float angleMap(float angle, float max);
int8_t findSign(float value);
float floatMod(float x, float m);
float angleBetween(float angleCounterClockwise, float angleClockwise);
float smallestAngleBetween(float angleCounterClockwise, float angleClockwise);
float midAngleBetween(float angleCounterClockwise, float angleClockwise);
uint8_t mod(int8_t x, int8_t m);
bool angleIsInside(float angleBoundCounterClockwise, float angleBoundClockwise, float angleCheck);

struct Movement {
	float direction;
	float correction;
	float speed;
};
struct Vector3D {
	float x;
	float y;
	float z;
};
struct BluetoothData {
	uint16_t ballDir;
	uint8_t ballStr;
	bool role;
};

#endif // COMMON_H
