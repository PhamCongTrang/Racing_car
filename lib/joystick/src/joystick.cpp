#include "joystick.h"
#include "Arduino.h"

joystick::joystick(int _x, int _y, int _xmax, int _ymax, int _xmin, int _ymin)
{
    this->x = _x-(_xmax+_xmin)/2;
    this->y = _y-(_ymax+_ymin)/2;
    this->xmax = _xmax;
    this->ymax = _ymax;
    this->xmin = _xmin;
    this->ymin = _ymin;
    this->vel =  255*2/(_xmax+_xmin)*x;
    this->phi =  90 + 120/(_ymax-_ymin)*y;
}
