#include <math.h>
#include <Arduino.h>

#ifndef COMMON_H_
#define COMMON_H_

////==========DEFINES==========////

//-----General-----//
#define WHITE true
#define LED_PIN 13
#define ATTACK 1
#define DEFENSE 0
#define DEFAULT_ROLE !WHITE
#define LED_BLINK_TIME_DEFEND 800
#define LED_BLINK_TIME_ATTACK 200

//-----Math-----//
#define DEGREES_TO_RADIANS 0.017453292519943295769236907684886
#define RADIANS_TO_DEGREES 57.295779513082320876798154814105
#define MATH_E 2.7182818284590452353602874713527

//-----Compass-----//
#define DRIFT_DELAY 100
#define IMU_CALIBRATION_COUNT 20
#define IMU_CALIBRATION_TIME 50

//-----Tsops-----//

//--General--//
#define TSOP_NUM 12
#define TSOP_MAX_IGNORE 256
#define TSOP_MIN_IGNORE 0
#define TSOP_READ_NUM 255
#if WHITE
	#define BALL_CLOSE_STRENGTH 160
	#define BALL_STR_MULTI 1
#else
	#define BALL_CLOSE_STRENGTH 145
	#define BALL_STR_MULTI 1
#endif

//--Angles--//
#define TSOP_ANGLE_0 0
#define TSOP_ANGLE_1 30
#define TSOP_ANGLE_2 60
#define TSOP_ANGLE_3 90
#define TSOP_ANGLE_4 120
#define TSOP_ANGLE_5 150
#define TSOP_ANGLE_6 180
#define TSOP_ANGLE_7 210
#define TSOP_ANGLE_8 240
#define TSOP_ANGLE_9 270
#define TSOP_ANGLE_10 300
#define TSOP_ANGLE_11 330

//--Pins--//
#define TSOP_PIN_0 54
#define TSOP_PIN_1 55
#define TSOP_PIN_2 56
#define TSOP_PIN_3 52
#define TSOP_PIN_4 51
#define TSOP_PIN_5 42
#define TSOP_PIN_6 43
#define TSOP_PIN_7 44
#define TSOP_PIN_8 57
#define TSOP_PIN_9 53
#define TSOP_PIN_10 41
#define TSOP_PIN_11 40

//--I values--//
#define TSOP_X_0 1
#define TSOP_X_1 sqrt(3) / 2
#define TSOP_X_2 0.5
#define TSOP_X_3 0
#define TSOP_X_4 -0.5
#define TSOP_X_5 sqrt(3) / -2
#define TSOP_X_6 -1
#define TSOP_X_7 sqrt(3) / -2
#define TSOP_X_8 -0.5
#define TSOP_X_9 0
#define TSOP_X_10 0.5
#define TSOP_X_11 sqrt(3) / 2

//--J Values--//
#define TSOP_Y_0 0
#define TSOP_Y_1 0.5
#define TSOP_Y_2 sqrt(3) / 2
#define TSOP_Y_3 1
#define TSOP_Y_4 sqrt(3) / 2
#define TSOP_Y_5 0.5
#define TSOP_Y_6 0
#define TSOP_Y_7 -0.5
#define TSOP_Y_8 sqrt(3) / -2
#define TSOP_Y_9 -1
#define TSOP_Y_10 sqrt(3) / -2
#define TSOP_Y_11 -0.5

//-----Motors-----//

//--General--//
#define MOTOR_NUM 3

#define AVOID_FAST_SPEED 255
#define AVOID_MEDIUM_SPEED 160
#define AVOID_SLOW_SPEED 100
#define GOALIE_FIND_GOAL_SPEED 100
#define ORBIT_FAST_SPEED 255
#if WHITE
	#define ORBIT_SLOW_SPEED 160
#else
	#define ORBIT_SLOW_SPEED 255
#endif

#define MOTOR_0_SCALE 1
#define MOTOR_1_SCALE 1
#define MOTOR_2_SCALE 1

//--Pin Values--//
#define PWM_1 5
#define INONE_1 47
#define INTWO_1 46

