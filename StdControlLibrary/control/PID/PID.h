#ifndef PID_h
#define PID_h
#include <mbed.h>

class PID
{
public:
    PID(double, double, double);
    double calculate(double, double, long double);

public:
    double Kp, Ki, Kd;
    
private:
    double integral;
    double diff[2]; // 0: 現在, 1: 過去
};

#endif
