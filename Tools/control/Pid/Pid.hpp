#ifndef _PID_HPP_
#define _PID_HPP_
#include <mbed.h>

class Pid
{
    public:
    Pid(double, double, double);
    double calculate(double, double);
    double Kp, Ki, Kd;
};

#endif
