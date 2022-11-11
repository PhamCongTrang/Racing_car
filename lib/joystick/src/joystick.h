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
    joystickControl(int _x, int _y, int _xmax, int _ymax, int _xmin, int _ymin)
    {
        x = _x;
        y = _y;
        xmin = _xmin;
        xmax = _xmax;
        ymin = _ymin;
        ymax = _ymax;
        ymin = _ymin;
    }
    void calc(int _vel, int _theta)
    {
        
    }

private:
    int _vel;
    int _theta;
}
#endif
