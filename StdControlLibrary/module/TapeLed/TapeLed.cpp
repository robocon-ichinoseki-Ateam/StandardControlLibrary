#include "TapeLed.h"

TapeLed::TapeLed(PinName redPin, PinName greenPin, PinName bluePin):
    _redPin(redPin), _greenPin(greenPin), _bluePin(bluePin)
{
    
}

void TapeLed::setParam(int red, int green, int blue, float spd)
{
    if (red >= 0)
        _ledParam[0] = red;
    if (green >= 0)
        _ledParam[1] = green;
    if (blue >= 0)
        _ledParam[2] = blue;
    if (spd >= 0)
        _ledParam[3] = spd;
}

void TapeLed::light()
{
    if (_ledParam[3] > 0)
    {
        isLedTickOn = true;
        tickState = false;
        ledTicker.attach(this, &TapeLed::ledTick, 1.0f / _ledParam[3]);
    }
    else
    {
        if(isLedTickOn)
        {
            ledTicker.detach();
            isLedTickOn = false;
        }
        
        for(int i = 0; i < 3; i++)
        {
            setLed(i, _ledParam[i]);
        }
    }
}

void TapeLed::setLed(int num, bool isOn)
{
    switch(num)
    {
        case 0: _redPin   = isOn; break;
        case 1: _greenPin = isOn; break;
        case 2: _bluePin  = isOn; break;
        
    }
}

void TapeLed::ledTick()
{
    tickState = !tickState;
    for(int i = 0; i < 3; i++)
    {
        setLed(i, (_ledParam[i] & tickState));
    }
}



