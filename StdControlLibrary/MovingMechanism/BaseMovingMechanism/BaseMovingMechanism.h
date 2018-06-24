#ifndef BaseMovingMechanism_h
#define BaseMovingMechanism_h

#include "mbed.h"
#include "GenericFunctions.h"
#include "MovingMechanismConstants.h"
#include "Vector.h"

class BaseMovingMechanism
{
public:
    BaseMovingMechanism(mechanismConfig_t config, thresholdParam_t thresholdParam, int wheelNum);
    void calculate(double vx, double vy, double angularVelocity, double angle = 0.0);
    void calculate(double velocityVector[3], double angle = 0.0);
    
protected:
    virtual void calculateEach(double velocityVector[3]) = 0;
    
protected:
    mechanismConfig_t _config;
    thresholdParam_t _thresholdParam;
    int _wheelNum;
    double _angle;
};

#endif //BaseMovingMechanism_h