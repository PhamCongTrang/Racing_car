#include <Arduino.h>
#include "Motion_Control.h"
#include "joystick.h"
void setup() {
  // put your setup code here, to run once:
  
  // LMotorController
  LMotorController motorController(ENA, IN1, IN2);

  //Servo
  Servo myservo;
  myservo.attach(6); // CHAN RA
  testObj 
}

void loop() 
{
  
}
