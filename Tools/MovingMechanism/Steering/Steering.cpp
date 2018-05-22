#include "Steering.h"

Steering::Steering(mechanismConfig_t config, thresholdParam_t thresholdParam) :
    _config(config), _thresholdParam(thresholdParam)
{
    
}

void Steering::calculate(double velocityVector[3], Vector2 outputRate[4], double angle)
{
    double v[3];
    Vector2 bufOutputRate[4];
    
    // 理論出力レート値が実際の範囲越えを起こしたかを格納するフラグ変数
    bool isOverflowOfOutputRate = false;

    // 最大値を格納 [0-_thresholdParam.maxOutput]
    double MaxAbsOutputRate = 0;
    
    // 閾値未満切り捨て、ガード処理
    for(int element = 0; element < 3; element++)
    {
        if(abs(velocityVector[element]) < _thresholdParam.minInput)
            velocityVector[element] = 0;
        if(abs(velocityVector[element]) > _thresholdParam.maxInput)
            velocityVector[element] = _thresholdParam.maxInput;
        
        v[element] = velocityVector[element];
    }

#warning use wheelRadius
    
    bufOutputRate[0].x = v[0] - _config.wheelRadius * v[2] * sin(_config.theta + angle);
    bufOutputRate[0].y = v[1] + _config.wheelRadius * v[2] * cos(_config.theta + angle);
        
    bufOutputRate[1].x = v[0] - _config.wheelRadius * v[2] * cos(_config.theta + angle);
    bufOutputRate[1].y = v[1] - _config.wheelRadius * v[2] * sin(_config.theta + angle);
        
    bufOutputRate[2].x = v[0] + _config.wheelRadius * v[2] * sin(_config.theta + angle);
    bufOutputRate[2].y = v[1] - _config.wheelRadius * v[2] * cos(_config.theta + angle);
        
    bufOutputRate[3].x = v[0] + _config.wheelRadius * v[2] * cos(_config.theta + angle);
    bufOutputRate[3].y = v[1] + _config.wheelRadius * v[2] * sin(_config.theta + angle);
    
    // 閾値処理
    for(int wheelNum = 0; wheelNum < 4; wheelNum++)
    {
        if(bufOutputRate[wheelNum].getMagnitude() < _thresholdParam.minOutput)
            bufOutputRate[wheelNum].set(0.0f, 0.0f);
            
        if(bufOutputRate[wheelNum].getMagnitude() > _thresholdParam.maxOutput)
            isOverflowOfOutputRate = true;
        
        MaxAbsOutputRate = bufOutputRate[wheelNum].getMagnitude();
    }
    
    for(int wheelNum = 0; wheelNum < 4; wheelNum++)
    {
#warning check points
        if(isOverflowOfOutputRate)
        {
            outputRate[wheelNum] = bufOutputRate[wheelNum] * _thresholdParam.maxOutput / MaxAbsOutputRate;
        }
        else
        {
            outputRate[wheelNum] = bufOutputRate[wheelNum];
        }    
    }
}