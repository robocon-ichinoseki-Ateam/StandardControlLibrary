#include "MovingMechanism.h"

Omni::Omni(mechanismConfig_t config, thresholdParam_t thresholdParam, int option) :
    BaseMovingMechanism(config, thresholdParam, OMNI_3WHEEL)//, _option(option)
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

void Omni::calculate(double velocityVector[3], double outputRate[], double angle)
{
    setDefaultRateMatrix(angle);
    calculateBase(velocityVector, outputRate);
}

void Omni::setDefaultRateMatrix(double angle)
{
    // for Omni
    
    double fwa = _config.theta;
    double buf_rateMatrix[3][3]= 
    {
        {-sin(fwa + (oneThirdrPi * 0 + angle)), cos(fwa + (oneThirdrPi * 0 + angle)), _config.radius},
        {-sin(fwa + (oneThirdrPi * 2 + angle)), cos(fwa + (oneThirdrPi * 2 + angle)), _config.radius},
        {-sin(fwa + (oneThirdrPi * 4 + angle)), cos(fwa + (oneThirdrPi * 4 + angle)), _config.radius}
    };
    setRateMatrix(buf_rateMatrix);
}