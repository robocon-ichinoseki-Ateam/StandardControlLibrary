#include "Vector3.h"

Vector3::Vector3()
{
    set(0.0f, 0.0f, 0.0f);
}

Vector3::Vector3(double vx, double vy, double vz)
{
    set(vx, vy, vz);
}
    
void Vector3::set(double vx, double vy, double vz)
{
    x = vx;
    y = vy;
    z = vz;
}

double Vector3::getMagnitude()
{
    return sqrt(x*x + y*y + z*z);
}