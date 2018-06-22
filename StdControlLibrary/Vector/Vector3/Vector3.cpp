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

void Vector3::normalize()
{
    float m = getMagnitude();
    x /= m;
    y /= m;
    z /= m;
}

Vector3 Vector3::getNormalized()
{
    Vector3 r(x, y, z);
    r.normalize();
    return r;
}

void Vector3::rotate(Quaternion *q)
{
    // Todo
}

Vector3 Vector3::getRotated(Quaternion *q)
{
    Vector3 r(x, y, z);
    //r.rotate();
    return r;
}