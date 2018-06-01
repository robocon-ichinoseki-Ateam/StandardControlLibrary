#ifndef TapeLed_h
#define TapeLed_h

#include "mbed.h"

class TapeLed
{
public:
    TapeLed(PinName redPin, PinName greenPin, PinName bluePin);
    void setParam(int red, int green, int blue, float spd);
    void light();
    
protected:
    void setLed(int num, bool isOn);
    void ledTick();
    
  
protected:
    Ticker ledTicker;
    DigitalOut _redPin, _greenPin, _bluePin;
    int _ledParam[4];
    bool isLedTickOn;
    bool tickState;
};

#endif //TapeLed_h
