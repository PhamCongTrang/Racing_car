#include <Arduino.h>
#include "SPI.h"
#include "RF24.h"
#include "QTRSensors.h"

#include "joystick.h"
#include "sensor.h"

#include "LMotorController.h"
#include "Servo.h"
#include "SetPID.h"

// Define cac chan dieu khien dong co
#define SER 6
#define ENA 5
#define IN3 7
#define IN4 8

// Define line
#define LN1 1
#define LN2 2
#define LN3 3
#define LN4 4

// setup MOTOR
LMotorController motorController(ENA, IN3, IN4);
Servo myservo;

// setup for RF 2Ghz
const uint64_t pipe = 0x80E8ABC123LL; // địa chỉ phát
RF24 radio(9, 10);                    // thay 10 thành 53 với mega
int msg[3];
// set up of line follow

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
  // set up sensor
  pinMode(LN1, INPUT);
  pinMode(LN2, INPUT);
  pinMode(LN3, INPUT);
  pinMode(LN4, INPUT);

}
// ----------void LOOP-------------------------------------
void loop()
{
  // FULL
  if (radio.available())
  {
    while (radio.available()) // bỏ đi
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
        int line1 = digitalRead(LN1);
        int line2 = digitalRead(LN2);
        int line3 = digitalRead(LN3);
        int line4 = digitalRead(LN4);
        int error;
        error = line1*1 + line2*2 + line3*4 + line4*8;
        switch (error)
        {
          case 0b0001: goc = 3;     break;
          case 0b0010: goc = 1.5;   break;
          case 0b0110: goc = 0;     break;
          case 0b0100: goc = -1;    break;
          case 0b1000: goc = -2;    break;
          case 0b1111: goc = -2.5;  break;
          case 0b1001: goc = -2.5;  break;
        default :                   break;
        }
        myservo.write(90 - 15*goc);
        Serial.println(goc);
        motorController.move(120);
      }
    }
  }  
  //
  /* CODE PID ANALOG
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
    for (uint8_t i = 0; i < SensorCount; i++)
  {
    Serial.print(sensorValues[i]);
    Serial.print('\t');
  }
  */
  /* CODE DIGITAL SWITCH CASE
  int line1 = digitalRead(LN1);
  int line2 = digitalRead(LN2);
  int line3 = digitalRead(LN3);
  int line4 = digitalRead(LN4);

  //sensor ob(line1, line2, line3, line4);
  //int goc=ob.phi;

  int error;
  error = line1*1 + line2*2 + line3*4 + line4*8;
  switch (error)
  {
    case 0b0001: goc = 3;     break;
    case 0b0010: goc = 1.5;   break;
    case 0b0110: goc = 0;     break;
    case 0b0100: goc = -1;    break;
    case 0b1000: goc = -2;    break;
    case 0b1111: goc = -2.5;  break;
    case 0b1001: goc = -2.5;  break;
  default :                   break;
  }
  myservo.write(90 - 15*goc);
  Serial.println(goc);
  motorController.move(120);
  */
}
