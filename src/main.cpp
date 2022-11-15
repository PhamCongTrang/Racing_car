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
#define IN1 4
#define IN2 3

// setup MOTOR
LMotorController motorController(ENA, IN1, IN2);
Servo myservo;

// setup for RF 2Ghz
/*
const uint64_t pipe = 0x80E8ABC123LL; // địa chỉ phát
RF24 radio(9, 10);                    // thay 10 thành 53 với mega
int msg[3];
*/
// set up of line follow
QTRSensors qtr;
const uint8_t SensorCount = 5;
uint16_t sensorValues[SensorCount];

//----------void SETUP-------------------------------------
void setup()
{
  // put your setup code here, to run once:
/*
  // VoidSetup of rf 2.4ghz
  Serial.begin(9600);
  radio.begin();
  radio.setAutoAck(1);
  radio.setDataRate(RF24_2MBPS); // Tốc độ dữ liệu
  radio.setChannel(10);          // Đặt kênh
  radio.openReadingPipe(1, pipe);
  radio.startListening();
*/
  myservo.attach(SER);
  // configure the sensors
  qtr.setTypeRC();
  qtr.setSensorPins((const uint8_t[]){8, 9, 10, 11, 12}, SensorCount);
  qtr.setEmitterPin(2);

  // Call calibrate() 400 times to make calibration take about 10 seconds.
  for (uint16_t i = 0; i < 400; i++)
  {
    qtr.calibrate();
  }
}
// ----------void LOOP-------------------------------------
void loop()

{
  /*
  if (radio.available())
  {
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
        uint16_t position = qtr.readLineBlack(sensorValues);
        errpre = errnow;
        errnow = position; //Thay errnow = Hàm của Hoàng : vị trí tương đối của line so với điểm chính giữa
        dt = millis() - tpre;
        tpre = millis();
        P = Kp*errnow;
        I += Ki*errnow*dt;
        D = Kd*(errnow-errpre)/dt;
        motorController.move(255*(1-Kv*abs(D)));
        myservo.write(P + I + D);
      }
    }
  }*/
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
  Serial.print(position); Serial.print('\t');
  Serial.print(errnow); Serial.print('\t');
  Serial.println(P+90);
}
