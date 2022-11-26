#include <Arduino.h>
#include "SPI.h"
#include "RF24.h"

#include "QTRSensors.h"

#include "joystick.h"

#include "LMotorController.h"
#include "Servo.h"
#include "SetPID.h"

// Define cac chan dieu khien dong co
#define SER 5 // Dao cho cho ENA
#define ENA 6
#define IN3 8
#define IN4 7

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
  qtr.setSensorPins((const uint8_t[]){A0, A1, A2, A3, A4, A5, 3,4}, SensorCount);
  qtr.setEmitterPin(2);
}

// ----------void LOOP-------------------------------------
void loop()
{ // void
  if (radio.available())
  { // Check avaiable
    radio.read(&msg, sizeof(msg));
    if (msg[2] == 1) 
    { // Control
      joystick obj(msg[0], msg[1], 1022, 1022, 0, 0);

      if (obj.vel > 10)
        v = 0.7 * obj.vel + 72.86;
      else if (obj.vel < -10)
        v = 0.7 * obj.vel - 72.86;
      else
        v = 0;
      motorController.move(v);
      myservo.write(obj.phi);
    } // End Control
    else // Line Following
    if(mode == 1) // DIGITAL
    {
      qtr.read(sensorValues);
      for (uint8_t i = 0; i < SensorCount; i++)
      {
        if (sensorValues[i] > 2000)  valueLine[i] = 0;
        else  valueLine[i] = 1;
        Serial.print(valueLine[i]);
      }
        
      position = valueLine[0] + valueLine[1] * 2 + valueLine[2] * 4 + valueLine[3] * 8 + valueLine[4] * 16 + valueLine[5] * 32 + valueLine[6] * 64 + valueLine[7] * 128;
      //Serial.print(position);
      switch (position)
      {
        case 0b00000000:  error = error / abs(error);  break;
        case 0b00000001:  error = 16;  break;
        case 0b00000010:  error = 12 + 4;  break;
        case 0b00000100:  error = 8 + 3;  break;
        case 0b00001000:  error = 4 + 3;  break;
        case 0b00010000:  error = -4 - 3;  break;
        case 0b00100000:  error = -8 - 3;  break;
        case 0b01000000:  error = -12 - 4;  break;
        case 0b10000000:  error = -16;  break;

        case 0b00000011:  error = 14 + 2;  break;
        case 0b00000110:  error = 10 + 4;  break;
        case 0b00001100:  error = 6 + 3;  break;
        case 0b00011000:  error = 0;  break;
        case 0b00110000:  error = -6 - 3;  break;
        case 0b01100000:  error = -10 - 4;  break;
        case 0b11000000:  error = -14 - 2;  break;

        case 0b00000111:  error = 12 + 4;  break;
        case 0b00001110:  error = 8 + 3;  break;
        case 0b00011100:  error = 4 + 2;  break;
        case 0b00111000:  error = -4 + 2;  break;
        case 0b01110000:  error = -8 - 3;  break;
        case 0b11100000:  error = -12 - 4;  break;

        case 0b00001111:  error = 10 + 5;  break;
        case 0b00011110:  error = 6 + 4;  break;
        case 0b00111100:  error = 0;  break;
        case 0b01111000:  error = -6 - 4;  break;
        case 0b11110000:  error = -10 - 5;  break;

        case 0b00011111:  error = 8 + 5;  break;
        case 0b00111110:  error = 4 + 3;  break;
        case 0b01111100:  error = -4 - 3;  break;
        case 0b11111000:  error = -8 - 5;  break;

        case 0b00111111:  error = 6 + 6;  break;
        case 0b01111110:  error = 0;  break;
        case 0b11111100:  error = -6 - 6;  break;

        case 0b01111111:  error = 4 + 4;  break;
        case 0b11111110:  error = -4 - 4;  break;

        case 0b11111111:  {if (error > 0)  error = 16;
                          else  error = -16; } break;
        
        default:  break;
      } //end switch case
      Serial.println(error);
      if (abs(error) == 1) // Check co lui
      { // Chay lui
        motorController.move(-130);
        myservo.write(90 + 30 * error); // dau servo
        delay(600);                     // Tha troi xe 0,1s
        motorController.move(30); // phanh
      } // End chay lui
      else 
      { // Chay tien
        motorController.move(100 + abs(error * error) * 0.32);
        if (error > 0)  goc = error * 1.25;
        else  goc = error * 1.1;
        myservo.write(90 - goc * 2.25);
      } // End chay tien
    }
    else //PID
    {
      qtr.read(sensorValues);
      for (uint8_t i = 0; i < SensorCount; i++)
        if (sensorValues[i] > 2000)  valueLine[i] = 1;
        else  valueLine[i] = 0;
      sum = valueLine[0] * (-4) + valueLine[1] * (-3) + valueLine[2] * (-2) + valueLine[3] * (-1) + valueLine[4] * 1 + valueLine[5] * 2 + valueLine[6] * 3 + valueLine[7] * 4;
      dem = valueLine[0] + valueLine[1] + valueLine[2] + valueLine[3] + valueLine[4] + valueLine[5] + valueLine[6] + valueLine[7];
      if (dem != 0)  errnow = sum / dem;
      else  errnow = errpre / abs(errpre) * 40 / Kp;

      if (errnow == 0 && dem == 0)
      { // Chay lui
        motorController.move(-120);
        myservo.write(90 + 30 * errpre / abs(errpre)); // dau servo
        delay(500);                                    // Tha troi xe 0,1s
        motorController.move(30);
      } // End chay lui
      else
      { // Chay tien
        dt = millis() - tpre;
        tpre = millis();

        P = Kp * errnow;
        I += Ki * errnow * dt;
        D = Kd * (errnow - errpre) / dt;

        errpre = errnow;

        motorController.move(90 + abs(P + I + D));
        myservo.write(-(P + I + D) + 92); // Dau servo
      } // End chay tien
    } // End PID
  } // End check avaiable
} // End void
 