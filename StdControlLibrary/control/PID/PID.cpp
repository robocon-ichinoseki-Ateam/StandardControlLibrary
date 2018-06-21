#include "PID.h"
PID::PID(double p, double i, double d)
{
    Kp = p;
    Ki = i;
    Kd = d;
}
    
double PID::calculate(double targetVal, double nowVal, long double dt)
{   
    static double integral = 0;
    static double diff[2] = {0, 0}; // 0: 現在, 1: 過去
    double p, i, d;
    
    diff[0] = targetVal - nowVal;
    integral += (diff[0] + diff[1]) * (dt / 2.0);
        
    p = Kp * diff[0];
    i = Ki * integral;
    d = Kd * ((diff[0] - diff[1]) / dt);
    
    // 次回ループのために今回の値を前回の値にする
    diff[1] = diff[0];
        
    return p + i + d;
}
