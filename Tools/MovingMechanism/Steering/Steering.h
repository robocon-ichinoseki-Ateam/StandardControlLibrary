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
    //void init(mechanismConfig_t config, thresholdParam_t thresholdParam);
    
    void calculate(double velocityVector[3], double angle = 0.0f);
    Vector2 getWheelVelocity(short num);
    
protected:
    mechanismConfig_t _config;
    thresholdParam_t _thresholdParam;
    
    Vector2 v[4];
    double length;
    double rotationCorrection;
};

#endif //Steering_h