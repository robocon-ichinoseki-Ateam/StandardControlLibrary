#include "Potentiometer.h"

Potentiometer::Potentiometer(PinName pin, double maxValue, double startValue):
    _pin(pin), _maxValue(maxValue), _startValue(startValue)
{
    
}

double Potentiometer::getValue()
{
    return ( _pin.read() );
}

double Potentiometer::getAbsoluteAngle()
{
    return ( getValue() * _maxValue );
}

double Potentiometer::getRelativeAngle()
{
    return ( (getValue() - _startValue) * _maxValue );
}