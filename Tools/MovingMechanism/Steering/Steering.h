#ifndef Steering_h
#define Steering_h

#include "BaseMovingMechanism.h"

class Steering : public BaseMovingMechanism
{
public:
    Steering(mechanismConfig_t config, thresholdParam_t thresholdParam);
    
    virtual void calculateEach(double velocityVector[3]);
    Vector2 getWheelVector(short num);
    
protected:
    Vector2 v[4];
    //double length;
    double rotationCorrection;
};

#endif //Steering_h