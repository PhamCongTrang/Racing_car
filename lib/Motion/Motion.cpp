// FUNCTION DIEU KHIEN 2 DONG CO
// DONG CO DC GAN VOI BANH SAU THONG QUA L298N
// DONG CO SERVO DIEU HUONG PHIA TRUOC DIEU KHIEN TRUC TIEP QUA ARDUINO UNO
#include "Motion.h"
#include "Arduino.h"
#include "LMotorController.h"
#include "Servo.h"

#define ENA 5
#define IN1 4
#define IN2 3

void Motion(int speed, int theta)
{
    // DC MOTOR
    LMotorController motorController(ENA, IN1, IN2);
    motorController.move(speed);
    //SERVO MOTOR  
    Servo myservo;
    myservo.attach(6);
    myservo.write(theta);
}