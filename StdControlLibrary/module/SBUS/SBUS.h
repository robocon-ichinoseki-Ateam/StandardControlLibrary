#ifndef SBUS_h
#define SBUS_h
#include "mbed.h"

class SBUS
{
public:
    SBUS(PinName tx, PinName rx);
    int16_t getData(uint8_t ch);
    int getStickVal(int axis);
    int getSwitchVal(int parm);

private:
    RawSerial sbus_;
    void sbusIrqRx ();
    int sbusIndex;
    unsigned int rcChannel[18];
    long map(long x, long in_min, long in_max, long out_min, long out_max); // From:Arduino.h
};

#endif