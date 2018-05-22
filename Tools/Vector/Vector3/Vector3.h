#ifndef Vector_3_h
#define Vector_3_h

#include "mbed.h"

class Vector3
{
public:
    Vector3();
    Vector3(float vx, float vy, float vz);
    
    void set(float vx, float vy, float vz);
    double getMagnitude();
    static Vector3 zero()
    {
        return Vector3(0.0f, 0.0f, 0.0f);
    }
    
    Vector3& operator = (Vector3& v)
    {
        x = v.x;
        y = v.y;
        z = v.z;
        
        return *this;
    }
    
    Vector3& operator + (Vector3& v)
    {
        x += v.x;
        y += v.y;
        z += v.z;
        
        return *this;
    }
    
    Vector3& operator - (Vector3& v)
    {
        x -= v.x;
        y -= v.y;
        z -= v.z;
        
        return *this;
    }
    
    Vector3& operator * (float value)
    {
        x *= value;
        y *= value;
        z *= value;
        
        return *this;
    }
    
    Vector3& operator / (float value)
    {
        x /= value;
        y /= value;
        z /= value;
        
        return *this;
    }
public:
    float x, y, z;
};

#endif //Vector_3_h
