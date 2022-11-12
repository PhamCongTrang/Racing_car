#include <Arduino.h>
#include "Motion_Control.h"
#include "joystick.h"
#include "RF24.h"
void setup()
{
  // put your setup code here, to run once:
  // LMotorController
  double motorSpeedFactor = 1;
  LMotorController motorController(ENA, IN1, IN2, motorSpeedFactor);

  // Servo
  Servo myservo;
<<<<<<< HEAD
  myservo.attach(9); // CHAN RA
  testObj joystick(700, 800, 1022, 1022, 0, 0);
=======
  myservo.attach(6); // CHAN RA
  testObj 
>>>>>>> 1b9edebc8f7abfc252c6b25b1aca107780c1900d
}
void loop()

{
  Serial.println(testObj.vel);
  Serial.println(testObj.phi);
}
