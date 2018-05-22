#include "Vector2.h"

Vector2::Vector2()
{
    set(0.0f, 0.0f);
}

Vector2::Vector2(float vx, float vy)
{
    set(vx, vy);
}
    
void Vector2::set(float vx, float vy)
{
    x = vx;
    y = vy;
}

double Vector2::getMagnitude()
{
    return sqrt(x*x + y*y);
}