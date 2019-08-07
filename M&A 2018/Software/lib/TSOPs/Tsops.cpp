#include "Tsops.h"

Tsops::Tsops() {}

void Tsops::tsopsSetup() {
	for (int i = 0; i < TSOP_NUM; i++) {
		pinMode(tsopPins[i], INPUT);
	}
}

void Tsops::updateOnce() {
	for (int i = 0; i < TSOP_NUM; i++) {
		tempValues[i] += 1 - digitalRead(tsopPins[i]);
	}
	tsopCounter++;
}

void Tsops::filterTsops() {
	for (int i = 0; i < TSOP_NUM; i++) {
		if(tempValues[i] > TSOP_MAX_IGNORE || tempValues[i] < TSOP_MIN_IGNORE) {
			values[i] = 0;
		} else {
			values[i] = tempValues[i];
		}
	}
	#if !DEFAULT_ROLE
		values[6] = 0;
	#endif
}

void Tsops::read() {
	for(int i = tsopCounter; i < TSOP_READ_NUM; i++) {
		updateOnce();
	}
	filterTsops();
	findTsops();
	findStrength();
	findAngle();
	finishedRead();
}

void Tsops::finishedRead() {
	tsopCounter = 0;
	for(int i = 0; i < TSOP_NUM; i++) {
		values[i] = 0;
		tempValues[i] = 0;
		sortedValues[i] = 0;
		indexes[i] = 0;
	}
}

void Tsops::findTsops() {
	for (int i = 0; i < TSOP_NUM; i++) {
		for (int j = 0; j < TSOP_NUM; j++) {
			if (values[i] > sortedValues[j]) {
				if (j <= i) {
					ARRAYSHIFTDOWN(sortedValues, j, i);
					ARRAYSHIFTDOWN(indexes, j, i);
				}
				sortedValues[j] = values[i];
				indexes[j] = i;
				break;
			}
		}
	}
}

void Tsops::findStrength() {
	avgStr = ((3 * sortedValues[0]) + (2 * sortedValues[1]) + sortedValues[2] + sortedValues[3]) / 7;
	ballVisible = (avgStr != 0);
}

void Tsops::findAngle() {
	double x = ((sortedValues[0] * xValues[indexes[0]]) + (sortedValues[1] * xValues[indexes[1]]) + (sortedValues[2] * xValues[indexes[2]]) + (sortedValues[3] * xValues[indexes[3]])) / 4;
	double y = ((sortedValues[0] * yValues[indexes[0]]) + (sortedValues[1] * yValues[indexes[1]]) + (sortedValues[2] * yValues[indexes[2]]) + (sortedValues[3] * yValues[indexes[3]])) / 4;
	ballDir = angleMap(RADIANS_TO_DEGREES*(atan2(y, x)), 360);
	ballDir = angleIsInside(340, 60, ballDir) ? angleMap(ballDir - 7.5 , 360) : ballDir;
	// Serial.println(ballDir);
}

double Tsops::getBallDir() {
	return ballDir;
}

double Tsops::getAvgStr() {
	return avgStr;
}

bool Tsops::getBallVisible() {
	return ballVisible;
}
