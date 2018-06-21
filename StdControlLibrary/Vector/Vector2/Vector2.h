#ifndef Vector_2_h
#define Vector_2_h

#include "mbed.h"
#include "GenericFunctions.h"

class Vector2
{
public:
    Vector2();
    Vector2(double vx, double vy);
    
    // function
    void set(double vx, double vy);
    double getMagnitude();
    void normalize();
    Vector2 getNormalized();
    void rotate(double angle);
    Vector2 getRotated(double angle);
    
    // static function
    static double getDot(Vector2 a, Vector2 b);
    static double getAngle(Vector2 a, Vector2 b);
    static double getDistance(Vector2 a, Vector2 b); // = (b-a).getMagnitude()
    static Vector2 leap(Vector2 a, Vector2 b, double t);
    //static leapUnclamped(Vector2 a, Vector2 b, double t);
    //static Vector2 sLeap(Vector2 a, Vector2 b, double t);
    
    // constatnt vector
    static Vector2 zero()
    {
        return Vector2(0.0, 0.0);
    }

    static Vector2 up()
    {
        return Vector2(0.0, 1.0);
    }
    
    static Vector2 down()
    {
        return Vector2(0.0, -1.0);
    }
    
    static Vector2 right()
    {
        return Vector2(1.0, 0.0);
    }
    
    static Vector2 left()
    {
        return Vector2(-1.0, 0.0);
    }
    
    // operator
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
