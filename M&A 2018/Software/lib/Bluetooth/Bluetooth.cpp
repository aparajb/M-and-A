#include "Bluetooth.h"

Bluetooth::Bluetooth(bool startingRole) {
    startRole = startingRole;
}

void Bluetooth::init() {
    Serial2.begin(38400);
    role = startRole;
}

void Bluetooth::update(BluetoothData data) {
    thisData = data;
    if(bluetoothSendTimer.timeHasPassed()) {
        send();
    }
    recieve();
    isConnected = true;
    if(bluetoothTimer.timeHasPassed()) {
        isConnected = false;
    }
}

void Bluetooth::send() {
    Serial2.write(BT_START_BYTE);
    Serial2.write(BT_START_BYTE);
    Serial2.write(highByte(thisData.ballDir));
    Serial2.write(lowByte(thisData.ballDir));
    Serial2.write(thisData.ballStr);
    Serial2.write(thisData.role);
}

void Bluetooth::recieve() {
    int buffer[BT_PACKAGE_NUM - 2] = {65535, 65535, 65535, false};
    while(Serial2.available() >= BT_PACKAGE_NUM) {
        isConnected = true;
        uint8_t firstByte = Serial2.read();
        uint8_t secondByte = Serial2.peek();

        if(firstByte == BT_START_BYTE && secondByte == BT_START_BYTE) {
            Serial2.read();
            for(int i = 0; i < BT_PACKAGE_NUM - 2; i++) {
                buffer[i] = Serial2.read();
            }
        }
        bluetoothTimer.update();
    }
    otherData.ballDir = buffer[0] << 8 | buffer[1];
    otherData.ballStr = buffer[2];
    otherData.role = buffer[3] == 0 ? false : true;
}
