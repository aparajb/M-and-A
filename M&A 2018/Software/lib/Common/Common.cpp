#include "Common.h"

double updateMax(double max, double newVal) {
	return max > newVal ? max : newVal;
}

double angleMap(double angle, double max) {
	while(angle >= max) {
		angle -= 360;
	}
	while(angle < (max-360)) {
		angle += 360;
	}
	return angle;
}

int findSign(double value) {
	return value >= 0 ? 1 : -1;
}

double doubleMod(double x, double m) {
	double r = fmod(x, m);
	return r < 0 ? r + m : r;
}

double angleBetween(double angleCounterClockwise, double angleClockwise) {
	return doubleMod(angleClockwise - angleCounterClockwise, 360);
}

double smallestAngleBetween(double angleCounterClockwise, double angleClockwise) {
	double ang = angleBetween(angleCounterClockwise, angleClockwise);
	return fmin(ang, 360 - ang);
}

double midAngleBetween(double angleCounterClockwise, double angleClockwise) {
	return mod(angleCounterClockwise + angleBetween(angleCounterClockwise, angleClockwise) / 2.0, 360);
}

int mod(int x, int m) {
	int r = x % m;
	return r < 0 ? r + m : r;
}

bool angleIsInside(double angleBoundCounterClockwise, double angleBoundClockwise, double angleCheck) {
	if(angleBoundCounterClockwise < angleBoundClockwise) {
		return(angleBoundCounterClockwise < angleCheck && angleCheck < angleBoundClockwise);
	} else {
		return(angleBoundCounterClockwise < angleCheck || angleCheck < angleBoundClockwise);
	}
}
