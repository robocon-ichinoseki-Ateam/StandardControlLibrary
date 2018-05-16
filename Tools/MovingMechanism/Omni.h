#ifndef Omni_h
#define Omni_h

// mechanismConfig_t .option
#define OMNI_3WHEEL 3
#define OMNI_4WHEEL 4

class Omni : public BaseMovingMechanism
{
public:
    Omni(mechanismConfig_t config, thresholdParam_t thresholdParam, int option = OMNI_3WHEEL);
    void setRateMatrix(double rateArray[4][3]);
    void calculate(double velocityVector[3], double outputRate[], double angle);
    
protected:
    void setDefaultRateMatrix(double angle = 0.0f);
    
protected:
    //int _option;
};

#endif //Omni_h