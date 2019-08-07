#include "LightSensors.h"

LightSensors::LightSensors() {
    for (int i = 0; i < LS_NUM; i++) {
        lightSensors[i] = LightSensor(pins[i]);
    }
}

void LightSensors::lightSensorsSetup() {
    for (int i = 0; i < LS_NUM; i++) {
        lightSensors[i].lightSensorSetup();
    }
}

void LightSensors::readArray() {
    for(int i = 0; i < LS_NUM; i++) {
        lightSensorOnWhite[i] = lightSensors[i].onWhite();
    }
    lightSensorOnWhite[BROKEN_LIGHT_SENSOR] = 0;
}

void LightSensors::fillInSensors() {
    for (int i = 0; i < LS_NUM; i ++) {
        if(!lightSensorOnWhite[i]) {
            if(lightSensorOnWhite[mod(i - 1, LS_NUM)] && lightSensorOnWhite[mod(i + 1, LS_NUM)]) {
                lightSensorOnWhite[i] = true;
            }
        }
    }
}

void LightSensors::findClusters() {
    clustersActivated = 0;
    findStart = true;
    for (int i = 0; i < 4; i++) {
        starts[i] = -1;
        ends[i] = -1;
    }
    for (int i = 0; i < LS_NUM; i++) {
        if(findStart) {
            if(lightSensorOnWhite[i]) {
                starts[clustersActivated] = i;
                findStart = false;
                clustersActivated += 1;
            }
        } else {
            if(!lightSensorOnWhite[i]) {
                ends[clustersActivated - 1] = i - 1;
                findStart = true;
            }
        }
    }
    if(lightSensorOnWhite[15]) {
        ends[clustersActivated - 1] = 15;
    }
    if(clustersActivated >= 1) {
        if(lightSensorOnWhite[0] && lightSensorOnWhite[15]) {
            starts[0] = starts[clustersActivated - 1];
            starts[clustersActivated - 1] = -1;
            ends[clustersActivated - 1] = -1;
        }
    }
}

void LightSensors::updateLineLocation() {
    readArray();
    fillInSensors();
    findClusters();
    if(clustersActivated > 0) {
        double cluster1Angle = midAngleBetween(starts[0] * LS_INTERVAL_ANGLE, ends[0] * LS_INTERVAL_ANGLE);
        double cluster2Angle = midAngleBetween(starts[1] * LS_INTERVAL_ANGLE, ends[1] * LS_INTERVAL_ANGLE);
        double cluster3Angle = midAngleBetween(starts[2] * LS_INTERVAL_ANGLE, ends[2] * LS_INTERVAL_ANGLE);
        if(clustersActivated == 3) {
            double angleDiff12 = angleBetween(cluster1Angle, cluster2Angle);
            double angleDiff23 = angleBetween(cluster2Angle, cluster3Angle);
            double angleDiff31 = angleBetween(cluster3Angle, cluster1Angle);
            double biggestAngle = updateMax(angleDiff12, updateMax(angleDiff23, angleDiff31));
            if(biggestAngle == angleDiff12) {
                lineDir = midAngleBetween(cluster2Angle, cluster1Angle);
            } else if(biggestAngle == angleDiff23) {
                lineDir = midAngleBetween(cluster3Angle, cluster2Angle);
            } else {
                lineDir = midAngleBetween(cluster1Angle, cluster3Angle);
            }
        } else if (clustersActivated == 2) {
            lineDir = angleBetween(cluster1Angle, cluster2Angle) <= 180 ? midAngleBetween(cluster1Angle, cluster2Angle) : midAngleBetween(cluster2Angle, cluster1Angle);
        } else {
            lineDir = cluster1Angle;
        }
    } else {
        lineDir = -1;
    }
}

double LightSensors::getLineDir() {
  return lineDir;
}
