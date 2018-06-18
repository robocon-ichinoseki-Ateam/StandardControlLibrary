#ifndef Vector_3_h
#define Vector_3_h

#include "mbed.h"
#include "Quaternion.h"

class Vector3
{
public:
    Vector3();
    Vector3(double vx, double vy, double vz);
    
    void set(double vx, double vy, double vz);
    double getMagnitude();
    void normalize();
    Vector3 getNormalized();
    void rotate(Quaternion *q);
    Vector3 getRotated(Quaternion *q);
    
    static Vector3 zero()
    {
        return Vector3(0.0f, 0.0f, 0.0f);
    }
    
    Vector3& operator = (const Vector3& v)
    {
        x = v.x;
        y = v.y;
        z = v.z;
        
        return *this;
    }
    
    bool operator == (const Vector3& v) const
    {
        return (x == v.x) && (y == v.y) && (z == v.z);
    }
    
    bool operator != (const Vector3& v) const
    {
        return !((x == v.x) && (y == v.y) && (z == v.z));
    }
    
    Vector3 operator + (const Vector3& v)
    {
        return Vector3(x + v.x, y + v.y, z + v.z);
    }
    
    Vector3 operator - (const Vector3& v)
    {
        return Vector3(x - v.x, y - v.y, z - v.z);
    }
    
    Vector3 operator * (double value)
    {
        return Vector3(x * value, y * value, z * value);
    }
    
    Vector3 operator / (double value)
    {
        return Vector3(x / value, y / value, z / value);
    }
    
    Vector3& operator += (const Vector3& v)
    {
        x += v.x;
        y += v.y;
        z += v.z;
        
        return *this;
    }
    
    Vector3& operator -= (const Vector3& v)
    {
        x -= v.x;
        y -= v.y;
        z -= v.z;
        
        return *this;
    }
    
    Vector3& operator *= (double value)
    {
        x *= value;
        y *= value;
        z *= value;
        
        return *this;
    }
    
    Vector3& operator /= (double value)
    {
        x /= value;
        y /= value;
        z /= value;
        
        return *this;
    }
public:
    double x, y, z;
};

#endif //Vector_3_h
