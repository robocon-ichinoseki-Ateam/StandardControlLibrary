#ifndef Omni_h
#define Omni_h

// mechanismConfig_t .option
#define OMNI_3WHEEL 3
#define OMNI_4WHEEL 4

class Omni : public BaseMovingMechanism
{
public:
    Omni(mechanismConfig_t config, thresholdParam_t thresholdParam, int wheelNum = OMNI_3WHEEL);
    void init(mechanismConfig_t config, thresholdParam_t thresholdParam, int wheelNum = OMNI_3WHEEL);
    
    void setRateMatrix(double rateArray[][3]);
    void calculate(double vx, double vy, double angularVelocity, double angle = 0.0);
    void calculate(double velocityVector[3], double angle = 0.0);
    
protected:
    void setDefaultRateMatrix();
    
protected:
    //int _option;
};

#endif //Omni_h