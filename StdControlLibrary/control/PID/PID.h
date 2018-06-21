#ifndef PID_h
#define PID_h
#include <mbed.h>

class PID
{
    public:
    PID(double, double, double);
    double calculate(double, double, long double);
    double Kp, Ki, Kd;
};

#endif
