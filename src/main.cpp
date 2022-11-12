#include <Arduino.h>
#include "SPI.h"

#include "joystick.h"

#include "LMotorController.h"
#include "Servo.h"
#include "Motion.h"

//
#define SER 6
#define ENA 5
#define IN1 4
#define IN2 3

// setup for RF 2Ghz
const uint64_t pipe = 0x80E8ABC123LL; // địa chỉ phát
RF24 radio(9, 10);                    // thay 10 thành 53 với mega
int msg[3];

void setup()
{
  // put your setup code here, to run once:
  // LMotorController
  LMotorController motorController(ENA, IN1, IN2);

  // Servo
  Servo myservo;
  myservo.attach(9); // CHAN RA

  // VoidSetup of rf 2.4ghz
  Serial.begin(9600);
  radio.begin();
  radio.setAutoAck(1);
  radio.setDataRate(RF24_2MBPS); // Tốc độ dữ liệu
  radio.setChannel(10);          // Đặt kênh
  radio.openReadingPipe(1, pipe);
  radio.startListening();
}
void loop()

{
    if (radio.available()) {
    while (radio.available()) {
      radio.read(&msg, sizeof(msg));
      joystick obj(msg[0], msg[1], 1022, 1022, 0, 0);
      Motion(testObj.vel, testObj.phi);
    }
  }

  
}
