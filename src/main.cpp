#include <Arduino.h>

#include "joystick.h"

#include "LMotorController.h"
#include "Servo.h"
#include "Motion.h"

/*
#define SER 6
#define ENA 5
#define IN1 4
#define IN2 3
 */

void setup()
{
  // put your setup code here, to run once:
  /*
  // LMotorController
  LMotorController motorController(ENA, IN1, IN2);

  // Servo
  Servo myservo;
  myservo.attach(9); // CHAN RA
  */
}
void loop()

{
  joystick testObj(700, 800, 1022, 1022, 0, 0);
  Serial.println(testObj.vel);
  Serial.println(testObj.phi);

  Motion(testObj.vel, testObj.phi);
}
