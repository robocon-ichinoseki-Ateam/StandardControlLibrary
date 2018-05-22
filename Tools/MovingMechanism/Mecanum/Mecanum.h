#ifndef Mecanum_h
#define Mecanum_h

// option
#define MECANUM_CROSS 0
#define MECANUM_SQUARE 1

class Mecanum : public BaseMovingMechanism
{
public:
    Mecanum(mechanismConfig_t config, thresholdParam_t thresholdParam, int option = MECANUM_CROSS);
    void setRateMatrix(double rateArray[4][3]);
    void calculate(double velocityVector[3], double outputRate[], double angle);
    
protected:
    void setDefaultRateMatrix(double angle = 0.0f);
    
protected:
    int _option;
    
};

#endif //Mecanum_h
