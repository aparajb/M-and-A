#include "TSSPs.h"

void TSSPs::init() {
    for(uint8_t i = 0; i < TSSP_NUM; i++) {
		pinMode(tsspPins[i], INPUT);
	}
	if(EEPROM.read(0)) {
		for(int i = 0; i < TSSP_NUM; i++) {
			tsspAdd[i] = AtsspAdd[i];
		}
	} else {
		for(int i = 0; i < TSSP_NUM; i++) {
			tsspAdd[i] = BtsspAdd[i];
		}
	}
}

void TSSPs::update() {
	for(int i = tsspCounter; i < TSSP_READ_NUM; i++) {
		for(int i = 0; i < TSSP_NUM; i++) {
		    tsspValues[i] += 1 - digitalRead(tsspPins[i]);
	    }
	    tsspCounter++;
	}
	for(int i = 0; i < TSSP_NUM; i++) {
		tsspValues[i] = tsspValues[i] != 0 ? tsspValues[i] + tsspAdd[i] : 0;
		tsspSortedValues[i] = 0;
	}
    for(int i = 0; i < TSSP_NUM; i++) {
		for(int j = 0; j < TSSP_NUM; j++) {
			if(tsspValues[i] > tsspSortedValues[j]) {
				if(j <= i) {
					ARRAYSHIFTDOWN(tsspSortedValues, j, i);
					ARRAYSHIFTDOWN(tsspIndexes, j, i);
				}
				tsspSortedValues[j] = tsspValues[i];
				tsspIndexes[j] = i;
				break;
			}
		}
	}
    ballStr = ((3 * tsspSortedValues[0]) + (2 * tsspSortedValues[1]) + tsspSortedValues[2] + tsspSortedValues[3]) / 7;
	ballVisible = (ballStr != 0);
    float x = ((tsspSortedValues[0] * tsspXValues[tsspIndexes[0]]) + (tsspSortedValues[1] * tsspXValues[tsspIndexes[1]]) + (tsspSortedValues[2] * tsspXValues[tsspIndexes[2]]) + (tsspSortedValues[3] * tsspXValues[tsspIndexes[3]])) / 4;
	float y = ((tsspSortedValues[0] * tsspYValues[tsspIndexes[0]]) + (tsspSortedValues[1] * tsspYValues[tsspIndexes[1]]) + (tsspSortedValues[2] * tsspYValues[tsspIndexes[2]]) + (tsspSortedValues[3] * tsspYValues[tsspIndexes[3]])) / 4;
	ballDir = ballVisible ? 360 - floatMod((RADIANS_TO_DEGREES * (atan2f(y, x))) - 90, 360) : -1;
	tsspCounter = 0;
	for(int i = 0; i < TSSP_NUM; i++) {
		tsspValues[i] = 0;
		tsspSortedValues[i] = 0;
		tsspIndexes[i] = 0;
	}
}

float TSSPs::calculateAngleAddition() {
	float dir = ballDir > 180 ? ballDir - 360 : ballDir;
    float ballAngleDifference = findSign(dir) * fmin(90, 0.4 * expf(0.25 * smallestAngleBetween(ballDir, 0)));
    float strengthFactor = constrain(ballStr / BALL_CLOSE_STRENGTH, 0, 1);
    float distanceMultiplier = constrain((0.02 * strengthFactor * expf(4.5 * strengthFactor)), 0, 1);
	angleAddition = ballAngleDifference * distanceMultiplier;
	return angleAddition;
}