#define PWM_2 6
#define INONE_2 30
#define INTWO_2 29

#define PWM_3 2
#define INONE_3 24
#define INTWO_3 25

//--Angles--//
#define MOTOR_ANGLE_0 300
#define MOTOR_ANGLE_1 180
#define MOTOR_ANGLE_2 60

//-----PID-----//
#define HEADING_KP 4.5
#define HEADING_KI 0
#define HEADING_KD 0.52
#define HEADING_MAX_CORRECTION 255

#define CAMERA_KP 1
#define CAMERA_KI 0
#define CAMERA_KD 1.5
#define CAMERA_MAX_CORRECTION 255

#define CAMERA_WEAK_KP 0.3
#define CAMERA_WEAK_KI 0
#define CAMERA_WEAK_KD 0
#define CAMERA_WEAK_MAX_CORRECTION 180

#define CAMERA_DEFEND_KP 2
#define CAMERA_DEFEND_KI 0
#define CAMERA_DEFEND_KD 3
#define CAMERA_DEFEND_MAX_CORRECTION 255

#define DEFEND_SIDEWAYS_KP -8.8
#define DEFEND_SIDEWAYS_KI 0.0
#define DEFEND_SIDEWAYS_KD 0.05
#define DEFEND_SIDEWAYS_MAX_SPEED 255

#define CENTRE_DISTANCE_KP -0.4
#define CENTRE_DISTANCE_KI 0
#define CENTRE_DISTANCE_KD 0

#define CENTRE_SIDEWAYS_KP -2
#define CENTRE_SIDEWAYS_KI 0
#define CENTRE_SIDEWAYS_KD 0

//-----Light Sensors-----//

//--General--//
#define LS_NUM 16
#define LS_CALIBRATE_COUNT 10
#define LS_DEFAULT_THRESHOLD 200
#define LS_BUFFER 200
#define LS_INTERVAL_ANGLE 22.5

#if WHITE
	#define BROKEN_LIGHT_SENSOR 5
#else
	#define BROKEN_LIGHT_SENSOR 4
#endif

//--Pins--//
#define LS_0 A7
#define LS_1 A6
#define LS_2 A10
#define LS_3 A11
#define LS_4 A12
#define LS_5 A13
#define LS_6 A3
#define LS_7 A2
#define LS_8 A1
#define LS_9 A0
#define LS_10 A22
#define LS_11 A21
#define LS_12 A24
#define LS_13 A23
#define LS_14 A9
#define LS_15 A8

//--Angles--//

// With PCB
#define LS_ANGLE_0 0
#define LS_ANGLE_1 22.5
#define LS_ANGLE_2 45
#define LS_ANGLE_3 67.5
#define LS_ANGLE_4 90
#define LS_ANGLE_5 112.5
#define LS_ANGLE_6 135
#define LS_ANGLE_7 157.5
#define LS_ANGLE_8 180
#define LS_ANGLE_9 202.5
#define LS_ANGLE_10 225
#define LS_ANGLE_11 247.5
#define LS_ANGLE_12 270
#define LS_ANGLE_13 292.5
#define LS_ANGLE_14 315
#define LS_ANGLE_15 337.5

//--I Values--//
#define LS_I_0 0
#define LS_I_1 (RADIANS_TO_DEGREES*(cos(DEGREES_TO_RADIANS*LS_ANGLE_1)))
#define LS_I_2 (sqrt(2)/2)
#define LS_I_3 (RADIANS_TO_DEGREES*(cos(DEGREES_TO_RADIANS*LS_ANGLE_3)))
#define LS_I_4 1
#define LS_I_5 (RADIANS_TO_DEGREES*(cos(DEGREES_TO_RADIANS*LS_ANGLE_5)))
#define LS_I_6 (sqrt(2)/2)
#define LS_I_7 (RADIANS_TO_DEGREES*(cos(DEGREES_TO_RADIANS*LS_ANGLE_7)))
#define LS_I_8 0
#define LS_I_9 (RADIANS_TO_DEGREES*(cos(DEGREES_TO_RADIANS*LS_ANGLE_9)))
#define LS_I_10 (-sqrt(2)/2)
#define LS_I_11 (RADIANS_TO_DEGREES*(cos(DEGREES_TO_RADIANS*LS_ANGLE_11)))
#define LS_I_12 -1
#define LS_I_13 (RADIANS_TO_DEGREES*(cos(DEGREES_TO_RADIANS*LS_ANGLE_13)))
#define LS_I_14 (-sqrt(2)/2)
#define LS_I_15 (RADIANS_TO_DEGREES*(cos(DEGREES_TO_RADIANS*LS_ANGLE_15)))

