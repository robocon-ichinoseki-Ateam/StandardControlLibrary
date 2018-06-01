#include "MovingMechanism.h"

Omni::Omni(mechanismConfig_t config, thresholdParam_t thresholdParam) :
    BaseMovingMechanism(config, thresholdParam, config.option)
{
    v = new double[_wheelNum];
    _rateMatrix = new double*[_wheelNum];
    for (int i = 0; i < _wheelNum; i++) {
        _rateMatrix[i] = new double[3];
    }
    setDefaultRateMatrix();
}

void Omni::setRateMatrix(double rateMatrix[][3])
{
    for(int wheel = 0; wheel < _wheelNum; wheel++)
    {
        for(int element = 0; element < 3; element++)
        {
            _rateMatrix[wheel][element] = rateMatrix[wheel][element];
        }
    }
}

void Omni::calculateEach(double velocityVector[3])
{
    double maxValue = 0;
    
    for(int wheel = 0; wheel < _wheelNum; wheel++)
    {
        v[wheel] = 0;
        for (int element = 0; element < 3; element++) {
            v[wheel] += _rateMatrix[wheel][element] * velocityVector[element];
        }
        
        // 最大値を格納
        if(abs(v[wheel]) > maxValue)
            maxValue = abs(v[wheel]);
    }
    
    // 出力ガード処理
    for(int wheel = 0; wheel < _wheelNum; wheel++)
    {
        if(maxValue > _thresholdParam.maxOutput)
            v[wheel] = map<double>(v[wheel], -maxValue, maxValue, -_thresholdParam.maxOutput, _thresholdParam.maxOutput);
            
        if(abs(v[wheel]) < _thresholdParam.minOutput)
            v[wheel] = 0;
    }
}

void Omni::setDefaultRateMatrix()
{
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

double Omni::getWheelVelocity(short num)
{
    return *(v + num);
}