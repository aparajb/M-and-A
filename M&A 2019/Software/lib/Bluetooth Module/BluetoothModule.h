#ifndef BLUETOTTHMODULE_H
#define BLUETOTTHMODULE_H

#include <Common.h>
#include <Timer.h>

class BluetoothModule {
public:
    BluetoothModule() {}
    void init();
    void update(float ballDir, float ballStr);
    BluetoothData thisData = {0, 0, false};
    Timer switchTimer = Timer(BT_SWITCH_TIMER);
    bool isConnected = false;
    bool isSwitching = false;
private:
    void send();
    void recieve();
    void decideRole();
    BluetoothData otherData = {0, 0, false};
    Timer bluetoothConnectedTimer = Timer(BT_CONNECTED_TIMER);
    Timer bluetoothSendTimer = Timer(BT_SEND_TIMER);
    uint16_t sameRole = 0;
};



#endif // BLUETOTTHMODULE_H