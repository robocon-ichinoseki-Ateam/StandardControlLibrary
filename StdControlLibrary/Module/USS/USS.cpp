#include "USS.h"

USS::USS(PinName echoPin, PinName trigPin, double timeout) : _echoPin(echoPin), _trigPin(trigPin), _timeout(timeout)
{
    _echoPin.mode(PullDown);
    _echoPin.rise(this, &USS::isr_rise);
    _echoPin.fall(this, &USS::isr_fall);
    TrigerTiming.attach(this, &USS::Triger, 0.060);
}

void USS::Triger()
{
    _trigPin = 1;
    wait_us(15);
    _trigPin = 0;
}

double USS::calcuTimeOfDistance(double distance)
{
    return (2 * distance) / 343;
}

double USS::calcuTimeOfDistance_ms(double distance)
{
    return calcuTimeOfDistance(distance * 1000);
}

double USS::calcuTimeOfDistance_us(double distance)
{
    return calcuTimeOfDistance(distance * 1000000);
}

void USS::setAutoUpdate(bool isOn)
{
    _isAutoUpdate = isOn;
}

void USS::start()
{
    //    _trigPin = 1;
    //    wait_us(15);
    //    _trigPin = 0;
}

void USS::isr_rise()
{
    _timer.start();
    _timeoutTimer.attach(this, &USS::timeout, _timeout);
}

void USS::isr_fall()
{
    _timer.stop();
    if (_timer.read() < _timeout)
    {
        if (_timer.read() != 0)
            _distance = (_timer.read() * 343) / 2;
        //        _distance = _timer.read();

        //        _distance = _timer.read_us() * 0.000170;
        _isData = true;

        _timer.reset();

        if (_isAutoUpdate)
        {
            start();
        }
    }
    else
    {
        _timer.reset();
        _distance = 0.0;
        _isData = true;
        start();
    }
}

void USS::timeout()
{
    _timer.stop();
    _timer.reset();
    _timeoutTimer.detach();
    //_distance = 0.0;
    _isData = true;

    if (_isAutoUpdate)
    {
        start();
    }
}

bool USS::isData()
{
    return _isData;
}

double USS::getDistance()
{
    _isData = false;
    return _distance;
}

// Option
void USS::rise(void (*fptr)(void))
{
    _echoPin.rise(fptr);
}
void USS::fall(void (*fptr)(void))
{
    _echoPin.fall(fptr);
}