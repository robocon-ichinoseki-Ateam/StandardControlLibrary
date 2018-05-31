#include "MovingMechanism.h"

Mecanum::Mecanum(mechanismConfig_t config, thresholdParam_t thresholdParam, int option) :
    BaseMovingMechanism(config, thresholdParam, 4), _option(option)
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

void Mecanum::calculate(double vx, double vy, double angularVelocity, double angle)
{
    double velocityVector[3] = {vx, vy, angularVelocity};
    calculate(velocityVector, angle);
}

void Mecanum::calculate(double velocityVector[3], double angle)
{
    // xy方向の入力をangle分回転
    velocityVector[0] = velocityVector[0] * cos(-angle) - velocityVector[1] * sin(-angle);
    velocityVector[1] = velocityVector[0] * sin(-angle) + velocityVector[1] * cos(-angle);
    
    calculateBase(velocityVector);
}

#warning mechanismConfig_t .thetaに対応させる
void Mecanum::setDefaultRateMatrix()
{
    // for mecanum
    int x_option = 1;
    
    double x = _config.width / 2;
    double y = _config.length / 2;
    
    // 機体中心からホイールまでの距離
#warning [mm]? [m]?
    double length = sqrt(x*x + y*y);

    // 理想的なメカナムホイールの配置（45deg）からのズレの度合い
    double rotationCorrection = cos(atan2(y, x) - PI / 4); 
    
    if(_option == MECANUM_SQUARE)
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