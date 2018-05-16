#ifndef Potentiometer_h
#define Potentiometer_h

#include "mbed.h"

class Potentiometer
{
public:
    Potentiometer(PinName pin, double maxValue, double startValue);
    double getValue();
    double getAbsoluteAngle();
    double getRelativeAngle();
    
protected:
    AnalogIn _pin;
    double _maxValue;
    double _startValue;
    
};

#endif //Potentiometer_h
