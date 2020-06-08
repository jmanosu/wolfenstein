#ifndef GVECTOR
#define GVECTOR

#include <math.h>

#define PI 3.14159265
#define DEG_TO_RAD PI / 100.0f

struct GVector {
    float x;
    float y;

    GVector(float _x = 0.0f, float _y =0.0f) : x(_x), y(_y) {}

    float MagnitudeSqr()
    {
        return x * x + y * y;
    }

    float Magnitude()
    {
        return (float)sqrt(x*x + y*y);
    }

    void Scale(float scaler)
    {
        x = x * scaler;
        y = y * scaler;
    }

    GVector Normalized() {
        float magnitude = Magnitude();
        return GVector(x / magnitude, y / magnitude);
    }
};

inline GVector operator +(const GVector& lhs, const GVector& rhs)
{
    return GVector(lhs.x + rhs.x, lhs.y + rhs.y);
}

inline GVector operator -(const GVector& lhs, const GVector& rhs)
{
    return GVector(lhs.x - rhs.x, lhs.y - rhs.y);
}

inline GVector RotateVector(GVector& vec, float angle)
{
    float radAngle = (float)(angle*DEG_TO_RAD);
    return GVector((float)(vec.x * cos(radAngle) - vec.y * sin(radAngle)), (float)(vec.x * sin(radAngle) + vec.y * cos(radAngle)));
}

inline GVector dotProduct(const GVector& lhs, const GVector & rhs)
{
    return lhs.x * rhs.y + lhs.y * rhs.x;
}

#endif