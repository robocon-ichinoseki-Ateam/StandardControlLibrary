#ifndef Steering_h
#define Steering_h

#include "mbed.h"
#include "ArduinoMacro.h"
#include "MovingMechanismConstants.h"
#include "Vector.h"

class Steering
{
public:
    Steering(mechanismConfig_t config, thresholdParam_t thresholdParam);
    void calculate(double velocityVector[3], Vector2 outputRate[4], double angle = 0.0f);
    
protected:
    mechanismConfig_t _config;
    thresholdParam_t _thresholdParam;
};

#endif //Steering_h