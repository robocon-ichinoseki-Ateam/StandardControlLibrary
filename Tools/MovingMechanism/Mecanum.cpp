#include "MovingMechanism.h"

Mecanum::Mecanum(mechanismConfig_t config, thresholdParam_t thresholdParam, int option) :
    BaseMovingMechanism(config, thresholdParam, 4), _option(option)
{
    setDefaultRateMatrix();
}
    
void Mecanum::setRateMatrix(double rateMatrix[4][3])
{
    for(int motor = 0; motor < _wheelNum; motor++)
    {
        for(int element = 0; element < 3; element++)
        {
            _rateMatrix[motor][element] = rateMatrix[motor][element];
        }
    }
}

void Mecanum::calculate(double velocityVector[3], double outputRate[], double angle)
{
    setDefaultRateMatrix(angle);
    calculateBase(velocityVector, outputRate);
}

#warning mechanismConfig_t .theta とangleに対応させる
void Mecanum::setDefaultRateMatrix(double angle)
{
    // for mecanum
    int x_option = 1;
    if(_option == MECANUM_SQUARE)
        x_option = -1;
    double buf_rateMatrix[4][3] = 
    {
        {-1 * x_option,  1, _config.radius},
        {-1 * x_option, -1, _config.radius},
        { 1 * x_option, -1, _config.radius},
        { 1 * x_option,  1, _config.radius}
    };
    setRateMatrix(buf_rateMatrix);
}