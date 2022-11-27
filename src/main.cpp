#include <Arduino.h>
#include "SPI.h"
#include "RF24.h"

#include "QTRSensors.h"

#include "joystick.h"

#include "LMotorController.h"
#include "Servo.h"
#include "SetPID.h"

// Define cac chan dieu khien dong co
#define SER 5 
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
const uint8_t SensorCount = 5;
uint16_t sensorValues[SensorCount];
int valueLine[5];

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
  qtr.setSensorPins((const uint8_t[]){A0, A1, A2, A3, A4}, SensorCount);
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
      }
        
      position = valueLine[0] + valueLine[1] * 2 + valueLine[2] * 4 + valueLine[3] * 8 + valueLine[4] * 16;
      //Serial.print(position);
      switch (position)
      {
        case 0b00000:  error = error / abs(error);  break;

        case 0b00001:  error = 16;  break;
        case 0b00010:  error = 8;  break;
        case 0b00100:  error = 0;  break;
        case 0b01000:  error = -8;  break;
        case 0b10000:  error = -16;  break;

        case 0b00011:  error = 12;  break;
        case 0b00110:  error = 4;  break;
        case 0b01100:  error = -4;  break;
        case 0b11000:  error = -12;  break;

        case 0b00111:  error = 12;  break;
        case 0b01110:  error = 4;  break;
        case 0b11100:  error = -4;  break;

        case 0b01111:  error = 12;  break;
        case 0b11110:  error = 4;  break;

        case 0b11111:  {if (error > 0)  error = 16;
                          else  error = -16; } break;
        
        default:  break;
      } //end switch case
      Serial.println(error);
      if (abs(error) == 1) // Check co lui
      { // Chay lui
        if ((millis() - lineout) > 1000)
        {
          myservo.write(90 + 30 * error); // dau servo
          motorController.move(-180);
          delay(500);                     // Tha troi xe 0,1s
          //motorController.move(100); // phanh
          Serial.print("lui"); Serial.println(millis() - lineout);
        }
        else
        {
          if (error > 0)  goc = error * 1.25;
          else  goc = error * 1.1;
          myservo.write(90 - 36 * error); // dau servo
          motorController.move(120); 
          Serial.println("Warning out ---");
        }
      } // End chay lui
      else 
      { // Chay tien
        lineout = millis();
        motorController.move(110 + abs(error * error) * 0.4);
        if (error > 0)  goc = error * 1.25;
        else  goc = error * 1.1;
        myservo.write(90 - goc * 2.25);
        Serial.print("Tien"); Serial.println(lineout);
      } // End chay tien
    }
    else //PID
    {
      qtr.read(sensorValues);
      for (uint8_t i = 0; i < SensorCount; i++)
        if (sensorValues[i] > 2000)  valueLine[i] = 1;
        else  valueLine[i] = 0;
      sum = valueLine[0] * (-2) + valueLine[1] * (-1) + valueLine[2] * (0) + valueLine[3] * (1) + valueLine[4] * 2;
      dem = valueLine[0] + valueLine[1] + valueLine[2] + valueLine[3] + valueLine[4];
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
 