#include "MovingMechanism.h"

Mecanum::Mecanum(mechanismConfig_t config, thresholdParam_t thresholdParam) :
    BaseMovingMechanism(config, thresholdParam, 4)
{
    setDefaultRateMatrix();
}
    
void Mecanum::setRateMatrix(double rateMatrix[4][3])
{
    for(int wheel = 0; wheel < _wheelNum; wheel++)
    {
        for(int element = 0; element < 3; element++)
        {
            _rateMatrix[wheel][element] = rateMatrix[wheel][element];
        }
    }
}

void Mecanum::calculateEach(double velocityVector[3])
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

//Todo: mechanismConfig_t .thetaに対応させる
void Mecanum::setDefaultRateMatrix()
{
    int x_option = 1;
    
    double x = _config.width / 2;
    double y = _config.length / 2;
    
    // 機体中心からホイールまでの距離
    double length = sqrt(x*x + y*y);

    // 理想的なメカナムホイールの配置（45deg）からのズレの度合い
    double rotationCorrection = cos(atan2(y, x) - PI / 4); 
    
    if(_config.option == MECANUM_SQUARE)
        x_option = -1;
    
    double buf_rateMatrix[4][3] = 
    {
        {-1 * x_option,  1, length * rotationCorrection},
        {-1 * x_option, -1, length * rotationCorrection},
        { 1 * x_option, -1, length * rotationCorrection},
        { 1 * x_option,  1, length * rotationCorrection}
    };
    
    setRateMatrix(buf_rateMatrix);
}

double Mecanum::getWheelVelocity(short num)
{
    return v[num];
}