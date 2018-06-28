#include "VNH5019.h"

VNH5019::VNH5019(PinName pwm, PinName inA, PinName inB, float maxValue, bool isHighBrake):
    _pwm(pwm), _inA(inA), _inB(inB), _maxValue(maxValue), _isHighBrake(isHighBrake)
{
    setPeripd_us(50); // 20kHz
    write(0.0);
}

void VNH5019::setPeriod(float value)
{
    _pwm.period(value);
}

void VNH5019::setPeriod_ms(int ms)
{
    _pwm.period_ms(ms);
}

void VNH5019::setPeripd_us(int us)
{
    _pwm.period_us(us);
}

void VNH5019::write(float value)
{
    _value = guard(value, -_maxValue, _maxValue);
    
    if(value > 0)
    {
        _pwm = abs(_value / _maxValue);
        _inA = 1;
        _inB = 0;
    }
    else if(value < 0)
    {
        _pwm = abs(_value / _maxValue);
        _inA = 0;
        _inB = 1;
    }
    else
    {
        _pwm = 0.0;
        if(_isHighBrake)
        {
            _inA = 1;
            _inB = 1;
        }
        else
        {
            _inA = 0;
            _inB = 0;
        }
    }
}

float VNH5019::read()
{
    return _value;
}
