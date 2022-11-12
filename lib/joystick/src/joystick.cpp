#include "joystick.h"
#include "Arduino.h"

joystick::joystick(float _x, float _y, float _xmax, float _ymax, float _xmin, float _ymin)
{
    this->x = _x;
    this->y = _y;
    this->xmax = _xmax;
    this->ymax = _ymax;
    this->xmin = _xmin;
    this->ymin = _ymin;
    this->vel = 255*sqrt(pow(x,2)+pow(y,2))/sqrt(pow(xmax,2)+pow(ymax,2));
    this->phi = atan(y/x);    
}
