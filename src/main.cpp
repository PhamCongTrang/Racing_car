#include <Arduino.h>
#include "Motion_Control.h"
void setup() {
  // put your setup code here, to run once:
  // LMotorController
  double motorSpeedFactor = 1;
  LMotorController motorController(ENA, IN1, IN2, motorSpeedFactor);

  //Servo
  Servo myservo;
  myservo.attach(9); // CHAN RA
}

void loop() 
{
  
}
