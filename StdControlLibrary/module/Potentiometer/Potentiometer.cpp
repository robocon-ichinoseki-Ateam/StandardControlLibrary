#include "Potentiometer.h"

Potentiometer::Potentiometer(PinName pin):
    _pin(pin), _minValue(0.0), _maxValue(1.0)
{
    
}

Potentiometer::Potentiometer(PinName pin, double minValue, double maxValue):
    _pin(pin), _minValue(minValue), _maxValue(maxValue)
{
    
}

void Potentiometer::setRange(double minValue, double maxValue)
{
    _minValue = minValue;
    _maxValue = maxValue;
}

double Potentiometer::getRawValue()
{
    return ( _pin.read() );
}

double Potentiometer::getValue()
{
    return ( guard(map<double>(getRawValue(), _minValue, _maxValue, 0.0, 1.0), 0.0, 1.0) );
}