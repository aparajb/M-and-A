#ifndef LIGHTSENSORS_H
#define LIGHTSENSORS_H

#include <LightSensor.h>
#include <Arduino.h>

class LightSensors {
public:
    LightSensors();
    void lightSensorsSetup();
    void readArray();
    void fillInSensors();
    void findClusters();
    void updateLineLocation();
    double getLineDir();
private:
    LightSensor lightSensors[LS_NUM];
    int pins[LS_NUM] = {LS_0, LS_1, LS_2, LS_3, LS_4, LS_5, LS_6, LS_7, LS_8, LS_9, LS_10, LS_11, LS_12, LS_13, LS_14, LS_15};
    double lightSensor_I[LS_NUM] = {LS_I_0, LS_I_1, LS_I_2, LS_I_3, LS_I_4, LS_I_5, LS_I_6, LS_I_7, LS_I_8, LS_I_9, LS_I_10, LS_I_11, LS_I_12, LS_I_13, LS_I_14, LS_I_15};
    double lightSensor_J[LS_NUM] = {LS_J_0, LS_J_1, LS_J_2, LS_J_3, LS_J_4, LS_J_5, LS_J_6, LS_J_7, LS_J_8, LS_J_9, LS_J_10, LS_J_11, LS_J_12, LS_J_13, LS_J_14, LS_J_15};
    bool lightSensorOnWhite[16] = {false};
    int starts[4] = {0};
    int ends[4] = {0};
    bool findStart;
    int clustersActivated;
    double totalI;
    double totalJ;
    double lineDir;
};

#endif
