#ifndef Mecanum_h
#define Mecanum_h

#include "BaseMovingMechanism.h"

// option
#define MECANUM_CROSS 0
#define MECANUM_SQUARE 1

class Mecanum : public BaseMovingMechanism
{
public:
    Mecanum(mechanismConfig_t config, thresholdParam_t thresholdParam);
    
    void setRateMatrix(double rateMatrix[4][3]);
    virtual void calculateEach(double velocityVector[3]);
    double getWheelVelocity(short num);
    
protected:
    void setDefaultRateMatrix();
    
protected:
    double _rateMatrix[4][3];
    double v[4];
};

#endif //Mecanum_h
