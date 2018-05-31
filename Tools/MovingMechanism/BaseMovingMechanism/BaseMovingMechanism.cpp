#include "BaseMovingMechanism.h"

BaseMovingMechanism::BaseMovingMechanism(mechanismConfig_t config, thresholdParam_t thresholdParam, int wheelNum):
    _config(config), _thresholdParam(thresholdParam), _wheelNum(wheelNum)
{
    
}

/*
BaseMovingMechanism::initBase(mechanismConfig_t config, thresholdParam_t thresholdParam)
{
    _config = config;
    _thresholdParam = thresholdParam;
}
*/

void BaseMovingMechanism::calculateBase(double vx, double vy, double angularVelocity)
{
    double velocityVector[3] = {vx, vy, angularVelocity};
    calculateBase(velocityVector);
}

void BaseMovingMechanism::calculateBase(double velocityVector[3])
{
    double maxValue = 0;
    
    // 入力ガード処理
    for(int element = 0; element < 3; element++)
    {
        if(velocityVector[element] > _thresholdParam.maxInput)
            velocityVector[element] = _thresholdParam.maxInput;
            
        if(velocityVector[element] < _thresholdParam.minInput)
            velocityVector[element] = 0;
    }
    
    // 線形変換
    for(int wheel = 0; wheel < _wheelNum; wheel++)
    {
        for (int element = 0; element < 3; element++) {
            v[wheel] += _rateMatrix[wheel][element] * velocityVector[wheel];
        }
        
        // 最大値を格納
        if(abs(v[wheel]) > maxValue)
            maxValue = v[wheel];
    }
    
    // 出力ガード処理
    for(int wheel = 0; wheel < _wheelNum; wheel++)
    {
        if(maxValue > _thresholdParam.maxOutput)
            v[wheel] = map<double>(v[wheel], -maxValue, maxValue, -_thresholdParam.maxOutput, _thresholdParam.maxOutput);
            
        if(v[wheel] < _thresholdParam.minOutput)
            v[wheel] = 0;
    }
}

double BaseMovingMechanism::getWheelVelocity(short num)
{
    return v[num];
}

