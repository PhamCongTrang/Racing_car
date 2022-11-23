#include <Arduino.h>

#include "SPI.h"
#include "RF24.h"

#include "QTRSensors.h"

#include "joystick.h"

#include "LMotorController.h"
#include "Servo.h"
#include "SetPID.h"



// Define cac chan dieu khien dong co
#define SER 6
#define ENA 5
#define IN3 7
#define IN4 8



// setup MOTOR
LMotorController motorController(ENA, IN3, IN4);
Servo myservo;



// setup for RF 2Ghz
const uint64_t pipe = 0x80E8ABC123LL; // địa chỉ phát
RF24 radio(9, 10);                    // thay 10 thành 53 với mega
int msg[3];



//----------void SETUP-------------------------------------
void setup()
{
  // VoidSetup of rf 2.4ghz
  Serial.begin(9600);
  radio.begin();
  radio.setAutoAck(1);
  radio.setDataRate(RF24_2MBPS); // Tốc độ dữ liệu
  radio.setChannel(10);          // Đặt kênh
  radio.openReadingPipe(1, pipe);
  radio.startListening();

  myservo.attach(SER);
}



// ----------void LOOP-------------------------------------
void loop()
{
  if (radio.available())
  {
    while (radio.available()) // bỏ đi
    {
      radio.read(&msg, sizeof(msg));
      if (msg[2] == 1)
      {
        joystick obj(msg[0], msg[1], 1022, 1022, 0, 0);

        if (obj.vel > 10)
          v = 0.7 * obj.vel + 72.86;
        else if (obj.vel < -10)
          v = 0.7 * obj.vel - 72.86;
        else
          v = 0;
        motorController.move(v);
        myservo.write(obj.phi);
      }
      else
      {
        
      }
    }
  }
  /*
  //  CODE PID ANALOG
      uint16_t position = qtr.readLineBlack(sensorValues);
  errpre = errnow;
  errnow = position - 2500; // Thay errnow = Hàm của Hoàng : vị trí tương đối của line so với điểm chính giữa
  dt = millis() - tpre;
  tpre = millis();
  P = Kp * errnow;
  I += Ki * errnow * dt;
  D = Kd * (errnow - errpre) / dt;
  motorController.move(255 * (1 - Kv * abs(D)));
  myservo.write((P + I + D) + 90);
  */
}
