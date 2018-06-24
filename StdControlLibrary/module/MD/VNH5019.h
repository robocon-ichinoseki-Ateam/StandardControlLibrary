#ifndef VNH5019_h
#define VNH5019_h

#include "mbed.h"
#include "GenericFunctions.h"

class VNH5019
{
public:
    VNH5019(PinName pwm, PinName inA, PinName inB, float maxValue, bool isHighBrake = false);
    void setPeriod(float value);
    void setPeriod_ms(int ms);
    void setPeripd_us(int us);
    void write(float value);
    float read();
    
    VNH5019& operator= (float value) {
        write(value);
        return *this;
    }

    VNH5019& operator= (VNH5019& rhs) {
        write(rhs.read());
        return *this;
    }
    
protected:
    float _maxValue, _value;
    bool _isHighBrake;
    PwmOut _pwm;
    DigitalOut _inA, _inB;
};
#endif //VNH5019_h
