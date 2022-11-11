#ifndef joystick
#define joystick
#include <Arduino.h>
class joystickControl
{
public:
    int x;
    int y;
    int xmax;
    int ymax;
    int xmin;
    int ymin;

private:
    int _vel;
    int _theta;
    joystickControl(int _x, int _y, int _xmax, int _ymax, int _xmin, int _ymin)
    {
        x = _x;
        y = _y;
        xmin = _x;
        xmax = _xmax;
        ymin = _ymin;
        ymax = _ymax;
        ymin = ymin;
    }
}
#endif
