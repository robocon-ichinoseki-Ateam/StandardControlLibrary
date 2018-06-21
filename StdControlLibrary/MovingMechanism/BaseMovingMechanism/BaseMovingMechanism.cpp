#include "BaseMovingMechanism.h"

BaseMovingMechanism::BaseMovingMechanism(mechanismConfig_t config, thresholdParam_t thresholdParam, int wheelNum):
    _config(config), _thresholdParam(thresholdParam), _wheelNum(wheelNum)
{

}

void BaseMovingMechanism::calculate(double vx, double vy, double angularVelocity, double angle)
{
    double velocityVector[3] = {vx, vy, angularVelocity};
    calculate(velocityVector, angle);
}

void BaseMovingMechanism::calculate(double velocityVector[3], double angle)
{
    _angle = angle;
    
    // 入力ガード処理
    for(int element = 0; element < 3; element++)
    {
        if(abs(velocityVector[element]) > _thresholdParam.maxInput)
            velocityVector[element] = _thresholdParam.maxInput * signOf(velocityVector[element]);
            
        if(abs(velocityVector[element]) < _thresholdParam.minInput)
            velocityVector[element] = 0;
    }
    
    // xy方向の入力をangle分回転
    double v[3];
    v[0] = velocityVector[0] * cos(-angle) - velocityVector[1] * sin(-angle);
    v[1] = velocityVector[0] * sin(-angle) + velocityVector[1] * cos(-angle);
    v[2] = velocityVector[2];
    
    // 出力を計算する
    calculateEach(v);
}
