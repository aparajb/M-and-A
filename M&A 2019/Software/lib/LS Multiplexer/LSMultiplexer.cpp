#include "LSMultiplexer.h"

LSMultiplexer::LSMultiplexer() {}

void LSMultiplexer::init() {
        pinMode(MUX1_S0, OUTPUT);
        pinMode(MUX1_S1, OUTPUT);
        pinMode(MUX1_S2, OUTPUT);
        pinMode(MUX1_S3, OUTPUT);
        pinMode(MUX1_OUT, INPUT);
        pinMode(MUX2_OUT, INPUT);
    // for(uint8_t i = 0; i < 5; i++) {
    //     pinMode(control[i], OUTPUT);
    // }
    // pinMode(controlOutput, INPUT);
    for(uint8_t i = 0; i < LS_NUM; i++) {
        uint16_t calibrateTotal = 0;
        for (uint8_t j = 0; j < LS_CALIBRATE_COUNT; j++) {
            read(i);
            calibrateTotal += readValue[i];
        }
        thresholdValue[i] = (uint16_t)round(calibrateTotal / LS_CALIBRATE_COUNT) + LS_BUFFER;
    }
}

void LSMultiplexer::read(uint8_t LSIndex) {
    // bool binary[5] = {false};
    // float decimal = pins[LSIndex];
    // for(uint8_t i = 4; i >= 0 && decimal >= 1; i--) {
    //     binary[i] = ((uint8_t)decimal) % 2;
    //     decimal /= 2;
    // }
    // for(uint8_t i = 0; i < 5; i++) {
    //     digitalWrite(control[i], binary[i]);
    // }

    bool isFirstMux = true;
    int muxChannel = 0;
    if (LSIndex <= 7) {
        muxChannel = 7 - LSIndex;
    } else if (LSIndex <= 15 ) {
        muxChannel = LSIndex;
    } else if (LSIndex <= 23) {
        isFirstMux = false;
        muxChannel = 23 - LSIndex;
    } else if (LSIndex <= 31) {
        isFirstMux = false;
        muxChannel = LSIndex - 16;
    }
    digitalWrite(MUX1_S0, muxChannel & 0x1);
    digitalWrite(MUX1_S1, (muxChannel >> 1) & 0x1);
    digitalWrite(MUX1_S2, (muxChannel >> 2) & 0x1);
    digitalWrite(MUX1_S3, (muxChannel >> 3) & 0x1);
    readValue[LSIndex] = analogRead(isFirstMux ? MUX1_OUT : MUX2_OUT);
    if(LSIndex == 15) {
        readValue[LSIndex] = 0;
    }
}

