#ifndef BaseMovingMechanism_h
#define BaseMovingMechanism_h

#include "mbed.h"
#include "ArduinoMacro.h"
#include "MovingMechanismConstants.h"
#include "GenericFunctions.h"

class BaseMovingMechanism
{
public:
    BaseMovingMechanism(mechanismConfig_t config, thresholdParam_t thresholdParam, int wheelNum);
    double getWheelVelocity(short num);
    
protected:
    //void initBase(mechanismConfig_t config, thresholdParam_t thresholdParam, int wheelNum);
    void setRateMatrix(double matrix[][3]);
    void calculateBase(double vx, double vy, double angularVelocity);
    void calculateBase(double velocityVector[3]);
    
protected:
    mechanismConfig_t _config;
    thresholdParam_t _thresholdParam;
    int _wheelNum;
    
    double _rateMatrix[4][3];
    double v[4];
    
};

#endif //BaseMovingMechanism_h