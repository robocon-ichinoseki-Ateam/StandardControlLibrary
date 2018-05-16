#ifndef Vector_2_h
#define Vector_2_h

#include "mbed.h"

class Vector2
{
public:
    Vector2();
    Vector2(float vx, float vy);
    
    void set(float vx, float vy);
    double getMagnitude();
    static Vector2 zero()
    {
        return Vector2(0.0f, 0.0f);
    }
    
    Vector2& operator = (Vector2& v)
    {
        x = v.x;
        y = v.y;
        
        return *this;
    }
    
    Vector2& operator + (Vector2& v)
    {
        x += v.x;
        y += v.y;
        
        return *this;
    }
    
    Vector2& operator - (Vector2& v)
    {
        x -= v.x;
        y -= v.y;
        
        return *this;
    }
    
    Vector2& operator * (float value)
    {
        x *= value;
        y *= value;
        
        return *this;
    }
    
    Vector2& operator / (float value)
    {
        x /= value;
        y /= value;
        
        return *this;
    }
    
public:
    float x, y;
};

#endif //Vector_2_h
