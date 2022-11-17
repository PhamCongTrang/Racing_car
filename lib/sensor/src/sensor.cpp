#include "sensor.h"
#include "Arduino.h"

joystick::sensor(int _x, int _y, int _z, int _t);
{
    this->ln0 = _x;
    this->ln1 = _y;
    this->ln2 = _z;
    this->ln3 = _t;
    this->phi =  static_cast<int>(90 + 80/(_ymax-_ymin)*y);
    int pos = (_x)*1 + (_y)*2 + (_z)*4 + (_t)*8;
    switch (Sensor)
    {
    case 0b1111: error = 4;  break; // full black
    case 0b0000: error = 0;  break; // full white
    


    default : error = lastErr; break;
      }
}
