#ifndef Potentiometer_h
#define Potentiometer_h

#include "mbed.h"
#include "GenericFunctions.h"

class Potentiometer
{
public:
    Potentiometer(PinName pin);
    Potentiometer(PinName pin, double minValue, double maxValue);
    void setRange(double minValue, double maxValue);
    double getRawValue();
    double getValue();
    
protected:
    AnalogIn _pin;
    double _minValue;
    double _maxValue;
};

#endif //Potentiometer_h
