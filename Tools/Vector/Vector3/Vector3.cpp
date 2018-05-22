#include "Vector3.h"

Vector3::Vector3()
{
    set(0.0f, 0.0f, 0.0f);
}

Vector3::Vector3(float vx, float vy, float vz)
{
    set(vx, vy, vz);
}
    
void Vector3::set(float vx, float vy, float vz)
{
    x = vx;
    y = vy;
    z = vz;
}

double Vector3::getMagnitude()
{
    return sqrt(x*x + y*y + z*z);
}