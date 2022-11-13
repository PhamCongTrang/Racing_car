#include "joystick.h"
#include "Arduino.h"

joystick::joystick(float _x, float _y, float _xmax, float _ymax, float _xmin, float _ymin)
{
    this->x = _x-(_xmax+_xmin)/2;
    this->y = _y-(_ymax+_ymin)/2;
    this->xmax = _xmax;
    this->ymax = _ymax;
    this->xmin = _xmin;
    this->ymin = _ymin;
    this->vel =  static_cast<int>(255*2/(_xmax+_xmin)*x);
    this->phi =  static_cast<int>(90 + 60/(_ymax-_ymin)*y);
}
