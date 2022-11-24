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

// Define sensor
QTRSensors qtr;
const uint8_t SensorCount = 8;
uint16_t sensorValues[SensorCount];
int valueLine[8];


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

  // configure the sensors
  qtr.setTypeRC();
  qtr.setSensorPins((const uint8_t[]){4, 3, A0, A1, A2, A3, A4, A5}, SensorCount);
  qtr.setEmitterPin(2);
}

// ----------void LOOP-------------------------------------
void loop()
{
  /* FULL
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
        // read raw sensor values
        qtr.read(sensorValues);
        for (uint8_t i = 0; i < SensorCount; i++)
        {
          if (sensorValues[i] > 2000)
          {
            valueLine[i] = 0;
          }
          else
          {
            valueLine[i] = 1;
          }
          Serial.print(position, BIN);
        }
        position = valueLine[0] + valueLine[1]*2 + valueLine[2]*4 + valueLine[3]*8 + valueLine[4]*16 + valueLine[5]*32 + valueLine[6]*64 + valueLine[7]*128;
        Serial.println(position , DEC);
        //position = ~ position;
        switch (position)
        {
          case 0b00000001: error = 16 + 2;   break;
          case 0b00000010: error = 12 + 2;   break;
          case 0b00000100: error = 8;   break;
          case 0b00001000: error = 4;   break;
          case 0b00010000: error = -4;   break;
          case 0b00100000: error = -8;   break;
          case 0b01000000: error = -12;   break;
          case 0b10000000: error = -16;   break;

          case 0b00000011: error = 14 + 2;   break;
          case 0b00000110: error = 10;   break;
          case 0b00001100: error = 6;   break;
          case 0b00011000: error = 0;   break;
          case 0b00110000: error = -6;   break;
          case 0b01100000: error = -10;   break;
          case 0b11000000: error = -14;   break;

          case 0b00000111: error = 12 + 2;   break;
          case 0b00001110: error = 8 + 2;   break;
          case 0b00011100: error = 4;   break;
          case 0b00111000: error = -4;   break;
          case 0b01110000: error = -8;   break;
          case 0b11100000: error = -12;   break;
          
          case 0b00001111: error = 10 + 2;   break;
          case 0b00011110: error = 6;   break;
          case 0b00111100: error = 0;   break;
          case 0b01111000: error = -6;   break;
          case 0b11110000: error = -10;   break;

          case 0b00011111: error = 8;   break;
          case 0b00111110: error = 4;   break;
          case 0b01111100: error = -4;   break;
          case 0b11111000: error = -8;   break;

          case 0b00111111: error = 6;   break;
          case 0b01111110: error = 0;   break;
          case 0b11111100: error = -6;   break;

          case 0b01111111: error = 4;   break;
          case 0b11111110: error = -4;   break;   
                  
          default: break;
        }
        motorController.move(80 + abs(error)*4);
        myservo.write(90 - error*2.5);
      }
    }
  } */
  // CODE PID DIGITAL
  qtr.read(sensorValues);
        for (uint8_t i = 0; i < SensorCount; i++)
        {
          if (sensorValues[i] > 2000)
          {
            valueLine[i] = 0;
          }
          else
          {
            valueLine[i] = 1;
          }
          Serial.print(position, BIN);
        }
        position = valueLine[0] + valueLine[1]*2 + valueLine[2]*4 + valueLine[3]*8 + valueLine[4]*16 + valueLine[5]*32 + valueLine[6]*64 + valueLine[7]*128;
        Serial.println(position , DEC);
        //position = ~ position;
        switch (position)
        {
          case 0b00000001: error = 16 + 2;   break;
          case 0b00000010: error = 12 + 2;   break;
          case 0b00000100: error = 8;   break;
          case 0b00001000: error = 4;   break;
          case 0b00010000: error = -4;   break;
          case 0b00100000: error = -8;   break;
          case 0b01000000: error = -12;   break;
          case 0b10000000: error = -16;   break;

          case 0b00000011: error = 14 + 2;   break;
          case 0b00000110: error = 10;   break;
          case 0b00001100: error = 6;   break;
          case 0b00011000: error = 0;   break;
          case 0b00110000: error = -6;   break;
          case 0b01100000: error = -10;   break;
          case 0b11000000: error = -14;   break;

          case 0b00000111: error = 12 + 2;   break;
          case 0b00001110: error = 8 + 2;   break;
          case 0b00011100: error = 4;   break;
          case 0b00111000: error = -4;   break;
          case 0b01110000: error = -8;   break;
          case 0b11100000: error = -12;   break;
          
          case 0b00001111: error = 10 + 2;   break;
          case 0b00011110: error = 6;   break;
          case 0b00111100: error = 0;   break;
          case 0b01111000: error = -6;   break;
          case 0b11110000: error = -10;   break;

          case 0b00011111: error = 8;   break;
          case 0b00111110: error = 4;   break;
          case 0b01111100: error = -4;   break;
          case 0b11111000: error = -8;   break;

          case 0b00111111: error = 6;   break;
          case 0b01111110: error = 0;   break;
          case 0b11111100: error = -6;   break;

          case 0b01111111: error = 4;   break;
          case 0b11111110: error = -4;   break;   
                  
          default: break;
        }
        motorController.move(80 + abs(error)*4);
        myservo.write(90 - error*2.5);
        Serial.println(90 -error*2.5);
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
