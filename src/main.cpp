#include <Arduino.h>

#include "joystick.h"

#include "LMotorController.h"
#include "Servo.h"
#include "Motion_Control.h"

#define SER 6
#define ENA 5
#define IN1 4
#define IN2 3
 
void setup()
{
  // put your setup code here, to run once:
  
  // LMotorController
  LMotorController motorController(ENA, IN1, IN2);

  // Servo
  Servo myservo;
  myservo.attach(SER); // CHAN RA

  testObj joystick(700, 800, 1022, 1022, 0, 0);
}
void loop()

{
  Serial.println(testObj.vel);
  Serial.println(testObj.phi);

  Motion(testObj.vel, testObj.phi);
}
