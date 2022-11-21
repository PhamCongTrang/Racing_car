#ifndef sensor_h
#define sensor_h
#include "Arduino.h"
class sensor
{
public:
    int ln0;
    int ln1;
    int ln2;
    int ln3;
    int error;
    int pos;
    int lastErr;
    sensor(int _x, int _y, int _z, int _t);
    float phi;
};
#endif
