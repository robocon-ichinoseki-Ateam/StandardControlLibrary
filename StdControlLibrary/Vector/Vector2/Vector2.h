#ifndef Vector_2_h
#define Vector_2_h

#include "mbed.h"

class Vector2
{
public:
    Vector2();
    Vector2(double vx, double vy);
    
    void set(double vx, double vy);
    double getMagnitude();
    void normalize();
    Vector2 getNormalized();
    void rotate(double angle);
    Vector2 getRotated(double angle);
    
    static Vector2 zero()
    {
        return Vector2(0.0f, 0.0f);
    }
    
    Vector2& operator = (const Vector2& v)
    {
        x = v.x;
        y = v.y;
        
        return *this;
    }
    
    bool operator == (const Vector2& v) const
    {
        return (x == v.x) && (y == v.y);
    }
    
    bool operator != (const Vector2& v) const
    {
        return !((x == v.x) && (y == v.y));
    }
    
    Vector2 operator + (const Vector2& v)
    {
        return Vector2(x + v.x, y + v.y);
    }
    
    Vector2 operator - (const Vector2& v)
    {
        return Vector2(x - v.x, y - v.y);
    }
    
    Vector2 operator * (double value)
    {
        return Vector2(x * value, y * value);
    }
    
    Vector2 operator / (double value)
    {
        return Vector2(x / value, y / value);
    }
    
    Vector2& operator += (const Vector2& v)
    {
        x += v.x;
        y += v.y;
        
        return *this;
    }
    
    Vector2& operator -= (const Vector2& v)
    {
        x -= v.x;
        y -= v.y;
        
        return *this;
    }
    
    Vector2& operator *= (double value)
    {
        x *= value;
        y *= value;
        
        return *this;
    }
    
    Vector2& operator /= (double value)
    {
        x /= value;
        y /= value;
        
        return *this;
    }
    
public:
    double x, y;
};

#endif //Vector_2_h
