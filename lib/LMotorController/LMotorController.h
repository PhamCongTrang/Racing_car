#ifndef LMotorController_h
#define LMotorController_h


#include "Arduino.h"


class LMotorController
{
protected:
    int _ena, _in1, _in2;
    int _currentSpeed;
public:
    LMotorController(int ena, int in1, int in2);
    void move(int speed);
    void stopMoving();
};


#endif