//--J Values--//
#define LS_J_0 1
#define LS_J_1 (RADIANS_TO_DEGREES*(cos(DEGREES_TO_RADIANS*LS_ANGLE_1)))
#define LS_J_2 (sqrt(2)/2)
#define LS_J_3 (RADIANS_TO_DEGREES*(cos(DEGREES_TO_RADIANS*LS_ANGLE_3)))
#define LS_J_4 0
#define LS_J_5 (RADIANS_TO_DEGREES*(cos(DEGREES_TO_RADIANS*LS_ANGLE_5)))
#define LS_J_6 (-sqrt(2)/2)
#define LS_J_7 (RADIANS_TO_DEGREES*(cos(DEGREES_TO_RADIANS*LS_ANGLE_7)))
#define LS_J_8 -1
#define LS_J_9 (RADIANS_TO_DEGREES*(cos(DEGREES_TO_RADIANS*LS_ANGLE_9)))
#define LS_J_10 (-sqrt(2)/2)
#define LS_J_11 (RADIANS_TO_DEGREES*(cos(DEGREES_TO_RADIANS*LS_ANGLE_11)))
#define LS_J_12 0
#define LS_J_13 (RADIANS_TO_DEGREES*(cos(DEGREES_TO_RADIANS*LS_ANGLE_13)))
#define LS_J_14 (sqrt(2)/2)
#define LS_J_15 (RADIANS_TO_DEGREES*(cos(DEGREES_TO_RADIANS*LS_ANGLE_15)))

//-----IMU-----//
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
#define COMPASS_CALIBRATION 1.39
#define COMPASS_CALIBRATION_TIME 100
#define WHO_AM_I_MPU9250 0x75

//-----Pixy-----//

#define PIXY_READ_RATE 20
#define PIXY_FRAME_HEIGHT 200
#define MAX_ANGLING 200

//-----Defense-----//

#define DEFEND_GOAL_DISTANCE 150
#define DEFEND_SMALL_ANGLE 0

#define DEFEND_BLOCK_DISTANCE 700
#if WHITE
	#define DEFEND_CHARGE_STRENGTH 140
#else
	#define DEFEND_CHARGE_STRENGTH 100
#endif

//-----Bluetooth-----//

#define BT_PACKAGE_NUM 6
#define BT_START_BYTE 255
#define BT_TIMER 100
#define BT_SWITCH_TIMER 1000

////==========FUNCTIONS==========////

//-----General-----//
#define ARRAYSHIFTDOWN(a, lower, upper){          \
	if (upper == (sizeof(a)/sizeof(a[0])) - 1){   \
		for (int q = upper - 1; q >= lower; q--){ \
			*(a + q + 1) = *(a + q); }            \
	} else{                                       \
		for (int q = upper; q >= lower; q--){     \
			*(a + q + 1) = *(a + q); }}}

double updateMax(double max, double newVal);
double angleMap(double angle, double max);
int findSign(double value);
double doubleMod(double x, double m);
double angleBetween(double angleCounterClockwise, double angleClockwise);
double smallestAngleBetween(double angleCounterClockwise, double angleClockwise);
double midAngleBetween(double angleCounterClockwise, double angleClockwise);
int mod(int x, int m);
bool angleIsInside(double angleBoundCounterClockwise, double angleBoundClockwise, double angleCheck);

struct DirSpeed {
	double direction;
	double speed;
};

struct BluetoothData {
	int ballDir;
	int ballStr;
	bool role;
};

#endif
