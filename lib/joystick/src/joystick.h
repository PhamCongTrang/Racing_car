 #ifndef joystick_h
#define joystick_h
#include "Arduino.h"
class joystick
{
public:
    float x;
    float y;
    float xmax;
    float ymax;
    float xmin;
    float ymin;
    joystick(float _x, float _y, float _xmax, float _ymax, float _xmin, float _ymin);
    float vel;
    float phi;
};
#endif
