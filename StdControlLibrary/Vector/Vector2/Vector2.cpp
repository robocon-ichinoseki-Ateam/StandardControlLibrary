#include "Vector2.h"

Vector2::Vector2()
{
    set(0.0f, 0.0f);
}

Vector2::Vector2(double vx, double vy)
{
    set(vx, vy);
}
    
void Vector2::set(double vx, double vy)
{
    x = vx;
    y = vy;
}

double Vector2::getMagnitude()
{
    return sqrt(x*x + y*y);
}

void Vector2::normalize()
{
    float m = getMagnitude();
    x /= m;
    y /= m;
}

Vector2 Vector2::getNormalized()
{
    Vector2 r(x, y);
    r.normalize();
    return r;
}

void Vector2::rotate(double angle)
{
    double v[2] = {x, y};
    x = v[0] * cos(angle) - v[1] * sin(angle);
    y = v[0] * sin(angle) + v[1] * cos(angle);
}

Vector2 Vector2::getRotated(double angle)
{
    Vector2 r(x, y);
    r.rotate(angle);
    return r;
}