void LSMultiplexer::update(float heading) {
    for(uint8_t i = 0; i < LS_NUM; i++) {
        read(i);
    }
    for(uint8_t i = 0; i < LS_NUM; i++) {
        onWhite[mod(32-(i-7), 32)] = (readValue[i] > thresholdValue[i]);
            // Serial.printf ("%d ", onWhite[i]);
    }
    // Serial.println();
    for(uint8_t i = 0; i < LS_NUM; i ++) {
        if(!onWhite[i]) {
            if(onWhite[mod(i - 1, LS_NUM)] && onWhite[mod(i + 1, LS_NUM)]) {
                onWhite[i] = true;
            }
        }
    }
	uint8_t clustersNum = 0;
    bool findClusterStarts = true;
    int8_t clusterStarts[4] = {-1, -1, -1, -1};
    int8_t clusterEnds[4] = {-1, -1, -1, -1};
    for(uint8_t i = 0; i < LS_NUM; i++) {
        if(findClusterStarts) {
            if(onWhite[i]) {
                clusterStarts[clustersNum] = i;
                findClusterStarts = false;
                clustersNum += 1;
            }
        } else {
            if(!onWhite[i]) {
                clusterEnds[clustersNum - 1] = i - 1;
                findClusterStarts = true;
            }
        }
    }
    if(onWhite[LS_NUM - 1]) {
        clusterEnds[clustersNum - 1] = LS_NUM - 1;
    }
    if(clustersNum > 1) {
        if(onWhite[0] && onWhite[LS_NUM - 1]) {
            clusterStarts[0] = clusterStarts[clustersNum - 1];
            clusterStarts[clustersNum - 1] = -1;
            clusterEnds[clustersNum - 1] = -1;
            clustersNum -= 1;
        }
    }
    if(clustersNum > 0) {
        float cluster1Angle = midAngleBetween(clusterStarts[0] * LS_INTERVAL_ANGLE, clusterEnds[0] * LS_INTERVAL_ANGLE);
        float cluster2Angle = midAngleBetween(clusterStarts[1] * LS_INTERVAL_ANGLE, clusterEnds[1] * LS_INTERVAL_ANGLE);
        float cluster3Angle = midAngleBetween(clusterStarts[2] * LS_INTERVAL_ANGLE, clusterEnds[2] * LS_INTERVAL_ANGLE);
        if(clustersNum == 3) {
            float angleDiff12 = angleBetween(cluster1Angle, cluster2Angle);
            float angleDiff23 = angleBetween(cluster2Angle, cluster3Angle);
            float angleDiff31 = angleBetween(cluster3Angle, cluster1Angle);
            float biggestAngle = max(angleDiff12, max(angleDiff23, angleDiff31));
            if(biggestAngle == angleDiff12) {
                lineDir = midAngleBetween(cluster2Angle, cluster1Angle);
                lineSize = angleBetween(cluster2Angle, cluster1Angle) <= 180 ? 1 - cos(DEGREES_TO_RADIANS * (angleBetween(cluster2Angle, cluster1Angle) / 2.0)) : 1;
            } else if(biggestAngle == angleDiff23) {
                lineDir = midAngleBetween(cluster3Angle, cluster2Angle);
                lineSize = angleBetween(cluster3Angle, cluster2Angle) <= 180 ? 1 - cos(DEGREES_TO_RADIANS * (angleBetween(cluster3Angle, cluster2Angle) / 2.0)) : 1;
            } else {
                lineDir = midAngleBetween(cluster1Angle, cluster3Angle);
                lineSize = angleBetween(cluster1Angle, cluster3Angle) <= 180 ? 1 - cos(DEGREES_TO_RADIANS * (angleBetween(cluster1Angle, cluster3Angle) / 2.0)) : 1;
            }
        } else if (clustersNum == 2) {
            lineDir = angleBetween(cluster1Angle, cluster2Angle) <= 180 ? midAngleBetween(cluster1Angle, cluster2Angle) : midAngleBetween(cluster2Angle, cluster1Angle);
            lineSize = 1 - cos(DEGREES_TO_RADIANS * (angleBetween(cluster1Angle, cluster2Angle) <= 180 ? angleBetween(cluster1Angle, cluster2Angle) / 2.0 : angleBetween(cluster2Angle, cluster1Angle) / 2.0));
        } else {
            lineDir = cluster1Angle;
            lineSize = 1 - cos(DEGREES_TO_RADIANS * (angleBetween(clusterStarts[0] * LS_INTERVAL_ANGLE, clusterEnds[0] * LS_INTERVAL_ANGLE) / 2.0));
        }
    } else {
        lineDir = -1;
        lineSize = -1;
    }
    bool noLine = (lineDir == -1);
    float lineDirection = noLine ? -1 : floatMod(lineDir + heading, 360);
    if(onField) {
        if(!noLine) {
            fieldLineAngle = lineDirection;
            fieldLineSize = lineSize;
            onField = false;
        }
    } else {
        if(fieldLineSize == 3) {
            if(!noLine) {
                fieldLineAngle = floatMod(lineDirection + 180, 360);
                fieldLineSize = 2 - lineSize;
            }
        } else {  
            if(noLine) {
                if(fieldLineSize <= 1) {
                    onField = true;
                    fieldLineAngle = -1;
                    fieldLineSize = -1;
                } else {
                    fieldLineSize = 3;
                }
            } else {
                if(smallestAngleBetween(lineDirection, fieldLineAngle) <= 90) {
                    fieldLineAngle = lineDirection;
                    fieldLineSize = lineSize;
                } else {
                    fieldLineAngle = floatMod(lineDirection + 180, 360);
                    fieldLineSize = 2 - lineSize;
                }
            }
        }
    }
    Serial.print(fieldLineAngle); Serial.print("\t");
    Serial.println(fieldLineSize);
}

Movement LSMultiplexer::calculateOutAvoidance(float heading, Movement originalVal) {
    Movement sendVal = originalVal;
    if(!onField) {
        if(fieldLineSize > LS_MEDIUM_SIZE) {
            sendVal.direction = floatMod(fieldLineAngle + 180 - heading, 360);
            sendVal.speed = fieldLineSize > LS_BIG_SIZE ? LS_AVOID_FAST : LS_AVOID_MEDIUM;
        } else if(fieldLineSize > LS_SMALL_SIZE) {
            if(smallestAngleBetween(fieldLineAngle, sendVal.direction) < 60) {
                sendVal.speed = 0;
            }
        }
    }
    return sendVal;
}