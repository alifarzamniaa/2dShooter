#ifndef VEC2_H
#define VEC2_H
#include <cassert>
#include <cmath>

class Vec2
{
  public:
    Vec2() : x(0.0f), y(0.0f)
    {
    }

    Vec2(float x, float y) : x(x), y(y)
    {
    }

    float Length() const
    {
        return std::sqrt(x * x + y * y);
    }

    float LengthSquared() const
    {
        return x * x + y * y;
    }

    void Normalize()
    {
        auto len = Length();
        if (len > 0.0f)
        {
            x = x / len;
            y = y / len;
        }
    }

    Vec2 GetNormalized() const
    {
        auto len = Length();
        if (len > 0.0f)
        {
            return Vec2(x / len, y / len);
        }
        else
        {
            return *this;
        }
    }

    // NOTE(ali-farzamnia) : because its a float it should use epsilon stuff for better comparisons
    bool operator==(const Vec2& other) const
    {
        return x == other.x && y == other.y;
    }

    bool operator!=(const Vec2& other) const
    {
        return !(*this == other);
    }

    Vec2 operator*(float in_scale) const
    {
        return Vec2(x * in_scale, y * in_scale);
    }

    Vec2& operator*=(float in_scale)
    {
        x *= in_scale;
        y *= in_scale;
        return *this;
    }

    Vec2 operator+(const Vec2& other) const
    {
        return Vec2(x + other.x, y + other.y);
    }

    Vec2& operator+=(const Vec2& other)
    {
        x += other.x;
        y += other.y;
        return *this;
    }

    Vec2 operator/(float in_scale) const
    {
        assert(in_scale != 0.0f);
        return Vec2(x / in_scale, y / in_scale);
    }

    Vec2& operator/=(float in_scale)
    {
        assert(in_scale != 0.0f);
        x /= in_scale;
        y /= in_scale;
        return *this;
    }

    Vec2 operator-(const Vec2& other) const
    {
        return Vec2(x - other.x, y - other.y);
    }

    Vec2& operator-=(const Vec2& other)
    {
        x -= other.x;
        y -= other.y;
        return *this;
    }

    float DotProduct(const Vec2& other) const
    {
        return x * other.x + y * other.y;
    }

    float DistanceTo(const Vec2& other) const
    {
        return (*this - other).Length();
    }

    float CrossProduct(const Vec2& other) const
    {
        return x * other.y - y * other.x;
    }

  public:
    float x;
    float y;
};
#endif // ! VEC2_H
