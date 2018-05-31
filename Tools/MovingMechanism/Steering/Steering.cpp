#include "Steering.h"

Steering::Steering(mechanismConfig_t config, thresholdParam_t thresholdParam) :
    _config(config), _thresholdParam(thresholdParam)
{
        double x = _config.width / 2;
    double y = _config.length / 2;

#warning [mm]? [m]?
    // 機体中心からホイールまでの距離を出す
    if(_config.radius == 0.0)
    {
        _config.radius = sqrt(x*x + y*y);
    }
    
    // ホイールの配置から回転の時のホイール角度を出す
    _config.theta = atan2(y, x);
}

void Steering::calculate(double velocityVector[3], double angle)
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
    
    // xy方向の入力をangle分回転
    velocityVector[0] = velocityVector[0] * cos(-angle) - velocityVector[1] * sin(-angle);
    velocityVector[1] = velocityVector[0] * sin(-angle) + velocityVector[1] * cos(-angle);
    
    // 各ホイールの速度の計算
#warning use _config.width & _config.length. rotationCorrection
    //v[0].x = velocityVector[0] - velocityVector[2] * sin(_config.theta + angle);
    
    v[0].x = velocityVector[0] - _config.radius * velocityVector[2] * sin(_config.theta);
    v[0].y = velocityVector[1] + _config.radius * velocityVector[2] * cos(_config.theta);
        
    v[1].x = velocityVector[0] - _config.radius * velocityVector[2] * cos(_config.theta);
    v[1].y = velocityVector[1] - _config.radius * velocityVector[2] * sin(_config.theta);
        
    v[2].x = velocityVector[0] + _config.radius * velocityVector[2] * sin(_config.theta);
    v[2].y = velocityVector[1] - _config.radius * velocityVector[2] * cos(_config.theta);
        
    v[3].x = velocityVector[0] + _config.radius * velocityVector[2] * cos(_config.theta);
    v[3].y = velocityVector[1] + _config.radius * velocityVector[2] * sin(_config.theta);
    
    // 最大値を格納
    for(int wheel = 0; wheel < 4; wheel++)
    {
        if(v[wheel].getMagnitude() > maxValue)
            maxValue = v[wheel].getMagnitude();
    }
    
    // 出力ガード処理
    for(int wheel = 0; wheel < 4; wheel++)
    {
        if(maxValue > _thresholdParam.maxOutput)
            v[wheel] = v[wheel] * _thresholdParam.maxOutput / maxValue;
            
        if(v[wheel].getMagnitude() < _thresholdParam.minOutput)
            v[wheel].set(0,0);
    }
}

Vector2 Steering::getWheelVelocity(short num)
{
    return v[num];
}