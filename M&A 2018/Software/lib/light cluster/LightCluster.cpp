#include "LightCluster.h"

LightCluster::LightCluster() {}

void LightCluster::resetCluster() {
    firstSensor = -1;
    lastSensor = -1;
    clusterActivated = false;
}

void LightCluster::findClusterCentre() {
    if(clusterActivated == true) {
        if(firstSensor < lastSensor) {
            clusterCentre = ((firstSensor + lastSensor) / 2) * 22.5;
        } else {
            clusterCentre = angleMap(((firstSensor + lastSensor) / 2) * 22.5 + 180, 360);
        }
    }
}
