#include "BluetoothModule.h"

void BluetoothModule::init() {
    Serial3.begin(9600);
}

void BluetoothModule::update(float ballDir, float ballStr) {
    thisData.ballDir = (uint16_t)ballDir;
    thisData.ballStr = (uint8_t)ballStr;
    if(bluetoothSendTimer.timeHasPassed()) {
        send();
    }
    recieve();
    decideRole();
    isConnected = bluetoothConnectedTimer.timeHasPassedNoUpdate() ? false : true;
}

void BluetoothModule::send() {
    Serial3.write(BT_START_BYTE);
    Serial3.write(BT_START_BYTE);
    Serial3.write(highByte(thisData.ballDir));
    Serial3.write(lowByte(thisData.ballDir));
    Serial3.write(thisData.ballStr);
    Serial3.write(thisData.role);
}

void BluetoothModule::recieve() {
    uint8_t buffer[BT_PACKAGE_NUM - 2] = {255, 255, 255, false};
    if(Serial3.available() >= BT_PACKAGE_NUM) {
        uint8_t firstByte = Serial3.read();
        uint8_t secondByte = Serial3.peek();
        if(firstByte == BT_START_BYTE && secondByte == BT_START_BYTE) {
            Serial3.read();
            for(uint8_t i = 0; i < BT_PACKAGE_NUM - 2; i++) {
                buffer[i] = Serial3.read();
            }
            bluetoothConnectedTimer.update();
            otherData.ballDir = buffer[0] << 8 | buffer[1];
            otherData.ballDir = otherData.ballDir == 65535 ? -1 : otherData.ballDir;
            otherData.ballStr = buffer[2];
            bool roleBefore = otherData.role;
            otherData.role = buffer[3] == 0 ? false : true;
            if(!roleBefore && otherData.role) {
                if(otherData.role == thisData.role) {
                    isSwitching = true;
                }
            }
        }
    }
}

void BluetoothModule::decideRole() {
    if(!isConnected) {
        thisData.role = false;
        sameRole = 0;
    } else if(isSwitching) {
        thisData.role = !thisData.role;
        isSwitching = false;
        switchTimer.update();
        sameRole = 0;
    } else if(thisData.role == otherData.role) {
        if(sameRole > 100) {
            if(thisData.ballStr > otherData.ballStr) {
                thisData.role = true;
            } else {
                thisData.role = false;
            }
            sameRole = 0;
        } else {
            sameRole += 1;
        }
    }
}