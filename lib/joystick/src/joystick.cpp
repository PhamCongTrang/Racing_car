#include "joystick.h"
#include "Arduino.h"

joystick::joystick(int _x, int _y, int _xmax, int _ymax, int _xmin, int _ymin)
{
    int x = _x;
    int y = _y;
    int xmax = _xmax;
    int ymax = _ymax;
    int xmin = _xmin;
    int ymin = _ymin;
}
void calc()
{
    this->xNew = (this->x - (this->xmax - this->xmin)/2)/(this->xmax-this-> xmin)/2;
    this->yNew = (this->y - (this->ymax - this->ymin/2))/(this->ymax-this->ymin)/2;
    this->vel = 255*sqrt(pow(this->xNew,2)+pow(this->yNew,2));
    this->phi = atan(this->yNew/this->x);
     
}
