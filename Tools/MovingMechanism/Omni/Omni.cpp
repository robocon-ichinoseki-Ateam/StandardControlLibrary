#include "MovingMechanism.h"

Omni::Omni(mechanismConfig_t config, thresholdParam_t thresholdParam, int wheelNum) :
    BaseMovingMechanism(config, thresholdParam, wheelNum)//, _option(option)
{
    setDefaultRateMatrix();
}
    
void Omni::setRateMatrix(double rateMatrix[][3])
{
    for(int motor = 0; motor < _wheelNum; motor++)
    {
        for(int element = 0; element < 3; element++)
        {
            _rateMatrix[motor][element] = rateMatrix[motor][element];
        }
    }
}


void Omni::calculate(double vx, double vy, double angularVelocity, double angle)
{
    double velocityVector[3] = {vx, vy, angularVelocity};
    calculate(velocityVector, angle);
}

void Omni::calculate(double velocityVector[3], double angle)
{
    // xy方向の入力をangle分回転
    velocityVector[0] = velocityVector[0] * cos(-angle) - velocityVector[1] * sin(-angle);
    velocityVector[1] = velocityVector[0] * sin(-angle) + velocityVector[1] * cos(-angle);
    
    calculateBase(velocityVector);
}

void Omni::setDefaultRateMatrix()
{
    // for Omni
    
    double fwa = _config.theta;
    
    if(_wheelNum == 3)
    {
        double buf_rateMatrix[3][3] = 
        {
            {-sin(fwa + (oneThirdrPi * 0)), cos(fwa + (oneThirdrPi * 0)), _config.radius},
            {-sin(fwa + (oneThirdrPi * 2)), cos(fwa + (oneThirdrPi * 2)), _config.radius},
            {-sin(fwa + (oneThirdrPi * 4)), cos(fwa + (oneThirdrPi * 4)), _config.radius}
        };
        
        setRateMatrix(buf_rateMatrix);
    }
    if(_wheelNum == 4)
    {
        double buf_rateMatrix[4][3] = 
        {
            {-sin(fwa + (halfPi * 0)), cos(fwa + (halfPi * 0)), _config.radius},
            {-sin(fwa + (halfPi * 1)), cos(fwa + (halfPi * 1)), _config.radius},
            {-sin(fwa + (halfPi * 2)), cos(fwa + (halfPi * 2)), _config.radius},
            {-sin(fwa + (halfPi * 3)), cos(fwa + (halfPi * 3)), _config.radius}
        };
        setRateMatrix(buf_rateMatrix);
    }

}