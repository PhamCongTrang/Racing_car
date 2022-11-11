//------
#ifndef Motion_h
#define Motion_h


#include "Arduino.h"
#include "LMotorController.h"
#include "Servo.h"

#define ENA 10
#define IN1 6
#define IN2 7

class LMotorController
{
protected:
    int _ena, _in1, _in2;
    int _currentSpeed;
    double _motorAConst;
public:
    LMotorController(int ena, int in1, int in2, double motorAConst);
    void move(int speed);
    void stopMoving();
};


#endif