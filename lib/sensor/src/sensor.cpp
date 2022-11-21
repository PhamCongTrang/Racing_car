#include "sensor.h"
#include "Arduino.h"

sensor::sensor(int _x, int _y, int _z, int _t)
{
    this->ln0 = _x;
    this->ln1 = _y;
    this->ln2 = _z;
    this->ln3 = _t;
    this->pos = (_x)*1 + (_y)*2 + (_z)*4 + (_t)*8;
    switch (pos)
    {
    case 0b1001: this->error = 2;  break; // full black
    case 0b1101: this->error = 1;  break;
    case 0b0110: this->error = 0;  break;
    case 0b1100: this->error = -1;  break;
    case 0b1000: this->error = -2;  break;
    default : this->error = this->lastErr; break;
    }
    this->lastErr = error;
    this->phi = static_cast<int>(90 - 15*this->error);
    
}
