#include "LMotorController.h"
#include "Arduino.h"


LMotorController::LMotorController(int ena, int in1, int in2, double motorAConst)
{
    _motorAConst = motorAConst;
    
	_ena = ena;
	_in1 = in1;
	_in2 = in2;
	
	pinMode(_ena, OUTPUT);
	pinMode(_in1, OUTPUT);
	pinMode(_in2, OUTPUT);
    
}


void LMotorController::move(int speed)
{
    if (speed == _currentSpeed) return;
    
    if (speed > 255) speed = 255;
    else if (speed < -255) speed = -255;
    
    digitalWrite(_in1, speed > 0 ? HIGH : LOW);
    digitalWrite(_in2, speed > 0 ? LOW : HIGH);
    analogWrite(_ena, abs(speed) * _motorAConst);
    
    _currentSpeed = speed;
}

void LMotorController::stopMoving()
{
    digitalWrite(_in1, LOW);
    digitalWrite(_in2, LOW);
    digitalWrite(_ena, HIGH);
    
    _currentSpeed = 0;
}