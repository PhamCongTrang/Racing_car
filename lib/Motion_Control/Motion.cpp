// FUNCTION DIEU KHIEN 2 DONG CO
// DONG CO DC GAN VOI BANH SAU THONG QUA L298N
// DONG CO SERVO DIEU HUONG PHIA TRUOC DIEU KHIEN TRUC TIEP QUA ARDUINO UNO
#include "Motion.h"
#include <Arduino.h>
#include "LMotorController.h"

#define ENA 10
#define IN1 6
#define IN2 7
#define IN3 4
#define IN4 9
#define ENB 11

#define min_speed 0
#define max_speed 255

double motorSpeedFactorLeft = 1;
double motorSpeedFactorRight = 1;

LMotorController motorController(ENA, IN1, IN2, ENB, IN3, IN4, motorSpeedFactorLeft, motorSpeedFactorRight);

void setup()
{
    Serial.begin(9600);
    Wire.begin();
}
void loop()
{
    
    if ((abs(angleX) < 3) || (abs(angleX) > 75))
    {
        motorController.stopMoving();
    }
    else
    {
        if (speed > 0)
        {
            speed = constrain(speed, min_speed, max_speed);
        }
        else
        {
            speed = constrain(speed, -max_speed, -min_speed);
        }
        motorController.move(speed);
    }
}
