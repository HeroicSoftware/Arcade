#include <iostream>
#include <cassert>
#include <cmath>

#ifndef UTILITY_VECTOR2D_H_
#define UTILITY_VECTOR2D_H_
class Vector2D
{
public:
    static const Vector2D Zero;
    Vector2D() : Vector2D(0, 0)
    {
    }
    Vector2D(float x, float y) : x(x), y(y)
    {
    }
    inline float GetX() const
    {
        return x;
    }
    inline void SetX(float x)
    {
        this->x = x;
    }
    inline float GetY() const
    {
        return y;
    }
    inline void SetY(float y)
    {
        this->y = y;
    }

    bool operator!=(const Vector2D &vector2D) const; // IsNotEqual()
    bool operator==(const Vector2D &vector2D) const; // IsEqual()
    float GetAngleBetween(const Vector2D &vector2D);
    float GetDistance(const Vector2D &vector2D) const;
    float GetDotProduct(const Vector2D &vector2D) const;
    float Magnitude() const;
    float MagnitudeSquared() const;
    friend std::ostream &operator<<(std::ostream &consoleOut, const Vector2D &vector2D); // toString()
    friend Vector2D operator*(float scale, const Vector2D &vector2D);
    friend Vector2D operator/(float scale, const Vector2D &vector2D);
    Vector2D &Normalize();
    Vector2D &operator-=(const Vector2D &vector2D);
    Vector2D &operator*=(float scale);
    Vector2D &operator/=(float scale);
    Vector2D &operator+=(const Vector2D &vector2D);
    Vector2D GetProjectionOnToOtherVector(const Vector2D &vector2D) const;
    Vector2D GetReflectionVector(const Vector2D &normal) const;
    Vector2D GetUnitVector() const;
    Vector2D operator-() const;
    Vector2D operator-(const Vector2D &vector2D) const;
    Vector2D operator*(float scale) const;
    Vector2D operator/(float scale) const;
    Vector2D operator+(const Vector2D &vector2D) const;
    Vector2D RotationResult(float angle, const Vector2D &aroundPoint);
    void Rotate(float angle, const Vector2D &aroundPoint);

private:
    float x;
    float y;
};
#endif /* UTILITY_VECTOR2D_H_ */
