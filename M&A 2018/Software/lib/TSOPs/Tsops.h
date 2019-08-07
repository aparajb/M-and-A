#ifndef TSOPS_H
#define TSOPS_H

#include <Arduino.h>
#include <Common.h>

class Tsops {
public:
    Tsops();
    void tsopsSetup();
    void updateOnce();
    void filterTsops();
    void read();
    void finishedRead();
    void findTsops();
    void findStrength();
    void findAngle();
    double getBallDir();
    double getAvgStr();
    bool getBallVisible();
private:
    int tsopPins[TSOP_NUM] = {TSOP_PIN_0,TSOP_PIN_1,TSOP_PIN_2,TSOP_PIN_3,TSOP_PIN_4,TSOP_PIN_5,TSOP_PIN_6,TSOP_PIN_7,TSOP_PIN_8,TSOP_PIN_9,TSOP_PIN_10,TSOP_PIN_11};
    int tsopAngles[TSOP_NUM] = {TSOP_ANGLE_0, TSOP_ANGLE_1, TSOP_ANGLE_2, TSOP_ANGLE_3, TSOP_ANGLE_4, TSOP_ANGLE_5, TSOP_ANGLE_6, TSOP_ANGLE_7, TSOP_ANGLE_8, TSOP_ANGLE_9, TSOP_ANGLE_10, TSOP_ANGLE_11};
    int tempValues[TSOP_NUM] = {0};
    double xValues[TSOP_NUM] = {TSOP_X_0, TSOP_X_1, TSOP_X_2, TSOP_X_3, TSOP_X_4, TSOP_X_5, TSOP_X_6, TSOP_X_7, TSOP_X_8, TSOP_X_9, TSOP_X_10, TSOP_X_11};
    double yValues[TSOP_NUM] = {TSOP_Y_0, TSOP_Y_1, TSOP_Y_2, TSOP_Y_3, TSOP_Y_4, TSOP_Y_5, TSOP_Y_6, TSOP_Y_7, TSOP_Y_8, TSOP_Y_9, TSOP_Y_10, TSOP_Y_11};
    int tsopCounter;
    double ballDir;
    int values[TSOP_NUM] = {0};
    double avgStr;
    int sortedValues[TSOP_NUM] = {0};
    int indexes[TSOP_NUM] = {0};
    bool ballVisible;
};

#endif
