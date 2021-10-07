#ifndef CAMERA_H
#define CAMERA_H

#include <Common.h>
#include <Vect.h>

#define CAMERA_PACKET_NUM 8
#define CENTRE_X 120
#define CENTRE_Y 120
#define CAMERA_BAUD 115200
#define COMS_SYNC_BYTE 234


class Camera {
public:
    Camera();
    void init();
    void update(float heading, bool attackBlue);
    Vect robot;
    Vect ball;
private:
    Vect blueGoal;
    Vect yellowGoal;
    float ballPixeltoCM(float dist);
    float goalPixeltoCM(float dist);
};

#endif