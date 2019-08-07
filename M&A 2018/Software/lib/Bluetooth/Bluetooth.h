#ifndef BLUETOTTH_H_
#define BLUETOTTH_H_

#include <Common.h>
#include <Arduino.h>
#include <Timer.h>

class Bluetooth {
public:
    Bluetooth(bool startingRole);
    void init();
    void update(BluetoothData data);
    BluetoothData otherData = {0, 0, (1 - defaultMode)};
    bool isConnected = false;
private:
    void send();
    void recieve();
    bool defaultMode = 0;
    bool role;
    bool startRole;
    BluetoothData thisData = {0, 0, defaultMode};
    Timer bluetoothTimer = Timer(2000);
    Timer bluetoothSendTimer = Timer(10);
};



#endif
