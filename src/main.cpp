#include <Arduino.h>
#include "SPI.h"
#include "RF24.h"

#include "joystick.h"

#include "LMotorController.h"
#include "Servo.h"

// Define cac chan dieu khien dong co
#define SER 6
#define ENA 5
#define IN1 4
#define IN2 3

// setup MOTOR
LMotorController motorController(ENA, IN1, IN2);
Servo myservo;

// setup for RF 2Ghz
const uint64_t pipe = 0x80E8ABC123LL; // địa chỉ phát
RF24 radio(9, 10);                    // thay 10 thành 53 với mega
int msg[3];

//----------void SETUP-------------------------------------
void setup()
{
  // put your setup code here, to run once:

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
//------khai bao bien cho PID do line------
int dt, tpre;
int Kp, Ki, Kd, Kv; // Kv la he so giam toc khi vao goc cua
int errnow, errpre;
int P, I = 0, D;
//-----------------------------------------
void loop()

{
    if (radio.available()) {
    while (radio.available()) 
    {
      radio.read(&msg, sizeof(msg));
      if(msg[2] == 1)
      {
        joystick obj(msg[0], msg[1], 1022, 1022, 0, 0);
        motorController.move(obj.vel);
        myservo.write(obj.phi);
      }
      else
      {
        errpre = errnow;
        errnow = 0; //Thay errnow = Hàm của Hoàng : vị trí tương đối của line so với điểm chính giữa
        dt = millis() - tpre;
        tpre = millis();
        P = Kp*errnow;
        I += Ki*errnow*dt;
        D = Kd*(errnow-errpre)/dt;
        motorController.move(255*Kv*D);
        myservo.write(P + I + D);
      }
    }
  }   
}
