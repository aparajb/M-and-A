#include "LRFBoard.h"

LRFBoard::LRFBoard() {}

void LRFBoard::init() {
    Serial2.begin(9600);
    Serial6.begin(9600);
    Serial5.begin(9600);
    Serial4.begin(9600);
}

void LRFBoard::update() {
    if(Serial2.available() >= 8) {
        uint8_t firstByte = Serial2.read();
        uint8_t secondByte = Serial2.peek();
        if(firstByte == 90 && secondByte == firstByte) {
            Serial2.read();
            Serial2.read();
            Serial2.read();
            uint8_t highByte = Serial2.read();
            uint8_t lowByte = Serial2.read();
            front = highByte << 8 | lowByte;
        }
    }
    if(Serial6.available() >= 8) {
        uint8_t firstByte = Serial6.read();
        uint8_t secondByte = Serial6.peek();
        if(firstByte == 90 && secondByte == firstByte) {
            Serial6.read();
            Serial6.read();
            Serial6.read();
            uint8_t highByte = Serial6.read();
            uint8_t lowByte = Serial6.read();
            right = highByte << 8 | lowByte;
        }
    }
    if(Serial5.available() >= 8) {
        uint8_t firstByte = Serial5.read();
        uint8_t secondByte = Serial5.peek();
        if(firstByte == 90 && secondByte == firstByte) {
            Serial5.read();
            Serial5.read();
            Serial5.read();
            uint8_t highByte = Serial5.read();
            uint8_t lowByte = Serial5.read();
            back = highByte << 8 | lowByte;
        }
    }
    if(Serial4.available() >= 8) {
        uint8_t firstByte = Serial4.read();
        uint8_t secondByte = Serial4.peek();
        if(firstByte == 90 && secondByte == firstByte) {
            Serial4.read();
            Serial4.read();
            Serial4.read();
            uint8_t highByte = Serial4.read();
            uint8_t lowByte = Serial4.read();
            left = highByte << 8 | lowByte;
        }
    }
}