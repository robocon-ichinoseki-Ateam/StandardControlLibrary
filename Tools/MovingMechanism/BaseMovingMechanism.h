#ifndef BaseMovingMechanism_h
#define BaseMovingMechanism_h

#include "mbed.h"
#include "ArduinoMacro.h"
#include "MovingMechanismConstants.h"



class BaseMovingMechanism
{
public:
    BaseMovingMechanism(mechanismConfig_t config, thresholdParam_t thresholdParam, int wheelNum);
    void calculateBase(double velocityVector[3], double outputRate[]);
    
protected:
    void setRateMatrix(double matrix[][3]);
    
protected:
    mechanismConfig_t _config;
    thresholdParam_t _thresholdParam;
    int _wheelNum;
    
    double _rateMatrix[4][3];
    
};

#endif //BaseMovingMechanism_h