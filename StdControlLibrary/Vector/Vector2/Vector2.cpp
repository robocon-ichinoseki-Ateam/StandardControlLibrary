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