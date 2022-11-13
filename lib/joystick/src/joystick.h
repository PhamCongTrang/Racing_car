 #ifndef joystick_h
#define joystick_h
#include "Arduino.h"
class joystick
{
public:
    int x;
    int y;
    int xmax;
    int ymax;
    int xmin;
    int ymin;
    joystick(int _x, int _y, int _xmax, int _ymax, int _xmin, int _ymin);
    int vel;
    int phi;
};
#endif
