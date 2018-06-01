#ifndef Omni_h
#define Omni_h

#include "BaseMovingMechanism.h"

// mechanismConfig_t .option
#define OMNI_3WHEEL 3
#define OMNI_4WHEEL 4

class Omni : public BaseMovingMechanism
{
public:
    Omni(mechanismConfig_t config, thresholdParam_t thresholdParam);
    
    void setRateMatrix(double rateMatrix[][3]);
    virtual void calculateEach(double velocityVector[3]);
    double getWheelVelocity(short num);
    
protected:
    void setDefaultRateMatrix();
    
protected:
    //int _option;
    double **_rateMatrix;
    double *v;
};

#endif //Omni_h