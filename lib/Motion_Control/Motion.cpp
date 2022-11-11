// FUNCTION DIEU KHIEN 2 DONG CO
// DONG CO DC GAN VOI BANH SAU THONG QUA L298N
// DONG CO SERVO DIEU HUONG PHIA TRUOC DIEU KHIEN TRUC TIEP QUA ARDUINO UNO
#include "Motion.h"
#include "LMotorController.h"
#include "Servo.h"

void Motion::Motion(int speed, int theta)
{
    // DC MOTOR
    double motorSpeedFactor = 1;

    LMotorController motorController(ENA, IN1, IN2, motorSpeedFactor);

    motorController.move(speed);
    //SERVO MOTOR
     
}
